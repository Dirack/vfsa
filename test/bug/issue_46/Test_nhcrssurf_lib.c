/*
* Test_nhcrssurf.c (C)
* 
* Purpose: Test for bug related on issue 46.
* 
* Site: https://www.geofisicando.com
* 
* Programmer: Rodolfo A C Neves (Dirack) 21/02/2024
* 
* Email: rodolfo_profissional@hotmail.com
* 
* License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.
*/

#include "Unity/unity.h"
#include "../nhcrssurf_lib.h"
#include <rsf.h>

void setUp(){};

void tearDown(){};

void test_parametersFileDimensionN1EqualOrMajorThan3_check(){
/*< Parameters check should return true for correct value of n1 dimension. It should be equal or major than 3 >*/
	TEST_ASSERT_TRUE(parametersFileDimensionN1EqualOrMajorThan3(3));
	TEST_ASSERT_TRUE(parametersFileDimensionN1EqualOrMajorThan3(5));
	TEST_ASSERT_FALSE(parametersFileDimensionN1EqualOrMajorThan3(1));
	TEST_ASSERT_FALSE(parametersFileDimensionN1EqualOrMajorThan3(0));
	TEST_ASSERT_FALSE(parametersFileDimensionN1EqualOrMajorThan3(-1));
}

void test_checkParametersFileDimensionN1(){
/*< Check parameters file dimension n1. It should be defined and equal or major than 3 >*/

	sf_file par;
	int n1;
	char strerr[100];

	par = sf_output("dummyfile");

	TEST_ASSERT_FALSE(checkParametersFileDimensionN1(par,&n1,strerr));
	TEST_ASSERT_EQUAL_STRING("No n1= in parameters input",strerr);

	sf_putint(par,"n1",3);
	TEST_ASSERT_TRUE(checkParametersFileDimensionN1(par,&n1,strerr));
	TEST_ASSERT_EQUAL(3,n1);

	sf_putint(par,"n1",5);
	TEST_ASSERT_TRUE(checkParametersFileDimensionN1(par,&n1,strerr));
	TEST_ASSERT_EQUAL(5,n1);

	sf_putint(par,"n1",7);
	TEST_ASSERT_TRUE(checkParametersFileDimensionN1(par,&n1,strerr));
	TEST_ASSERT_EQUAL(7,n1);

	sf_putint(par,"n1",1);
	TEST_ASSERT_FALSE(checkParametersFileDimensionN1(par,&n1,strerr));
	TEST_ASSERT_EQUAL_STRING("Parameters file should have at least 3 parameters but n1=1",strerr);
	sf_putint(par,"n1",0);
	TEST_ASSERT_FALSE(checkParametersFileDimensionN1(par,&n1,strerr));
	TEST_ASSERT_EQUAL_STRING("Parameters file should have at least 3 parameters but n1=0",strerr);
	sf_putint(par,"n1",-1);
	TEST_ASSERT_FALSE(checkParametersFileDimensionN1(par,&n1,strerr));
	TEST_ASSERT_EQUAL_STRING("Parameters file should have at least 3 parameters but n1=-1",strerr);

}

void test_checkIfParametersAreTooSmall(){
/*< Parameters should not be too small to avoid zero division error >*/

	float v0=1.5, RN=1., RNIP=2.;
	char strerr[100];
	char tmp[100];

	TEST_ASSERT_TRUE(checkIfParametersAreTooSmall(v0,RN,RNIP,strerr));

	v0=0.;
	TEST_ASSERT_FALSE(checkIfParametersAreTooSmall(v0,RN,RNIP,strerr));
	sprintf(tmp,"One of the following parameters is too small v0=%f RN=%f RNIP=%f",v0,RN,RNIP);
	TEST_ASSERT_EQUAL_STRING(tmp,strerr);


	v0=1.5; RN=0.0001;
	TEST_ASSERT_FALSE(checkIfParametersAreTooSmall(v0,RN,RNIP,strerr));
	sprintf(tmp,"One of the following parameters is too small v0=%f RN=%f RNIP=%f",v0,RN,RNIP);
	TEST_ASSERT_EQUAL_STRING(tmp,strerr);

	v0=1.5; RN=1.; RNIP=0.0001;
	TEST_ASSERT_FALSE(checkIfParametersAreTooSmall(v0,RN,RNIP,strerr));
	sprintf(tmp,"One of the following parameters is too small v0=%f RN=%f RNIP=%f",v0,RN,RNIP);
	TEST_ASSERT_EQUAL_STRING(tmp,strerr);

}

int main(int argc, char* argv[]){

	sf_init(argc,argv);

	UNITY_BEGIN();
	RUN_TEST(test_parametersFileDimensionN1EqualOrMajorThan3_check);
	RUN_TEST(test_checkParametersFileDimensionN1);
	RUN_TEST(test_checkIfParametersAreTooSmall);

	return UNITY_END();
}
