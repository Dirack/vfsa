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
	FILE* fp;
	float v;

	//printf("%d\n",atoi(argv[2]));
	srand(atoi(argv[2]));

	/* Abrir o arquivo DADOS.dat */
	if((fp = fopen(argv[1],"wb"))==NULL){
		printf("Falha ao criar o arquivo! %s\n",argv[1]);
		exit(1);
	}

	v =  getRandomNumberBetween0and1();
	if(fwrite(&v,sizeof(float),1,fp)!=1)
		fprintf(stderr,"Não foram inscritos todos os elementos!\n");

	fclose(fp);
}
