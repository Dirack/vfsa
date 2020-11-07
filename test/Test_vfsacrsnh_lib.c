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

int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_signal_function);
	return UNITY_END();
}
