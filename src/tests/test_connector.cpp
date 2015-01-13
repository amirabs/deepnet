#include "../src/Connector.h"

using namespace std;

void test_trasfer(){

	const size_t iR = 5;
	const size_t iC = 5;
	const size_t iD = 2;
	const size_t iB = 2;
	size_t ksize = 3;

	Cube<DataType_SFFloat, Layout_RCDB> input_cube(iR,iC,iD,iB);
 
	LoweringConfig * p_config;
	p_config->kernel_size = ksize;

	const size_t oR = ksize*ksize*iD;
	const size_t oC = (iR-ksize+1)*(iR-ksize+1)*iB;

	Cube<DataType_SFFloat, Layout_RCDB> output_cube(iR,iC,1,1);

	const size_t n_in = input_cube.n_elements;
	for(int i=0; i<n_in; i++){
		input_cube.p_data[i] = i;
	}

	Connector<DataType_SFFloat, Layout_RCDB, DataType_SFFloat, Layout_RCDB, Connector_Lowering_R1C1> connector(&input_cube, &output_cube, 
		p_config);
	connector.transfer(&input_cube, &output_cube);
	output_cube.logical_print();
}

int main(int argc, char * argv[]){
	test_trasfer();
}