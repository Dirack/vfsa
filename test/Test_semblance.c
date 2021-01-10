/*
* Test_semblance.c (C)
* 
* Purpose: Test of the semblance function
* in the library of the program 'Mvfsacrsnh.c'.
* 
* Site: https://dirack.github.io
* 
* Programer: Rodolfo A C Neves (Dirack) 09/01/2021
* 
* Email: rodolfo_profissional@hotmail.com
* 
* License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.
*/

#include "Unity/unity.h"
#include "../vfsacrsnh_lib.h"
#include <rsf.h>

float*** t;
float teta[2*mMAX+1][hMAX];
int nt=1001, nh=401, nm=161;
sf_file in;

/* Traveltime curve for CMP m0=5 */
float t51[50]={1.1001389, 1.10020828, 1.10041654, 1.10076356, 1.10124922, 1.10187316, 
  1.10263538, 1.10353553, 1.10457325, 1.10574818, 1.10705984, 1.10850775, 1.11009133, 
  1.11181021, 1.11366343, 1.11565065, 1.11777091, 1.12002361, 1.12240791, 1.12492287, 
  1.12756777, 1.13034165, 1.13324356, 1.13627243, 1.13942742, 1.14270735, 1.14611125, 
  1.14963782, 1.1532861, 1.15705502, 1.16094327, 1.16494966, 1.16907299, 1.17331195, 
  1.17766547, 1.18213212, 1.18671083, 1.19140005, 1.19619858, 1.20110524, 1.20611858, 
  1.21123731, 1.21645999, 1.22178543, 1.22721231, 1.23273921, 1.23836482, 1.24408782, 
  1.24990678, 1.25582039};

void setUp(){};

void tearDown(){};

void test_nonHyperbolicCRSapp_function_for_pre_calculated_values(){
/*< Non-hyperbolic CRS traveltime approximation >*/

	float BETA=0.,RN=3.,RNIP=1.5;
	float m0=5.0, dm=0.025, om=0.0, oh=0.0;
	float dh=0.0125, dt=0.001;
	float t0=1.1, v0=1.5;
	int h;

	nonHyperbolicCRSapp(teta,m0,dm,om,dh,oh,t0,v0,RN,RNIP,BETA);

	/* In the CMP m0 and h0, time is equal to t0 */
	TEST_ASSERT_FLOAT_WITHIN(0.001,t0,teta[51][0]);

	/* Test pre calculated values in central CMP m0 */
	for(h=0;h<50;h++){
		TEST_ASSERT_FLOAT_WITHIN(0.001,t51[h],teta[51][h]);
	}
}

void test_semblance_return_value_between_0_1(){
/*< Semblance function should return a value inside interval [0,1]>*/

	float BETA=0.,RN=3.,RNIP=1.5;
	float m0=5.0, dm=0.01, om=0.0, oh=0.0;
	float dh=0.01, dt=0.001, nt=50;
	float t0=0.3, v0=1.5;
	int i;
	float semb;

	for(i=0;i<100;i++){
		semb=semblance(m0,dm,om,oh,dh,dt,nt,t0,v0,RN,RNIP,BETA,t);
		TEST_ASSERT(semb>=0.0 && semb <= 1.0);
	}
}

int main(int argc, char* argv[]){

	/* Redirect the stdin to datacube file */
	freopen("test_data_cube/dataCube.rsf","r",stdin);

	sf_init(argc,argv); 	
	in = sf_input("in");

	/* Read seismic data cube */
	t=sf_floatalloc3(nt,nh,nm);
	sf_floatread(t[0][0],nm*nh*nt,in);

	UNITY_BEGIN();
	RUN_TEST(test_nonHyperbolicCRSapp_function_for_pre_calculated_values);
	RUN_TEST(test_semblance_return_value_between_0_1);
	return UNITY_END();
}
