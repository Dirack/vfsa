/*
* Test_vfsacrsnh.c (C)
* 
* Purpose: Test of the functions in the library of the program 'Mvfsacrsnh.c'.
* 
* Site: https://www.geofisicando.com
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
#define ITMAX 100
#define hMAX 50
#define mMAX 50

/* Seimic datacube parameters to be used in tests */
float*** t; // it stores seismic datacube
float **returnedValues; // nonHyperbolicCRSapp returned values
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
	TEST_IGNORE_MESSAGE("TODO");
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
	int half=1;

	nonHyperbolicCRSapp(returnedValues,mMAX,hMAX,m0,dm,om,dh,oh,t0,v0,RN,RNIP,BETA,half);

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
	int half=1;

	for(i=0;i<100;i++){
		semb=semblance(m0,dm,om,oh,dh,dt,nt,t0,v0,RN,RNIP,BETA,t,mMAX,hMAX,half);
		TEST_ASSERT(semb>=0.0 && semb <= 1.0);
	}
}

void repeat_should_be_1_when_get_convercence_graph_true(){
/*< Repeat option should be equal 1 (use one thread) when get convergence graph option is true
 * This is done to avoid multiple theads during convergence graph generation
 * >*/

	TEST_ASSERT(repeatOptionEqual1ForGetConvergenceGraphTrue(true,1));
	TEST_ASSERT_FALSE(repeatOptionEqual1ForGetConvergenceGraphTrue(true,10));

}

void convergence_graph_file_preparation(){
/*< Test convergence graph file preparation. Test if the parameters set is correct >*/
	sf_file outgraph=NULL;
	int itmax = 500, repeat = 1;
	bool get_convergence_graph=true;
	int n1;
	float d1;
	float o1;
	char label[50];

	prepareConvergenceGraphFile(outgraph = sf_output("convgraph"),get_convergence_graph,repeat,itmax);
	TEST_ASSERT_TRUE(sf_histint(outgraph,"n1",&n1));
	TEST_ASSERT_EQUAL(n1,itmax);
	TEST_ASSERT_TRUE(sf_histfloat(outgraph,"d1",&d1));
	TEST_ASSERT_FLOAT_WITHIN(0.001,d1,1.0);
	TEST_ASSERT_TRUE(sf_histfloat(outgraph,"o1",&o1));
	TEST_ASSERT_FLOAT_WITHIN(0.001,o1,0.0);

	strcpy(label,sf_histstring(outgraph,"label1"));
	TEST_ASSERT_EQUAL_STRING("Iteration",label);
	strcpy(label,sf_histstring(outgraph,"label2"));
	TEST_ASSERT_EQUAL_STRING("Semblance",label);
}

void check_parameters_file_dimensions(){
/*< Test of the function to check parameters file dimension n1 and n2
 *  Dimensions should be defined and n1=nt0, n2=nm0
 * >*/

	int nt0=10, nm0=10;
	char* strerr = (char*) malloc(50*sizeof(char));
	sf_file parametersFiles = NULL;
	parametersFiles = sf_input("dummyheader");

        TEST_ASSERT_FALSE(checkParametersFileDimensionReturnStrError(parametersFiles,nt0,nm0,strerr));
	TEST_ASSERT_EQUAL_STRING("No n1= in file",strerr);

	sf_putint(parametersFiles,"n1",5);
        TEST_ASSERT_FALSE(checkParametersFileDimensionReturnStrError(parametersFiles,nt0,nm0,strerr));
	TEST_ASSERT_EQUAL_STRING("No n2= in file",strerr);

	sf_putint(parametersFiles,"n2",5);
        TEST_ASSERT_FALSE(checkParametersFileDimensionReturnStrError(parametersFiles,nt0,nm0,strerr));
	TEST_ASSERT_EQUAL_STRING("n1 should be equal to nt0 in file",strerr);

	sf_putint(parametersFiles,"n1",10);
        TEST_ASSERT_FALSE(checkParametersFileDimensionReturnStrError(parametersFiles,nt0,nm0,strerr));
	TEST_ASSERT_EQUAL_STRING("n2 should be equal to nm0 in file",strerr);

	sf_putint(parametersFiles,"n2",10);
        TEST_ASSERT_TRUE(checkParametersFileDimensionReturnStrError(parametersFiles,nt0,nm0,strerr));
}

void check_load_data_cube_file_dimensions(){
/*< Test of the function to check and load a data cube file >*/
	int n1, n2, n3;
	float o1, o2, o3;
	float d1, d2, d3;
	char* strerr = (char*) malloc(50*sizeof(char));
	sf_file in = NULL;
	in = sf_input("dummyheader");

        TEST_ASSERT_FALSE(checkAndLoadDataCubeDimensionsReturnStrError(in,&n1,&o1,&d1,&n2,&o2,&d2,&n3,&o3,&d3,strerr));
	TEST_ASSERT_EQUAL_STRING("No n1= in input",strerr);

	sf_putint(in,"n1",5);
        checkAndLoadDataCubeDimensionsReturnStrError(in,&n1,&o1,&d1,&n2,&o2,&d2,&n3,&o3,&d3,strerr);
	TEST_ASSERT_EQUAL(n1,5);

        TEST_ASSERT_FALSE(checkAndLoadDataCubeDimensionsReturnStrError(in,&n1,&o1,&d1,&n2,&o2,&d2,&n3,&o3,&d3,strerr));
	TEST_ASSERT_EQUAL_STRING("No o1= in input",strerr);

	sf_putfloat(in,"o1",0.);
        checkAndLoadDataCubeDimensionsReturnStrError(in,&n1,&o1,&d1,&n2,&o2,&d2,&n3,&o3,&d3,strerr);
	TEST_ASSERT_FLOAT_WITHIN(0.001,o1,0.);

        TEST_ASSERT_FALSE(checkAndLoadDataCubeDimensionsReturnStrError(in,&n1,&o1,&d1,&n2,&o2,&d2,&n3,&o3,&d3,strerr));
	TEST_ASSERT_EQUAL_STRING("No d1= in input",strerr);

	sf_putfloat(in,"d1",1.);
        checkAndLoadDataCubeDimensionsReturnStrError(in,&n1,&o1,&d1,&n2,&o2,&d2,&n3,&o3,&d3,strerr);
	TEST_ASSERT_FLOAT_WITHIN(0.001,d1,1.);

	TEST_ASSERT_FALSE(checkAndLoadDataCubeDimensionsReturnStrError(in,&n1,&o1,&d1,&n2,&o2,&d2,&n3,&o3,&d3,strerr));
	TEST_ASSERT_EQUAL_STRING("No n2= in input",strerr);

	sf_putint(in,"n2",5);
        checkAndLoadDataCubeDimensionsReturnStrError(in,&n1,&o1,&d1,&n2,&o2,&d2,&n3,&o3,&d3,strerr);
	TEST_ASSERT_EQUAL(n2,5);

        TEST_ASSERT_FALSE(checkAndLoadDataCubeDimensionsReturnStrError(in,&n1,&o1,&d1,&n2,&o2,&d2,&n3,&o3,&d3,strerr));
	TEST_ASSERT_EQUAL_STRING("No o2= in input",strerr);

	sf_putfloat(in,"o2",0.);
        checkAndLoadDataCubeDimensionsReturnStrError(in,&n1,&o1,&d1,&n2,&o2,&d2,&n3,&o3,&d3,strerr);
	TEST_ASSERT_FLOAT_WITHIN(0.001,o2,0.);

        TEST_ASSERT_FALSE(checkAndLoadDataCubeDimensionsReturnStrError(in,&n1,&o1,&d1,&n2,&o2,&d2,&n3,&o3,&d3,strerr));
	TEST_ASSERT_EQUAL_STRING("No d2= in input",strerr);

	sf_putfloat(in,"d2",1.);
        checkAndLoadDataCubeDimensionsReturnStrError(in,&n1,&o1,&d1,&n2,&o2,&d2,&n3,&o3,&d3,strerr);
	TEST_ASSERT_FLOAT_WITHIN(0.001,d2,1.);

	TEST_ASSERT_FALSE(checkAndLoadDataCubeDimensionsReturnStrError(in,&n1,&o1,&d1,&n2,&o2,&d2,&n3,&o3,&d3,strerr));
	TEST_ASSERT_EQUAL_STRING("No n3= in input",strerr);

	sf_putint(in,"n3",5);
        checkAndLoadDataCubeDimensionsReturnStrError(in,&n1,&o1,&d1,&n2,&o2,&d2,&n3,&o3,&d3,strerr);
	TEST_ASSERT_EQUAL(n3,5);

        TEST_ASSERT_FALSE(checkAndLoadDataCubeDimensionsReturnStrError(in,&n1,&o1,&d1,&n2,&o2,&d2,&n3,&o3,&d3,strerr));
	TEST_ASSERT_EQUAL_STRING("No o3= in input",strerr);

	sf_putfloat(in,"o3",0.);
        checkAndLoadDataCubeDimensionsReturnStrError(in,&n1,&o1,&d1,&n2,&o2,&d2,&n3,&o3,&d3,strerr);
	TEST_ASSERT_FLOAT_WITHIN(0.001,o3,0.);

        TEST_ASSERT_FALSE(checkAndLoadDataCubeDimensionsReturnStrError(in,&n1,&o1,&d1,&n2,&o2,&d2,&n3,&o3,&d3,strerr));
	TEST_ASSERT_EQUAL_STRING("No d3= in input",strerr);

	sf_putfloat(in,"d3",1.);
        checkAndLoadDataCubeDimensionsReturnStrError(in,&n1,&o1,&d1,&n2,&o2,&d2,&n3,&o3,&d3,strerr);
	TEST_ASSERT_FLOAT_WITHIN(0.001,d3,1.);

}

void check_load_parameters_file_data(){
/*< Check if the data is loaded correctly in parameters file vector >*/
	float** parametersFilesVectors[6];
	char* parametersFilesLabels[6] = {"rnmax","rnmin","rnipmax","rnipmin","betamax","betamin"};
	int nt0=5, nm0=5;
	int i, j, k;
	float values[6]={10.,0.,3.,1.,1,-1};

	loadParametersFilesVectors(parametersFilesVectors,parametersFilesLabels,nt0,nm0);

	for(k=0;k<6;k++){
		for(j=0;j<nm0;j++){
			for(i=0;i<nt0;i++){
				TEST_ASSERT_FLOAT_WITHIN(0.001,values[k],parametersFilesVectors[k][j][i]);
			}
		}
	}
}

void mt_convergence_graph_file_preparation(){
/*< Test multi thread convergence graph file preparation. Test if the parameters set is correct >*/
	sf_file outgraph=NULL;
	int itmax = 500, repeat = 5;
	bool get_mt_convergence_graph=true;
	int n1, n2;
	float d1, d2;
	float o1, o2;
	char label[50];

	prepareMTConvergenceGraphFile(outgraph = sf_output("mtconvgraph"),get_mt_convergence_graph,repeat,itmax);
	TEST_ASSERT_TRUE(sf_histint(outgraph,"n1",&n1));
	TEST_ASSERT_EQUAL(n1,itmax);
	TEST_ASSERT_TRUE(sf_histfloat(outgraph,"d1",&d1));
	TEST_ASSERT_FLOAT_WITHIN(0.001,d1,1.0);
	TEST_ASSERT_TRUE(sf_histfloat(outgraph,"o1",&o1));
	TEST_ASSERT_FLOAT_WITHIN(0.001,o1,0.0);

	TEST_ASSERT_TRUE(sf_histint(outgraph,"n2",&n2));
	TEST_ASSERT_EQUAL(n2,repeat);
	TEST_ASSERT_TRUE(sf_histfloat(outgraph,"d2",&d2));
	TEST_ASSERT_FLOAT_WITHIN(0.001,d1,1.0);
	TEST_ASSERT_TRUE(sf_histfloat(outgraph,"o2",&o2));
	TEST_ASSERT_FLOAT_WITHIN(0.001,o1,0.0);

	strcpy(label,sf_histstring(outgraph,"label1"));
	TEST_ASSERT_EQUAL_STRING("Iteration",label);
	strcpy(label,sf_histstring(outgraph,"label2"));
	TEST_ASSERT_EQUAL_STRING("Semblance",label);
}

int main(int argc, char* argv[]){

	/* Redirect the stdin to datacube file */
	freopen("test_data_cube/dataCube.rsf","r",stdin);

	sf_init(argc,argv); 	
	in = sf_input("in");

	/* Read seismic data cube */
	t=sf_floatalloc3(nt,nh,nm);
	sf_floatread(t[0][0],nm*nh*nt,in);

	returnedValues = sf_floatalloc2(hMAX,2*mMAX+1);

	UNITY_BEGIN();
	RUN_TEST(signal_function_return_1_for_positive_values_and_zero);
	RUN_TEST(signal_function_return_minus_1_for_negative_values);
	RUN_TEST(getRandomNumberBetween0and1_returns_float_between_0_and_1);
	RUN_TEST(curent_temperature_is_minor_equal_previous_temperature);
	RUN_TEST(if_parameters_remains_in_its_limits_after_disturbance);
	RUN_TEST(if_parameter_RN_is_major_than_RNIP);
	RUN_TEST(nonHyperbolicCRSapp_function_for_pre_calculated_values);
	RUN_TEST(semblance_return_value_between_0_1);
	RUN_TEST(repeat_should_be_1_when_get_convercence_graph_true);
	RUN_TEST(convergence_graph_file_preparation);
	RUN_TEST(check_parameters_file_dimensions);
	RUN_TEST(check_load_data_cube_file_dimensions);
	RUN_TEST(check_load_parameters_file_data);
	RUN_TEST(mt_convergence_graph_file_preparation);

	return UNITY_END();
}
