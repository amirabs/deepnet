#include "../src/Cube.h"


using namespace std;

void test_logical_print(){
	Cube<DataType_SFFloat, Layout_RCDB> cube(5,3,2,2);
	const size_t nelements = cube.n_elements;

	for(int i=0; i<nelements; i++){
		cube.p_data[i] = i;
	}

	cube.logical_print();	
}

void test_logical_get(){
	Cube<DataType_SFFloat, Layout_RCDB> cube(2,2,2,2);
	const size_t nelements = cube.n_elements;

	for(int i=0; i<nelements; i++){
		cube.p_data[i] = i;
	}

	DataType_SFFloat * dataptr;
	for(int r=0;r<cube.R;r++){
		for(int c=0;c<cube.C;c++){
			for(int d=0;d<cube.D;d++){
				for(int b=0;b<cube.B;b++){
					dataptr = cube.logical_get(r,c,d,b);	
					assert(dataptr == &cube.p_data[r + c*cube.R + d*cube.R*cube.C + b*cube.R*cube.C*cube.D]);
				}	
			}		
		}
	}

	Cube<DataType_SFFloat, Layout_BDRC> cube1(2,2,2,2);
	const size_t nelements1 = cube1.n_elements;

	for(int i=0; i<nelements1; i++){
		cube1.p_data[i] = i;
	}

	for(int r=0;r<cube1.R;r++){
		for(int c=0;c<cube1.C;c++){
			for(int d=0;d<cube1.D;d++){
				for(int b=0;b<cube1.B;b++){
					dataptr = cube1.logical_get(r,c,d,b);	
					assert(dataptr == &cube1.p_data[b + d*cube1.B + r*cube1.B*cube1.D + c*cube1.B*cube1.R*cube1.D]);
				}	
			}		
		}
	}
	
}

void test_physical_get_RCslice(){
	Cube<DataType_SFFloat, Layout_RCDB> cube(5,3,2,2);
	const size_t nelements = cube.n_elements;
	
	for(int i=0; i<nelements; i++){
		cube.p_data[i] = i;
	}	

	DataType_SFFloat * dataptr;

	for(int b=0;b<cube.B;b++){
		for(int d=0;d<cube.D;d++){
			dataptr = cube.physical_get_RCslice(d,b);	
			assert(dataptr == &cube.p_data[d*cube.R*cube.C + b*cube.R*cube.C*cube.D]);
		}	
	}

	dataptr = cube.physical_get_RCslice(0,0);
	assert(*dataptr == 0);
	dataptr = cube.physical_get_RCslice(0,1);
	assert(*dataptr == 30);
	dataptr = cube.physical_get_RCslice(1,0);
	assert(*dataptr == 15);
	dataptr = cube.physical_get_RCslice(1,1);
	assert(*dataptr == 45);
}

int main(int argc, const char * argv[]){
	// Test for logical print
	test_logical_print();

	//Test for logical_get
	test_logical_get();
	cout << "Test for Logical Get Passed" << endl;
	//Test for physical_get_RCslice
	test_physical_get_RCslice();
	cout << "Test for Physical_get_RCslice passed" << endl;
}

	
