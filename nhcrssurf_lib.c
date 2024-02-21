/*
	 nhcrssurf_lib.c (c)
	 
	 Purpose: 'Mnhcrssurf.c' library.
	 	 
	 Site: https://www.geofisicando.com
	 
	 Programmer: Rodolfo A. C. Neves (Dirack) 21/02/2024

	 Email:  rodolfo_profissional@hotmail.com

	 License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rsf.h>
/*^*/

bool parametersFileDimensionN1EqualOrMajorThan3(int n)
/*< Check parameters file dimension. It should be equal or major than 3 samples in the following orther RN, RNIP and BETA >*/
{
        if(n < 3) return false;

	return true;
}

bool checkParametersFileDimensionN1(sf_file par, int *n1, char *strerr)
/*< Check parameters file dimension n1. It should be equal or major than 3 and n1 should be defined >*/
{
	if(!sf_histint(par,"n1",n1)){
		strcpy(strerr,"No n1= in parameters input");
		return false;
	}else if(!parametersFileDimensionN1EqualOrMajorThan3(*n1)){
		sprintf(strerr, "Parameters file should have at least 3 parameters but n1=%d", *n1);
		return false;
	}

	return true;
}

bool checkIfParametersAreTooSmall(float v0, float RN, float RNIP, char *strerr)
/*< To avoid zero division error, parameters should not be too small >*/
{
        if(fabs(v0) < 0.001 || fabs(RN) < 0.001 || fabs(RNIP) < 0.001){
                sprintf(strerr,"One of the following parameters is too small v0=%f RN=%f RNIP=%f",v0,RN,RNIP);
		return false;
	}
	return true;
}
