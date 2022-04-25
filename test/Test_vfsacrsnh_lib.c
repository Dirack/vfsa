/*
* Test_vfsacrsnh.c (C)
* 
* Purpose: Test of the functions in the library of the program 'Mvfsacrsnh.c'.
* 
* Site: https://dirack.github.io
* 
* Programmer: Rodolfo A C Neves (Dirack) 06/11/2020
* 
* Email: rodolfo_profissional@hotmail.com
* 
* License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.
*/

#include "Unity/unity.h"
#include "../vfsacrsnh_lib.h"
#include <rsf.h>

/* Seimic datacube parameters to be used in tests */
float*** t; // it stores seismic datacube
float returnedValues[2*mMAX+1][hMAX]; // nonHyperbolicCRSapp returned values
int nt=1001, nh=401, nm=161; // datacube dimensions
sf_file in; // datacube RSF file

/* Traveltime curve for CMP m0=5 */
float preCalculatedValues[50]=
 {1.1001389, 1.10020828, 1.10041654, 1.10076356, 1.10124922, 1.10187316, 
  1.10263538, 1.10353553, 1.10457325, 1.10574818, 1.10705984, 1.10850775, 1.11009133, 
  1.11181021, 1.11366343, 1.11565065, 1.11777091, 1.12002361, 1.12240791, 1.12492287, 
  1.12756777, 1.13034165, 1.13324356, 1.13627243, 1.13942742, 1.14270735, 1.14611125, 
  1.14963782, 1.1532861, 1.15705502, 1.16094327, 1.16494966, 1.16907299, 1.17331195, 
  1.17766547, 1.18213212, 1.18671083, 1.19140005, 1.19619858, 1.20110524, 1.20611858, 
  1.21123731, 1.21645999, 1.22178543, 1.22721231, 1.23273921, 1.23836482, 1.24408782, 
  1.24990678, 1.25582039};

void setUp(){};

void tearDown(){};

void signal_function_return_1_for_positive_values_and_zero(){
/*< Signal function returns 1 for positive and zero value input >*/
	TEST_ASSERT_FLOAT_WITHIN(0.01,1.0,signal(1.0));
	TEST_ASSERT_FLOAT_WITHIN(0.001,1.0,signal(0.0));
	TEST_ASSERT_FLOAT_WITHIN(0.01,1.0,signal(5.0));
}

void signal_function_return_minus_1_for_negative_values(){
/*< Signal function returns -1 for negative values input >*/
	TEST_ASSERT_FLOAT_WITHIN(0.01,-1.0,signal(-1.0));
	TEST_ASSERT_FLOAT_WITHIN(0.01,-1.0,signal(-5.0));
}

void getRandomNumberBetween0and1_returns_float_between_0_and_1(){
/*< Function getRandomNumberBetween0and1 should return value inside interval [0,1] >*/
	int i;
	for(i=0;i<100;i++){
		TEST_ASSERT_TRUE(getRandomNumberBetween0and1()>=0.0);
		TEST_ASSERT(getRandomNumberBetween0and1()<=1.0);
	}
}

void  curent_temperature_is_minor_equal_previous_temperature(){
/*< Temperature function should converege to zero smoothly >*/
	int i;
	const float c0=0.5;
	const float temp0=10.;
	float temp, previousValue;
	for(i=0;i<ITMAX;i++){
		temp=getVfsaIterationTemperature(i,c0,temp0);
		TEST_ASSERT(previousValue<=temp);
	}
}

void if_parameters_remains_in_its_limits_after_disturbance(){
/*< CRS parameters (RN, RNIP,BETA) should remain in its pre defined limits >*/
	int i;
	const float c0=0.5;
	const float temp0=10.;
	float temp;
	float cnew[3], c[3]={0.,0.,0.};
	float rn_max=5., rn_min=0., rnip_max=4., rnip_min=0., beta_max=1., beta_min=-1.;
	for(i=0;i<ITMAX;i++){
		temp=getVfsaIterationTemperature(i,c0,temp0);
		disturbParameters(temp,cnew,c,rn_max,rn_min,rnip_max,rnip_min,beta_max,beta_min);
		/* TODO Correct the way you threat float precision */
		TEST_ASSERT_MESSAGE(cnew[0]<=rn_max+0.00001,"RN > RN_MAX");
		TEST_ASSERT_MESSAGE(cnew[0]>=rn_min-0.00001,"RN < RN_MIN");
		TEST_ASSERT_MESSAGE(cnew[1]<=rnip_max+0.00001,"RNIP > RNIP_MAX");
		TEST_ASSERT_MESSAGE(cnew[1]>=rnip_min-0.00001,"RNIP < RNIP_MIN");
		TEST_ASSERT_MESSAGE(cnew[2]<=beta_max+0.00001,"BETA > BETA_MAX");
		TEST_ASSERT_MESSAGE(cnew[2]>=beta_min-0.00001,"BETA < BETA_MIN");
		c[0]=cnew[0];
		c[1]=cnew[1];
		c[2]=cnew[2];
	}
}

void if_parameter_RN_is_major_than_RNIP(){
/*< CRS parameter RN must be major than RNIP >*/
	int i;
	const float c0=0.5;
	const float temp0=10.;
	float temp;
	float cnew[3], c[3]={0.,0.,0.};
	float rn_max=5., rn_min=0., rnip_max=4., rnip_min=0., beta_max=1., beta_min=-1.;
	for(i=0;i<ITMAX;i++){
		temp=getVfsaIterationTemperature(i,c0,temp0);
		disturbParameters(temp,cnew,c,rn_max,rn_min,rnip_max,rnip_min,beta_max,beta_min);
		TEST_ASSERT_MESSAGE(cnew[0]>cnew[1],"Error: RN < RNIP");
		c[0]=cnew[0];
		c[1]=cnew[1];
		c[2]=cnew[2];
	}
}

void nonHyperbolicCRSapp_function_for_pre_calculated_values(){
/*< Non-hyperbolic CRS approximation function comparison with pre calculated values >*/
	float BETA=0.,RN=3.,RNIP=1.5;
	float m0=5.0, dm=0.025, om=0.0, oh=0.0;
	float dh=0.0125, dt=0.001;
	float t0=1.1, v0=1.5;
	int h;

	nonHyperbolicCRSapp(returnedValues,m0,dm,om,dh,oh,t0,v0,RN,RNIP,BETA);

	/* In the CMP m0 and h0, time is equal to t0 */
	/* CMP 51 is m0, that is the midle of CMP window */
	TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001,t0,returnedValues[mMAX+1][0],"Returned t0 is different");

	/* Test pre calculated values in central CMP m0 */
	for(h=0;h<hMAX, h>=50;h++){
		TEST_ASSERT_FLOAT_WITHIN(0.001,preCalculatedValues[h],returnedValues[mMAX+1][h]);
	}
}

void semblance_return_value_between_0_1(){
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
	RUN_TEST(signal_function_return_1_for_positive_values_and_zero);
	RUN_TEST(signal_function_return_minus_1_for_negative_values);
	RUN_TEST(getRandomNumberBetween0and1_returns_float_between_0_and_1);
	RUN_TEST(curent_temperature_is_minor_equal_previous_temperature);
	RUN_TEST(if_parameters_remains_in_its_limits_after_disturbance);
	RUN_TEST(if_parameter_RN_is_major_than_RNIP);
	RUN_TEST(nonHyperbolicCRSapp_function_for_pre_calculated_values);
	RUN_TEST(semblance_return_value_between_0_1);

	return UNITY_END();
}
