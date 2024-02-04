/* Zero offset CRS parameter inversion of RN, RNIP, BETA with Very Fast Simulated Annealing (VFSA) Global Optimization. This program uses the Non-Hyperbolic CRS approximation (Fomel and Kazinnik, 2013) to fit seismic data cube and get the best parameters using semblance criteria.

Package version: 2.0.2

Programmer: Rodolfo A. C. Neves (Dirack) 13/08/2021

Email:  rodolfo_profissional@hotmail.com

License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

*/

#include "vfsacrsnh_lib.h"

int main(int argc, char* argv[])
{

	float m0; // Central CMP
	float om; // CMP axis origin
	float dm; // CMP sampling
	int nm; // Number of CMP's
	float oh; // Offset axis origin
	float dh; // Offset sampling
	int nh; // Number of Offsets
	int nt; // Number of time samples
	float ot; // Time axis origin
	float dt; // Time sampling
	bool verb; // Key to turn On/Off verbose mode
	float v0; // Near surface velocity
	float t0; // Normal ray time travel
	float cnew[3]; // Temporary parameters vector - actual iteration
	float c[3]; // Temporary parameters vector - last iteration
	float ***otm; // Optimized parameters
	float otrn=0., otrnip=0., otbeta=0.; // Optimized parameters
	float otsemb=0.; // Optimized semblance
	float deltaE, PM; // Metrópolis criteria
	float Em0=0; // Best semblance
	float u; // Random number
	float ***t; // Data cube A(m,h,t)
	int q, i, k, l; // loop counter
	float semb; // Semblance - actual iteration
	float RN, RNIP, BETA; // CRS parameters
	float semb0; // Initial semblance value
	float c0; // VFSA damping factor
	float temp0; // initial VFSA temperature
	float temp; // VFSA temperature
	int repeat; // Perform VFSA optimization more than once
	float om0; // m0's axis origin
	float dm0; // m0's sampling
	int nm0; // Number of m0's
	float ot0; // t0's axis origin
	float dt0; // t0's sampling
	int nt0; // Number of t0's
	float rnip_max, rnip_min; // RNIP limits
	float rn_max, rn_min; // RN limits
	float beta_max, beta_min; // BETA limits
	float **rnmaxvec=NULL, **rnminvec=NULL; // RN limits vector
	float **rnipmaxvec=NULL, **rnipminvec=NULL; // RNIP limits vector
	float **betamaxvec=NULL, **betaminvec=NULL; // BETA limits vector
	bool varlim; // y, variable search window to parameters
	int ntest1, ntest2; // Limits vector files dimension
	int itmax; // Maximum VFSA iterations
	float t0i, t0f;
	int ki, kf;
	bool interval;
	bool half; // Use half-offset instead of offset
	bool get_convergence_graph; // Option to generate a convergence graph

	/* RSF files I/O */  
	sf_file in; /* Seismic data cube A(m,h,t) */
	sf_file rnminfile=NULL, rnmaxfile=NULL, rnipminfile=NULL, rnipmaxfile=NULL, betaminfile=NULL, betamaxfile=NULL;
	sf_file parameters=NULL;
	sf_file out; /* RN, RNIP, BETA, Semblance, C0, Temp0, t0, m0 */
	sf_file outgraph=NULL; /* Convergence graph */

	/* RSF files axis */
	sf_axis ax,ay,az;

	sf_init(argc,argv); 

	in = sf_input("in");
	out = sf_output("out");

	if(!sf_getbool("getgraph",&get_convergence_graph)) get_convergence_graph=false;
	/* Generate convergence graph (y/n) */

	if(!sf_getbool("half",&half)) half=false;
	/* Use half-offset coordinates (y/n) */

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
	/* initial VFSA temperature */

	if(!sf_getint("repeat",&repeat)) repeat=1;
	/* How many times to perform VFSA global optimization */

	if(!sf_getbool("varlim",&varlim)) varlim=false;
	/* Set 'y' to use variable window search for parameters */

	if(!sf_getfloat("rnmax",&rn_max)) rn_max=5;
	/* RN maximum value */

	if(!sf_getfloat("rnmin",&rn_min)) rn_min=0;
	/* RN minimum value */

	if(!sf_getfloat("rnipmax",&rnip_max)) rnip_max=4.;
	/* RNIP maximum value */

	if(!sf_getfloat("rnipmin",&rnip_min)) rnip_min=0;
	/* RNIP minimum value */

	if(!sf_getfloat("betamax",&beta_max)) beta_max=1;
	/* BETA maximun value (radians) */

	if(!sf_getfloat("betamin",&beta_min)) beta_min=-1;
	/* BETA minimum value (radians) */

	if(!sf_getint("itmax",&itmax)) itmax=5000;
	/* Max VFSA iterations */

	if(!sf_getfloat("t0i",&t0i)) t0i=0.;
	/* Initial t0 */

	if(!sf_getfloat("t0f",&t0f)) t0f=nt0*dt0+ot0;
	/* final t0 */

	if(!sf_getbool("interval",&interval)) interval=false;

	if(get_convergence_graph){
		if(!repeatOptionEqual1ForGetConvergenceGraphTrue(get_convergence_graph,repeat))
			sf_error("The repeat parameter should be equal 1 for getgraph=y!");
		prepareConvergenceGraphFile(outgraph = sf_output("convgraph"),get_convergence_graph,repeat,itmax);
	}

	if(varlim){
		rnmaxfile = sf_input("rnmaxfile");
		if(!sf_histint(rnmaxfile,"n1",&ntest1)) sf_error("No n1= in rnmaxfile");
		if(!sf_histint(rnmaxfile,"n2",&ntest2)) sf_error("No n2= in rnmaxfile");
		if(ntest1!=nt0) sf_error("n1 should be equal to nt0 in rnmaxfile");
		if(ntest2!=nm0) sf_error("n2 should be equal to nm0 in rnmaxfile");
		rnmaxvec = sf_floatalloc2(nt0,nm0);
		sf_floatread(rnmaxvec[0],nt0*nm0,rnmaxfile);
		sf_fileclose(rnmaxfile);

		rnminfile = sf_input("rnminfile");
		if(!sf_histint(rnminfile,"n1",&ntest1)) sf_error("No n1= in rnminfile");
		if(!sf_histint(rnminfile,"n2",&ntest2)) sf_error("No n2= in rnminfile");
		if(ntest1!=nt0) sf_error("n1 should be equal to nt0 in rnminfile");
		if(ntest2!=nm0) sf_error("n2 should be equal to nm0 in rnminfile");
		rnminvec = sf_floatalloc2(nt0,nm0);
		sf_floatread(rnminvec[0],nt0*nm0,rnminfile);
		sf_fileclose(rnminfile);

		rnipmaxfile = sf_input("rnipmaxfile");
		if(!sf_histint(rnipmaxfile,"n1",&ntest1)) sf_error("No n1= in rnipmaxfile");
		if(!sf_histint(rnipmaxfile,"n2",&ntest2)) sf_error("No n2= in rnipmaxfile");
		if(ntest1!=nt0) sf_error("n2 should be equal to nt0 in rnipmaxfile");
		if(ntest2!=nm0) sf_error("n2 should be equal to nm0 in rnipmaxfile");
		rnipmaxvec = sf_floatalloc2(nt0,nm0);
		sf_floatread(rnipmaxvec[0],nt0*nm0,rnipmaxfile);
		sf_fileclose(rnipmaxfile);

		rnipminfile = sf_input("rnipminfile");
		if(!sf_histint(rnipminfile,"n1",&ntest1)) sf_error("No n1= in rnipminfile");
		if(!sf_histint(rnipminfile,"n2",&ntest2)) sf_error("No n2= in rnipminfile");
		if(ntest1!=nt0) sf_error("n1 should be equal to nt0 in ripminfile");
		if(ntest2!=nm0) sf_error("n2 should be equal to nm0 in ripminfile");
		rnipminvec = sf_floatalloc2(nt0,nm0);
		sf_floatread(rnipminvec[0],nt0*nm0,rnipminfile);
		sf_fileclose(rnipminfile);

		betamaxfile = sf_input("betamaxfile");
		if(!sf_histint(betamaxfile,"n1",&ntest1)) sf_error("No n1= in betamaxfile");
		if(!sf_histint(betamaxfile,"n2",&ntest2)) sf_error("No n2= in betamaxfile");
		if(ntest1!=nt0) sf_error("n1 should be equal to nt0 in betamaxfile");
		if(ntest2!=nm0) sf_error("n2 should be equal to nm0 in betamaxfile");
		betamaxvec = sf_floatalloc2(nt0,nm0);
		sf_floatread(betamaxvec[0],nt0*nm0,betamaxfile);
		sf_fileclose(betamaxfile);

		betaminfile = sf_input("betaminfile");
		if(!sf_histint(betaminfile,"n1",&ntest1)) sf_error("No n1= in betaminfile");
		if(!sf_histint(betaminfile,"n2",&ntest2)) sf_error("No n2= in betaminfile");
		if(ntest1!=nt0) sf_error("n1 should be equal to nt0 in betaminfile");
		if(ntest2!=nm0) sf_error("n2 should be equal to nm0 in betaminfile");
		betaminvec = sf_floatalloc2(nt0,nm0);
		sf_floatread(betaminvec[0],nt0*nm0,betaminfile);
		sf_fileclose(betaminfile);
	}

	if (!sf_histint(in,"n1",&nt)) sf_error("No n1= in input");
	if (!sf_histfloat(in,"d1",&dt)) sf_error("No d1= in input");
	if (!sf_histfloat(in,"o1",&ot)) sf_error("No o1= in input");
	if (!sf_histint(in,"n2",&nh)) sf_error("No n2= in input");
	if (!sf_histfloat(in,"d2",&dh)) sf_error("No d2= in input");
	if (!sf_histfloat(in,"o2",&oh)) sf_error("No o2= in input");
	if (!sf_histint(in,"n3",&nm)) sf_error("No n3= in input");
	if (!sf_histfloat(in,"d3",&dm)) sf_error("No d3= in input");
	if (!sf_histfloat(in,"o3",&om)) sf_error("No o3= in input");

	if(! sf_getbool("verb",&verb)) verb=false;
	/* y: active mode; n: quiet mode */

	if (verb) {

		sf_warning("Active mode on!!!");
		sf_warning("Input file parameters: ");
		sf_warning("n1=%i d1=%f o1=%f",nt,dt,ot);
		sf_warning("n2=%i d2=%f o2=%f",nh,dh,oh);
		sf_warning("n3=%i d3=%f o3=%f",nm,dm,om);
		sf_warning("Command line parameters: "); 
		sf_warning("c0=%f temp0=%f v0=%f itmax=%d repeat=%d",c0,temp0,v0,itmax,repeat);
		sf_warning("nt0=%d ot0=%f dt0=%f (%f s)",nt0,ot0,dt0,dt0*nt0);
		sf_warning("nm0=%d om0=%f dm0=%f (%f km)",nm0,om0,dm0,dm0*nm0);
		if(varlim){
			sf_warning("Parameters search window: varlim=y");
			sf_warning("FROM FILES");
		}else{
			sf_warning("Parameters search window: varlim=n");
			sf_warning("%f < RN < %f",rn_min,rn_max);
			sf_warning("%f < RNIP < %f",rnip_min,rnip_max);
			sf_warning("%f < BETA < %f",beta_min,beta_max);
		}
	}
	
	/* Read seismic data cube */
	t=sf_floatalloc3(nt,nh,nm);
	sf_floatread(t[0][0],nm*nh*nt,in);

	sf_fileclose(in);

	semb0=0;

	/* Save optimized parameters in vector */
	otm=sf_floatalloc3(nt0,nm0,4);
	if(interval){
		parameters=sf_input("parameters");
		sf_floatread(otm[0][0],nt0*nm0*4,parameters);
		ki=(int)((t0i-ot0)/dt0);
		kf=(int)((t0f-ot0)/dt0);
	}else{
		ki=0;
		kf=nt0;
	}

	for(l=0;l<nm0;l++){
		
		m0 = l*dm0+om0;

		for(k=ki;k<kf;k++){

				t0 = k*dt0+ot0;

				srand(time(NULL)*t0*m0);

				if(varlim){
					rn_max=rnmaxvec[l][k];
					rn_min=rnminvec[l][k];
					rnip_max=rnipmaxvec[l][k];
					rnip_min=rnipminvec[l][k];
					beta_max=betamaxvec[l][k];
					beta_min=betaminvec[l][k];
				}
				if(interval){
					c[0] = otm[0][l][k];
					c[1] = otm[1][l][k];
					c[2] = otm[2][l][k];
					cnew[0] = c[0];
					cnew[1] = c[1];
					cnew[2] = c[2];
					otrn=c[0];
					otrnip=c[1];
					otbeta=c[2];
					semb0=otm[3][l][k];
					otsemb = semb0;
				}else{
					c[0] = (rn_max+rn_min)/2.;
					c[0] += getRandomNumberBetween0and1()*c[0];
					c[1] = (rnip_max+rnip_min)/2.;
					c[1] += getRandomNumberBetween0and1()*c[1];
					c[2] = (beta_max+beta_min)/2.;
					c[2] += getRandomNumberBetween0and1()*c[2];
					cnew[0] = c[0];
					cnew[1] = c[1];
					cnew[2] = c[2];
					otrn=c[0];
					otrnip=c[1];
					otbeta=c[2];
					semb0=semblance(m0,dm,om,oh,dh,dt,nt,t0,v0,c[0],c[1],c[2],t,half);
					otsemb = semb0;
				}

				#pragma omp parallel for \
				private(i,q,temp,c,RN,RNIP,BETA,cnew,semb) \
				shared(semb0,otsemb,otrn,otrnip,otbeta) \
				schedule(dynamic)
				for(i=0;i<repeat;i++){

					for (q=0; q <itmax; q++){
							
						/* calculate VFSA temperature for this iteration */
						temp=getVfsaIterationTemperature(q,c0,temp0);
										
						/* parameter disturbance */
						disturbParameters(temp,cnew,c,rn_max,
						rn_min,rnip_max,rnip_min,beta_max,beta_min);

						RN = cnew[0];
						RNIP = cnew[1];
						BETA = cnew[2];

						semb=0;
					
						semb=semblance(m0,dm,om,oh,dh,dt,nt,t0,v0,RN,RNIP,BETA,t,half);

							/* VFSA parameters convergence condition */		
							if(fabs(semb) > fabs(semb0) ){
								#pragma omp critical(evaluate_best_semblance)
								{
								otsemb = semb;
								otrn = RN;
								otrnip = RNIP;
								otbeta = BETA;
								semb0 = semb;
								} /* Critical section parallelization */
							}

							/* VFSA parameters update condition */
							deltaE = semb - Em0;
							
							/* Metrópolis criteria */
							PM = expf(-deltaE/temp);
							
							if (deltaE<=0){
								c[0] = cnew[0];
								c[1] = cnew[1];
								c[2] = cnew[2];
								Em0 = semb;
							} else {
								u=getRandomNumberBetween0and1();
								if (PM > u){
									c[0] = cnew[0];
									c[1] = cnew[1];
									c[2] = cnew[2];
									Em0 = semb;
								}	
							}	
						
							if(get_convergence_graph) sf_floatwrite(&otsemb,1,outgraph);

					} /* loop over iterations */

				} /* repeat VFSA global optimization */
				otm[0][l][k] = otrn;
				otm[1][l][k] = otrnip;
				otm[2][l][k] = otbeta;
				otm[3][l][k] = otsemb;
			
				/* Show optimized parameters on screen before save them */
				if(verb) sf_warning("(%d/%d): RN=%.3f, RNIP=%.3f, BETA=%.3f, SEMB=%.3f ;",l*(kf-ki)+k+1,nm0*(kf-ki),otrn,otrnip,otbeta,otsemb);

			} /* Loop over t0s */
	} /* Loop over m0s */

	free(t);

	/* axis = sf_maxa(n,o,d)*/
	ax = sf_maxa(nt0, ot0, dt0);
	ay = sf_maxa(nm0, om0, dm0);
	az = sf_maxa(4, 0, 1);

	/* sf_oaxa(file, axis, axis index) */
	sf_oaxa(out,ax,1);
	sf_oaxa(out,ay,2);
	sf_oaxa(out,az,3);
	sf_putstring(out,"label1","t0");
	sf_putstring(out,"unit1","s");
	sf_putstring(out,"label2","m0");
	sf_putstring(out,"unit2","km");
	sf_putstring(out,"label3","parameters");
	sf_putstring(out,"unit3","RN, RNIP, BETA, Semblance");
	sf_putfloat(out,"C0",c0);
	sf_putfloat(out,"temp0",temp0);
	sf_floatwrite(otm[0][0],4*nt0*nm0,out);
}
