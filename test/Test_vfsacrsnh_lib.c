/*
* Test_vfsacrsnh.c (C)
* 
* Purpose: Test of the functions in the library of the program 'Mvfsacrsnh.c'.
* 
* Site: https://dirack.github.io
* 
* Programer: Rodolfo A C Neves (Dirack) 06/11/2020
* 
* Email: rodolfo_profissional@hotmail.com
* 
* License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.
*/

#include "Unity/unity.h"
#include "../vfsacrsnh_lib.h"
#include <rsf.h>

void setUp(){

};

void tearDown(){};

void test_signal_function(){

	TEST_ASSERT_FLOAT_WITHIN(0.01,1.0,signal(1.0));
	TEST_ASSERT_FLOAT_WITHIN(0.01,-1.0,signal(-1.0));
	TEST_ASSERT_FLOAT_WITHIN(0.001,1.0,signal(0.0));
	TEST_ASSERT_FLOAT_WITHIN(0.01,1.0,signal(5.0));
	TEST_ASSERT_FLOAT_WITHIN(0.01,-1.0,signal(-5.0));
}

void test_getRandomNumberBetween0and1(){

	int i;
	for(i=0;i<100;i++)
		TEST_ASSERT_FLOAT_WITHIN(1.0,0.0,getRandomNumberBetween0and1());
}

void test_getRandomNumberBetween0and1_positive(){

	int i;
	for(i=0;i<100;i++)	
		TEST_ASSERT_TRUE(getRandomNumberBetween0and1()>=0.0);
}

void  test_curent_temperature_is_minor_equal_previous_temperature(){
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

void test_if_parameters_remains_in_its_limits_after_disturbance(){
/*< CRS parameters (RN, RNIP,BETA) should remain in its pre defined limits >*/

	int i;
	const float c0=0.5;
	const float temp0=10.;
	float temp;
	float cnew[3], c[3]={0.,0.,0.};
	for(i=0;i<ITMAX;i++){
		temp=getVfsaIterationTemperature(i,c0,temp0);
		disturbParameters(temp,cnew,c);
		TEST_ASSERT(cnew[0]<=Rn_MAX);
		TEST_ASSERT(cnew[0]>=Rn_MIN);
		TEST_ASSERT(cnew[1]<=Rnip_MAX);
		TEST_ASSERT(cnew[1]>=Rnip_MIN);
		TEST_ASSERT(cnew[2]<=Beta_MAX);
		TEST_ASSERT(cnew[2]>=Beta_MIN);
		c[0]=cnew[0];
		c[1]=cnew[1];
		c[2]=cnew[2];
	}
}

void test_nonHyperbolicCRSapp(){
	TEST_IGNORE_MESSAGE("TODO");
}

void test_semblance(){
	TEST_IGNORE_MESSAGE("TODO");
}

int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_signal_function);
	RUN_TEST(test_getRandomNumberBetween0and1);
	RUN_TEST(test_getRandomNumberBetween0and1_positive);
	RUN_TEST(test_curent_temperature_is_minor_equal_previous_temperature);
	RUN_TEST(test_if_parameters_remains_in_its_limits_after_disturbance);
	RUN_TEST(test_nonHyperbolicCRSapp);
	RUN_TEST(test_semblance);
	return UNITY_END();
}
