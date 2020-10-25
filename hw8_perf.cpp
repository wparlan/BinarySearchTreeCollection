/*
Name: William Parlan
Assignment: Homework 3
Description: Main function that uses test_driver and GTEST to analyze runtimes for VectorCollection
*/
#include <iostream>
#include "bst_collection.h"
#include "test_driver.h"

using namespace std;

int main(int argc, char ** argv){
	//check command - line arguments`
	if ( argc != 2) {
		cout << "usage: " << argv[0] << " filename" <<endl;
		return 1;
	}

	// run basic performance test
	BSTCollection<string,double> test_collection;
	TestDriver<string,double> driver(argv[1], &test_collection);
	driver.run_tests();
	driver.print_results();
}
