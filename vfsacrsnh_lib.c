/*
	 vfsacrsnh_lib.c (c)
	 
	 Purpose: 'Mvfsacrsnh.c' library.
	 	 
	 Site: https://www.geofisicando.com
	 
	 Programmer: Rodolfo A. C. Neves (Dirack) 13/08/2021

	 Email:  rodolfo_profissional@hotmail.com

	 License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <rsf.h>
/*^*/

#define signal(s) ((s<0)?(-1.):(1.))
/*< Signal function >*/
/*^*/

void generatePreciseRandomSeed()
/*< Generate a more precise random seed >*/
{
	struct timeval start;
	gettimeofday(&start,NULL);
	srand((unsigned)start.tv_usec);
}

float getRandomNumberBetween0and1(){
/*< Function to get a random number between 0 and 1 >*/
	return (float)(rand()%1000)/1000;
}

float getVfsaIterationTemperature(	int iteration /* Number of the current iteration */,
					float dampingFactor /* C0, the VFSA damping factor */,
					float initialTemperature /* T0, the VFSA Initial temperature */)
/*< Temperature function for VFSA algorithm >*/
{

	return initialTemperature*expf(-dampingFactor*pow(iteration,0.25));

}

void disturbParameters(  float temperature /* Temperature of the current iteration */,
			 float* disturbedParameter /* disturbed parameters vector */,
			 float* parameter /* parameters vector */,
			 float rn_max,
			 float rn_min,
			 float rnip_max,
			 float rnip_min,
			 float beta_max,
			 float beta_min)
/*< Disturb parameters from the previous VFSA iteration

Note: It receives a parameter vector and distubs it accordingly to 
VFSA algorithm disturb parameters step.
 >*/
{
	float u;
	float disturbance;
	float rn_aperture=rn_max-rn_min;
	float rnip_aperture=rnip_max-rnip_min;
	float beta_aperture=beta_max-beta_min;

	u=getRandomNumberBetween0and1();
			
	disturbance = signal(u - 0.5) * temperature * (pow( (1+temperature),fabs(2*u-1) )-1);

	/* Disturb RN */

	disturbedParameter[0] = parameter[0] + disturbance * (rn_aperture);
				
	if (disturbedParameter[0] >= rn_max || disturbedParameter[0] <= rn_min) {

		disturbedParameter[0] = (rn_aperture) * getRandomNumberBetween0and1() + rn_min;
		
	}

	/* Disturb RNIP */

	disturbedParameter[1] = parameter[1] + disturbance * (rnip_aperture);
				
	if (disturbedParameter[1] >= (rnip_max) || disturbedParameter[1] <= (rnip_min)) {

		disturbedParameter[1] = (rnip_aperture) * getRandomNumberBetween0and1() + rnip_min;
		
	}

	if(disturbedParameter[1]<rnip_min) sf_error("rnip < rnip_min, %f < %f",disturbedParameter[1],rnip_min);

	/* Disturb BETA */

	disturbedParameter[2] = parameter[2] + (disturbance/10.) * (beta_aperture);

	if (disturbedParameter[2] >= beta_max || disturbedParameter[2] <= beta_min) {

		disturbedParameter[2] = (beta_aperture) * getRandomNumberBetween0and1() + beta_min;

	}		

}

void nonHyperbolicCRSapp(	float **t /* non-hyperbolic CRS traveltime surface */,
				int mMAX /* CMP aperture */,
				int hMAX /* Offset aperture */,
				float m0 /* Central CMP of the approximation */,
				float dm, /* CMP sampling */
				float om /* CMP axis origin */,
				float dh /* half-offset sampling */,
				float oh /* half-offset axis origin */,
				float t0 /* Normal ray traveltime */,
				float v0 /* Near surface velocity */,
				float RN /* RN, CRS parameter */,
				float RNIP /* RNIP, CRS parameter */,
				float BETA /* BETA, CRS parameter */,
				bool half /* Half-Offset coordinates */)
/*< Returns the Non hyperbolic CRS approximation surface (FOMEL; KAZINNIK, 2013) >*/
{
	float m0_index=(int)(m0/dm);
	float a1, a2, b2, c1, Fd, Fd1, Fd2;
	int im, ih;
	float m, h, mmh, mph;
	float sinB=sin(BETA),cosB=cos(BETA);
	
	om = om+(m0_index-mMAX)*dm;

	a1=(2*sinB)/(v0);		
	a2=(2*cosB*cosB*t0)/(v0*RN);
	b2=(2*cosB*cosB*t0)/(v0*RNIP);
	c1=2*b2+a1*a1-a2;

	for (im=0; im < 2*mMAX+1; im++){
			
		m=(im*dm+om)-m0;

		for(ih=0;ih<hMAX;ih++){
			
			h=ih*dh+oh;
			if(!half) h/=2;
			mmh=m-h;
			mph=m+h;

			Fd=(t0+a1*m)*(t0+a1*m)+a2*m*m;				
			Fd2=(t0+a1*(mmh))*(t0+a1*(mmh))+a2*(mmh)*(mmh);
			Fd1=(t0+a1*(mph))*(t0+a1*(mph))+a2*(mph)*(mph);					
			t[im][ih]=sqrt((Fd+c1*h*h+sqrt(Fd2*Fd1))*0.5); 
		}
	}

}

float semblance(float m0 /* Central CMP of the approximation */,
		float dm /* CMP sampling */,
		float om /* CMP axis origin */,
		float oh /* half-offset axis origin */,
		float dh /* half-offset axis sampling */,
		float dt /* time sampling */,
		int nt /* number of time samples */,
		float t0 /* Normal ray traveltime */,
		float v0 /* Near surface velocity */,
		float RN /* RN, CRS parameter */,
		float RNIP /* RNIP, CRS parameter */,
		float BETA /* BETA, CRS parameter */,
		float*** t /* reflection data cube A(m,h,t) */,
		int mMAX, /* CMP aperture */
		int hMAX, /* Offset aperture */
		bool half /* Half-offset coordinates */)
/*< Calculate semblance between the Non Hyperbolic CRS approximation surface and reflection data >*/
{

	int im, ih, numSamples=0;
	float amplitude=0.;
	float amplitudeSampleSum=0.;
	float amplitudeSquaredSampleSum=0.;
	float semblance=0;
	int tetai;
	float **teta;
	int m0_index_init, m0_index_end;

	teta = sf_floatalloc2(hMAX,2*mMAX+1);

	m0_index_init = (int)(m0/dm)-mMAX;
	m0_index_end = (int)(m0/dm)+mMAX;

	nonHyperbolicCRSapp(teta,mMAX,hMAX,m0,dm,om,dh,oh,t0,v0,RN,RNIP,BETA,half);

	for (im=m0_index_init; im < m0_index_end; im++){
			
		for(ih=0;ih<hMAX;ih++){

			tetai=roundf(teta[im-m0_index_init][ih]/dt);

			if(tetai>=0 && tetai < nt){
				amplitude = t[im][ih][tetai];
				
				amplitudeSampleSum += amplitude;
					
				amplitudeSquaredSampleSum += (amplitude*amplitude);
			}
				
			numSamples++;
		}
		
	}		

	if(amplitudeSampleSum==0)		
		return semblance=0;
	else
		return semblance=(amplitudeSampleSum*amplitudeSampleSum)/(numSamples*amplitudeSquaredSampleSum);

}

bool checkValueInsideBoundaries(float value, float min, float max)
/*< check if the value is inside the boundaries min < value < max >*/
{
	return (min < value && value < max);
}

bool validBoundariesAndApertureForCMP(int nm0, float om0, float dm0, int mMAX, int nm, float om, float dm, char *strerr)
/*< Check if CMP coordinates for m0s are inside data cube space to avoid segmentation fault errors >*/
{
	float m0min, m0max;

	m0min = om0-(dm*mMAX);
	m0max = om0+dm0*(nm0-1)+(dm*mMAX);

	if(m0min < om || m0max > (om+dm*(nm-1))){
		sprintf(strerr,"Invalid boundaries for CMP m0min=%f m0max=%f. Please check aperture!",m0min,m0max);
		return false;
	}

	return true;
}

bool validBoundariesAndApertureForOffset(int nh, float oh, float dh, int hMAX, char *strerr)
/*< Check if Offset coordinates are inside data cube space to avoid segmentation fault errors >*/
{
	if((oh+dh*hMAX) > (oh+dh*(nh-1))){
		sprintf(strerr,"Invalid boundaries for Offset hmin=%f hmax=%f. Please check aperture!",oh,oh+dh*hMAX);
		return false;
	}

	return true;
}

bool validBoundariesAndApertureForT0(int nt0, float ot0, float dt0, int nt, float ot, float dt, char *strerr)
/*< Check if t0 coordinates are inside data cube space to avoid segmentation fault errors >*/
{
	float t0min = ot0;
	float t0max = ot0+dt0*(nt0-1);

	if(t0min < ot || t0max > ot+dt*(nt-1)){
		sprintf(strerr,"Invalid boundaries for time t0 t0min=%f t0max=%f. Please check aperture!",t0min,t0max);
		return false;
	}

	return true;
}


bool repeatOptionEqual1ForGetConvergenceGraphTrue(bool get_convergence_graph, int repeat)
/*< Repeat option should be equal one when get_convergence_graph flag is on to avoid multiple thread >*/
{
	return repeat==1 && get_convergence_graph;
}

void prepareConvergenceGraphFile(sf_file outgraph, bool get_convergence_graph, int repeat, int itmax)
/*< Check parameters (repeat should be equal to 1 when generating a convergence graph)  and Prepare the convergence graph file >*/
{
	if(!repeatOptionEqual1ForGetConvergenceGraphTrue(get_convergence_graph,repeat))
		sf_error("The repeat parameter should be equal 1 for getgraph=y!");
	sf_putint(outgraph,"n1",itmax);
	sf_putfloat(outgraph,"d1",1);
	sf_putfloat(outgraph,"o1",0);
	sf_putstring(outgraph,"title","Convergence graph");
	sf_putstring(outgraph,"label1","Iteration");
	sf_putstring(outgraph,"label2","Semblance");
}

bool checkParametersFileDimensionReturnStrError(sf_file parametersFile,int nt0, int nm0, char* strerr)
/*< check n1 and n2 dimension and n1 should be equal to nt0 and n2 should be equal to nm0 in parameters files >*/
{
	int n1, n2;

	if(!sf_histint(parametersFile,"n1",&n1)){
		strcpy(strerr,"No n1= in file");
	}else if(!sf_histint(parametersFile,"n2",&n2)){
		strcpy(strerr,"No n2= in file");
	}else if(n1!=nt0){
		strcpy(strerr,"n1 should be equal to nt0 in file");
	}else if(n2!=nm0){
		strcpy(strerr,"n2 should be equal to nm0 in file");
	}else{
		return true;
	}
	return false;
}

bool checkAndLoadDataCubeDimensionsReturnStrError(sf_file in,
						  int *n1, float *o1, float *d1,
						  int *n2, float *o2, float *d2,
						  int *n3, float *o3, float *d3,
						  char *strerr)
/*< Check each dimension for a data cube and load it >*/
{
        if(!sf_histint(in,"n1",n1)){
		strcpy(strerr,"No n1= in input");
	}else if (!sf_histfloat(in,"o1",o1)){
		strcpy(strerr,"No o1= in input");
	}else if (!sf_histfloat(in,"d1",d1)){
		strcpy(strerr,"No d1= in input");
	}else if (!sf_histint(in,"n2",n2)){
		strcpy(strerr,"No n2= in input");
	}else if (!sf_histfloat(in,"o2",o2)){
	       	strcpy(strerr,"No o2= in input");
	}else if (!sf_histfloat(in,"d2",d2)){
		strcpy(strerr,"No d2= in input");
	}else if (!sf_histint(in,"n3",n3)){
		strcpy(strerr,"No n3= in input");
	}else if (!sf_histfloat(in,"o3",o3)){
		strcpy(strerr,"No o3= in input");
	}else if (!sf_histfloat(in,"d3",d3)){
		strcpy(strerr,"No d3= in input");
	}else{
		return true;
	}

	return false;

}

void loadParametersFilesVectors(float** parametersFilesVectors[6],char* labels[6], int nt0, int nm0)
/*< Load parameters file vector >*/
{
	int q;
	sf_file parametersFiles;
	char strerr[50];

	for(q=0;q<6;q++){
		parametersFiles = sf_input(labels[q]);
		if(!checkParametersFileDimensionReturnStrError(parametersFiles,nt0,nm0,strerr))
			sf_error("%s %s",strerr,labels[q]);
		parametersFilesVectors[q] = sf_floatalloc2(nt0,nm0);
		sf_floatread(parametersFilesVectors[q][0],nt0*nm0,parametersFiles);
		sf_fileclose(parametersFiles);
	}
}

void prepareMTConvergenceGraphFile(sf_file outgraph, bool get_mt_convergence_graph, int repeat, int itmax)
/*< Check parameters (repeat should be equal to 1 when generating a convergence graph)  and Prepare the convergence graph file >*/
{
	sf_putint(outgraph,"n1",itmax);
	sf_putfloat(outgraph,"d1",1);
	sf_putfloat(outgraph,"o1",0);
	sf_putint(outgraph,"n2",repeat);
	sf_putfloat(outgraph,"o2",0.);
	sf_putfloat(outgraph,"d2",1.);
	sf_putstring(outgraph,"label1","Iteration");
	sf_putstring(outgraph,"label2","Semblance");
}

