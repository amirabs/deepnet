#include "../src/Report.h"
#include <assert.h>
#include <cmath>

using namespace std;

const double EPS=1e-5;

#define show(x) std::cerr << #x << " : " << x << endl;

double bytes_to_GBytes(double b){
	return b/1024/1024/1024;
}

void test_report_get_data_GB(){
	Report r;

	r.n_floating_point_ops=1e7;
	r.n_data_read_byte=1e6;
	r.n_data_write_byte=1e8;
	r.elapsed_time=2;

	assert(abs(r.get_data_GB()-bytes_to_GBytes(r.n_data_read_byte+r.n_data_write_byte)) < EPS);
}

void test_report_get_throughput_GB(){
	Report r;

	r.n_floating_point_ops=1e7;
	r.n_data_read_byte=1e6;
	r.n_data_write_byte=1e8;	
	r.elapsed_time=2.0;

	assert(abs(r.get_throughput_GB()-bytes_to_GBytes(r.n_data_read_byte+r.n_data_write_byte)/r.elapsed_time) < EPS);
}

double test_report_get_flop_GFlop(){
	Report r;

	r.n_floating_point_ops=1e7;
	r.n_data_read_byte=1e6;
	r.n_data_write_byte=1e8;
	r.elapsed_time=2.0;

	assert(abs(r.get_flops_GFlops() - bytes_to_GBytes(r.n_floating_point_ops)));
}

void test_report_reset(){
	Report r;

	r.reset();

	assert(abs(r.t.elapsed()-0.0)<EPS);
	assert(r.n_floating_point_ops == 0);
	assert(r.n_data_read_byte == 0);
	assert(r.n_data_write_byte == 0);
	assert(r.elapsed_time == 0.0);
}

void test_report_start(){
	Report r;

	r.t.restart();

	assert(abs(r.t.elapsed()-0.0)<1e-3);
}

void test_report_end(){
	Report r;

	r.reset();

	r.n_floating_point_ops=1e7;
	r.n_data_read_byte=1e6;
	r.n_data_write_byte=1e8;
	r.elapsed_time=2.0;

	r.end(1e6, 1e8, 1e7);

	assert(r.n_floating_point_ops == 2e7);
	assert(r.n_data_read_byte == 2e6);
	assert(r.n_data_write_byte == 2e8);
	assert(abs(r.elapsed_time - 2.0)<EPS);
}

void test_report_aggregate(){
	Report r;
	Report r2;

	r.n_floating_point_ops=1e7;
	r.n_data_read_byte=1e6;
	r.n_data_write_byte=1e8;
	r.elapsed_time=2.0;

	r2.n_floating_point_ops=1e7;
	r2.n_data_read_byte=2e6;
	r2.n_data_write_byte=3e8;
	r2.elapsed_time=4.0;

	r.aggregate(r2);

	assert(r.n_floating_point_ops== 2e7);
	assert(r.n_data_read_byte == 3e6);
	assert(r.n_data_write_byte == 4e8);
	assert(abs(r.elapsed_time - 6.0)<EPS);
}

int main(int argc, const char * argv[]){
	// Test for report class, get_data_GB function
	test_report_get_data_GB();

	// Test for report class, get_throughput_GB function
	test_report_get_throughput_GB();

	// Test for report class, get_flop_GFlop function
	test_report_get_flop_GFlop();

	// Test for report class, reset function
	test_report_reset();

	// Test for report class, start function
	test_report_start();

	// Test for report class, end function
	test_report_end();

	// Test for report class, aggregate function
	test_report_aggregate();
}

	
