/* Version 1.0 - Zero offset CRS ter inversion (RN, RNIP, BETA) with Very Fast Simulated Aneeling (VFSA) Global Optimization

This program the Non-Hyperbolic CRS approximation to fit data cube and get the ters (Fomel, 2013).

Programer: Rodolfo A. C. Neves (Dirack) 19/09/2019

Email:  rodolfo_profissional@hotmail.com

License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

 */

#include "vfsacrsnh_lib.h"

int main(int argc, char* argv[])
{

	float m0; // central CMP
	float om; // CMP axis origin
	float dm; // CMP sampling
	int nm; // Number of CMP's
	float oh; // Offset axis origin
	float dh; // Offset sampling
	int nh; // Number of Offsets
	int nt; // Number of time samples
	float ot; // Time axis origin
	float dt; // Time sampling
	bool verb; // Key to turn On/Off active mode
	float v0; // Near surface velocity
	float t0; // Normal ray time travel
	float cnew[3]; // Temporary parameters vector - actual iteration
	float c[3]; // Temporary parameters vector - last iteration
	float **otm; // Optimazed parameters
	float otrn, otrnip, otbeta, otsemb; // Optimazed ters - actual iteration
	float deltaE, PM; // Metrópolis criteria
	float Em0=0; // Major semblance
	float u; // Random number
	float ***t; // Data cube A(m,h,t)
	int q, i, k, l; // loop counter
	float semb; // Semblance - actual iteration
	float RN, RNIP, BETA; // CRS ters
	float semb0; // Inicial semblance value
	float c0; // VFSA damping factor
	float temp0; // inicial VFSA temperature
	float temp; // VFSA temperature
	int repeat; // perform VFSA optimization more than once
	float om0;
	float dm0;
	int nm0;
	float ot0;
	float dt0;
	int nt0;

	/* RSF files I/O */  
	sf_file in, out;

	/* RSF files axis */
	sf_axis ax,ay,az;

	sf_init(argc,argv); 

	in = sf_input("in");
	out = sf_output("out");

	if (!sf_getfloat("om0",&om0)) om0=0.0;
	/* central CMP's origin  (Km) */
	m0=om0;

	if (!sf_getfloat("dm0",&dm0)) dm0=0.1;
	/* central CMP's sampling (Km) */

	if (!sf_getint("nm0",&nm0)) nm0=1;
	/* central CMP's number of samples (Km) */

	if (!sf_getfloat("v0",&v0)) v0=1.5;
	/* Near surface velocity (Km/s) */

	if (!sf_getfloat("ot0",&ot0)) ot0=0.0;
	/* t0's origin (s) */
	t0=ot0;

	if (!sf_getfloat("dt0",&dt0)) dt0=0.1;
	/* t0's sampling (s) */

	if (!sf_getint("nt0",&nt0)) nt0=1;
	/* Number of t0's sampling (s) */

	if (!sf_getfloat("c0",&c0)) c0=0.5;
	/* damping factor of VFSA */

	if (!sf_getfloat("temp0",&temp0)) temp0=10;
	/* inicial VFSA temperature */

	if(!sf_getint("repeat",&repeat)) repeat=1;
	/* How many times to perform VFSA global optimization */

	if (!sf_histint(in,"n1",&nt)) sf_error("No n1= in input");
	if (!sf_histfloat(in,"d1",&dt)) sf_error("No d1= in input");
	if (!sf_histfloat(in,"o1",&ot)) sf_error("No o1= in input");
	if (!sf_histint(in,"n2",&nh)) sf_error("No n2= in input");
	if (!sf_histfloat(in,"d2",&dh)) sf_error("No d2= in input");
	if (!sf_histfloat(in,"o2",&oh)) sf_error("No o2= in input");
	if (!sf_histint(in,"n3",&nm)) sf_error("No n3= in input");
	if (!sf_histfloat(in,"d3",&dm)) sf_error("No d3= in input");
	if (!sf_histfloat(in,"o3",&om)) sf_error("No o3= in input");

	if(! sf_getbool("verb",&verb)) verb=0;
	/* 1: active mode; 0: quiet mode */

	if (verb) {

		sf_warning("Active mode on!!!");
		sf_warning("Command line ters: "); 
		sf_warning("m0=%f v0=%f t0=%f c0=%f temp0=%f repeat=%i",m0,v0,t0,c0,temp0,repeat);
		sf_warning("Input file ters: ");
		sf_warning("n1=%i d1=%f o1=%f",nt,dt,ot);
		sf_warning("n2=%i d2=%f o2=%f",nh,dh,oh);
		sf_warning("n3=%i d3=%f o3=%f",nm,dm,om);
	}
	
	c[0] = 0;
	c[1] = 0;
	c[2] = 0;
	cnew[0] = 0;
	cnew[1] = 0;
	cnew[2] = 0;
	srand(time(NULL));

	/* Read seismic data cube */
	t=sf_floatalloc3(nt,nh,nm);
	sf_floatread(t[0][0],nm*nh*nt,in);

	sf_fileclose(in);

	semb0=0;

	/* Save optimized ters in ' file */
	otm=sf_floatalloc2(8,nm0*nt0);

	for(l=0;l<nm0;l++){
		
		m0 = l*dm0+om0;

		for(k=0;k<nt0;k++){
				otsemb = 0.0;
				semb0 = 0.0;
				t0 = k*dt0+ot0;
				#pragma omp parallel for \
				private(i,q,temp,c,RN,RNIP,BETA,cnew,semb) \
				shared(semb0,otsemb,otrn,otrnip,otbeta) \
				schedule(dynamic)
				for(i=0;i<repeat;i++){

					for (q=0; q <ITMAX; q++){
							
						/* calculate VFSA temperature for this iteration */
						temp=getVfsaIterationTemperature(q,c0,temp0);
										
						/* ter disturbance */
						disturbParameters(temp,cnew,c);
																				
						RN = cnew[0];
						RNIP = cnew[1];
						BETA = cnew[2];

						semb=0;
					
						/* Semblance: Non-hyperbolic CRS approximation with data */		
						semb=semblance(m0,dm,om,oh,dh,dt,nt,t0,v0,RN,RNIP,BETA,t);

						#pragma omp critical(evaluate_best_semblance)
						{

							if(q > ITMAX*0.2 && otsemb > 0.9) q=ITMAX;	
							/* VFSA ters convergence condition */		
							if(fabs(semb) > fabs(semb0) ){
								otsemb = semb;
								otrn = RN;
								otrnip = RNIP;
								otbeta = BETA;
								semb0 = semb;			
							}

							/* VFSA ters update condition */
							deltaE = -semb - Em0;
							
							/* Metrópolis criteria */
							PM = expf(-deltaE/temp);
							
							if (deltaE<=0){
								c[0] = cnew[0];
								c[1] = cnew[1];
								c[2] = cnew[2];
								Em0 = -semb;
							} else {
								u=getRandomNumberBetween0and1();
								if (PM > u){
									c[0] = cnew[0];
									c[1] = cnew[1];
									c[2] = cnew[2];
									Em0 = -semb;
								}	
							}	
						} /* Critical section parallelization */
						
					} /* loop over iterations */

					c[0]=0;c[1]=0;c[2]=0;

				} /* repeat VFSA global optimization */
				otm[k][0] = otrn;
				otm[k][1] = otrnip;
				otm[k][2] = otbeta;
				otm[k][3] = otsemb;
				otm[k][4] = c0;
				otm[k][5] = temp0;
				otm[k][6] = t0;
				otm[k][7] = m0;
			
				/* Show optimized ters on screen before save them */
				if(verb) sf_warning("(%d/%d): RN=%f, RNIP=%f, BETA=%f, SEMB=%f\r\r",l*nt0+k+1,nm0*nt0,otrn,otrnip,otbeta,otsemb);

			}
	}

	free(t);

	/* axis = sf_maxa(n,o,d)*/
	ax = sf_maxa(8, 0, 1);
	ay = sf_maxa(nt0*nm0, 0, 1);
	az = sf_maxa(1, 0, 1);


	/* sf_oaxa(file, axis, axis index) */
	sf_oaxa(out,ax,1);
	sf_oaxa(out,ay,2);
	sf_oaxa(out,az,3);
	sf_putstring(out,"label1","parameters");
	sf_putstring(out,"label2","(t0,m0) index");
	sf_floatwrite(otm[0],8*nt0*nm0,out);

	sf_close();
	exit(0);
}
