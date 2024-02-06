/*
* Test_issue_32.c (C)
* 
* Purpose: Test bug related on issue 32.
* 
* Site: https://dirack.github.io
* 
* Programmer: Rodolfo A C Neves (Dirack) 05/02/2024
* 
* Email: rodolfo_profissional@hotmail.com
* 
* License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.
*/

#include "../../Unity/unity.h"
#include "../../../vfsacrsnh_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <rsf.h>

void setUp(){};

void tearDown(){};

void getRandomNumberBetween0and1_returns_float_between_0_and_1(){
/*< Function getRandomNumberBetween0and1 should return value inside interval [0,1] >*/
	int i;
	FILE* fp;
	float v1,v2,v3;
	
	system("./call_generateRandomNumber.x teste1.bin $RANDOM");
	system("./call_generateRandomNumber.x teste2.bin $RANDOM");
	system("./call_generateRandomNumber.x teste3.bin $RANDOM");


	/* Abrir o arquivo binário */
	if((fp = fopen("teste1.bin","rb")) == NULL){
		printf("Impossível abrir o arquivo %s\n","testfile.txt");
		exit(1);
	}

	fread(&v1,sizeof(float),1,fp);

	fclose(fp);

	/* Abrir o arquivo binário */
	if((fp = fopen("teste2.bin","rb")) == NULL){
		printf("Impossível abrir o arquivo %s\n","testfile.txt");
		exit(1);
	}

	fread(&v2,sizeof(float),1,fp);

	fclose(fp);

	TEST_ASSERT_NOT_EQUAL(v1,v2);
}

int main(int argc, char* argv[]){

	UNITY_BEGIN();
	RUN_TEST(getRandomNumberBetween0and1_returns_float_between_0_and_1);

	return UNITY_END();
}
