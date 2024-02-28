/*
* Test_bug_issue_52.c (C)
* 
* Purpose: Test of bug related in issue 52.
* 
* Site: https://www.geofisicando.com
* 
* Programmer: Rodolfo A C Neves (Dirack) 27/02/2024
* 
* Email: rodolfo_profissional@hotmail.com
* 
* License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.
*/

#include "Unity/unity.h"
#include "../vfsacrsnh_lib.h"
#include <rsf.h>
#define ITMAX 100
#define hMAX 50
#define mMAX 50

void setUp(){};

void tearDown(){};

void testFunctionValueInsideBoundaries(){
/*< Function to assure that value is inside boundaries >*/
	TEST_ASSERT_TRUE(checkValueInsideBoundaries(1.0,0.,2.0));	
	TEST_ASSERT_FALSE(checkValueInsideBoundaries(1.0,1.1,2.0));	
	TEST_ASSERT_FALSE(checkValueInsideBoundaries(1.0,0.,0.5));	
}

void checkValidBoundariesAndApertureForCMP(){
/*< Function to assure that m0 values are inside boundaries to avoid segmentation fault errors >*/

	char strerr[100];
	int nm=401;
	float dm=0.025, om=0.;
	int nm0=1;
	float dm0=1., om0=3;
	int aperture=50;

	TEST_ASSERT_TRUE(validBoundariesAndApertureForCMP(nm0, om0, dm0, aperture, nm, om, dm, strerr));

	om0=1.;
	TEST_ASSERT_FALSE(validBoundariesAndApertureForCMP(nm0, om0, dm0, aperture, nm, om, dm, strerr));
	TEST_ASSERT_EQUAL_STRING("Invalid boundaries for CMP m0min=-0.250000 m0max=2.250000. Please check aperture!",strerr);

	om0=9.;
	TEST_ASSERT_FALSE(validBoundariesAndApertureForCMP(nm0, om0, dm0, aperture, nm, om, dm, strerr));
	TEST_ASSERT_EQUAL_STRING("Invalid boundaries for CMP m0min=7.750000 m0max=10.250000. Please check aperture!",strerr);
}

void checkValidBoundariesAndApertureForOffset(){
/*< Function to assure that Offset values are inside boundaries to avoid segmentation fault errors >*/

        char strerr[100];
        int nh=161;
        float dh=0.0125, oh=0.;
        int aperture=50;

        TEST_ASSERT_TRUE(validBoundariesAndApertureForOffset(nh, oh, dh, aperture, strerr));

        oh=0.;
	aperture=162;
        TEST_ASSERT_FALSE(validBoundariesAndApertureForOffset(nh, oh, dh, aperture, strerr));
        TEST_ASSERT_EQUAL_STRING("Invalid boundaries for Offset hmin=0.000000 hmax=2.025000. Please check aperture!",strerr);

}

void checkValidBoundariesAndApertureForT0(){
/*< Function to assure that t0 values are inside boundaries to avoid segmentation fault errors >*/

        char strerr[100];
        int nt=1001;
        float dt=0.004, ot=0.;
        int nt0=1;
        float dt0=1., ot0=3;

        TEST_ASSERT_TRUE(validBoundariesAndApertureForT0(nt0, ot0, dt0, nt, ot, dt, strerr));

        ot0=4.004;
        TEST_ASSERT_FALSE(validBoundariesAndApertureForT0(nt0, ot0, dt0, nt, ot, dt, strerr));
        TEST_ASSERT_EQUAL_STRING("Invalid boundaries for time t0 t0min=4.004000 t0max=4.004000. Please check aperture!",strerr);

        ot0=-0.004;
        TEST_ASSERT_FALSE(validBoundariesAndApertureForT0(nt0, ot0, dt0, nt, ot, dt, strerr));
        TEST_ASSERT_EQUAL_STRING("Invalid boundaries for time t0 t0min=-0.004000 t0max=-0.004000. Please check aperture!",strerr);
}


int main(int argc, char* argv[]){

	UNITY_BEGIN();
	RUN_TEST(testFunctionValueInsideBoundaries);
	RUN_TEST(checkValidBoundariesAndApertureForCMP);
	RUN_TEST(checkValidBoundariesAndApertureForOffset);
	RUN_TEST(checkValidBoundariesAndApertureForT0);

	return UNITY_END();
}
