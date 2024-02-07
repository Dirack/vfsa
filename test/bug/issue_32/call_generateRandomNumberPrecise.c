/*
* call_generateRandomNumber.c (C)
* 
* Purpose: Call function pretending to be the main program.
* 
* Site: https://dirack.github.io
* 
* Programmer: Rodolfo A C Neves (Dirack) 05/02/2024
* 
* Email: rodolfo_profissional@hotmail.com
* 
* License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.
*/

#include "../../../vfsacrsnh_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[]){

	generatePreciseRandomSeed();
	printf("%f",getRandomNumberBetween0and1());
}
