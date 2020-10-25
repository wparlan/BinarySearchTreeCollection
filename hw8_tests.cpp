/*
Name: William Parlan
Assignment: Homework 3
Description: File containing test cases for the BSTCollection class.
All 6 member functions are tested along with some fringe cases.
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <gtest/gtest.h>
#include "bst_collection.h"

using namespace std;

// Test 1: Test Size Function
TEST(BasicCollectionTest,CorrectSize){
	BSTCollection <string,double> c ;
	ASSERT_EQ(c.size(), 0);
	c.insert("a", 10.0);
	ASSERT_EQ(c.size(), 1);
	c.insert("b", 20.0);
	ASSERT_EQ(c.size(), 2);
}

// Test 2
TEST(BasicCollectionTest, InsertAndFind) {
	BSTCollection<string,double> c;
	double v;
	ASSERT_EQ(c.find("a", v), false);
	c.insert("a", 10.0);
	
	ASSERT_EQ(c.find("a", v), true);
	ASSERT_EQ(v, 10.0);
	ASSERT_EQ(c.find("b", v), false);
	c.insert("b", 20.0);
	ASSERT_EQ(c.find("b",v), true);
	ASSERT_EQ(v, 20.0);
}

// Test 3: Test Remove
// TEST(BasicCollectionTest, RemoveElems){
	// BSTCollection<string,double> c ;
	// c.insert("a", 10.0);
	// c.insert("b", 20.0);
	// c.insert("c", 30.0);
	// double v;
	// c.remove("a");
	// ASSERT_EQ(c.find("a", v), false);
	// c.remove("b");
	// ASSERT_EQ(c.find("b", v), false);
	// c.remove("c");
	// ASSERT_EQ(c.find("c", v), false);
	// ASSERT_EQ(c.size(), 0);
// }

// Test 4: Test find for a single value
TEST(BasicCollectionTest, GetKeys){
	BSTCollection <string,double> c;
	c.insert ("a", 10.0);
	c.insert ("b", 20.0);
	c.insert ("c", 30.0);
	vector<string>ks;
	c.keys(ks);
	vector<string>::iterator iter;
	iter = find(ks.begin(), ks.end(), "a");
	ASSERT_NE(iter, ks.end());
	iter = find(ks.begin(), ks.end(), "b");
	ASSERT_NE(iter, ks.end());
	iter = find(ks.begin(), ks.end(), "c");
	ASSERT_NE(iter, ks.end());
	iter = find(ks.begin(), ks.end(), "d");
	ASSERT_EQ(iter, ks.end());
}

// Test 5: Test overloaded find for a range of keys
TEST (BasicCollectionTest, GetKeyRange){
	BSTCollection<string,double> c;
	c.insert("a", 10.0);
	c.insert("b", 20.0);
	c.insert("c", 30.0);
	c.insert("d", 40.0);
	c.insert("e", 50.0);
	vector<string> ks;
	c.find("b", "d", ks);
	vector<string>::iterator iter;
	iter = find(ks.begin(), ks.end(), "b");
	ASSERT_NE(iter, ks.end());
	iter = find(ks.begin(), ks.end(), "c");
	ASSERT_NE(iter,ks.end());
	iter = find(ks.begin(), ks.end(), "d");
	ASSERT_NE(iter, ks.end());
	iter = find(ks.begin(), ks.end(), "a");
	ASSERT_EQ(iter, ks.end());
	iter = find(ks.begin(), ks.end(), "e");
	ASSERT_EQ(iter, ks.end());
}

// Test 6: Test sort function
TEST(BasicCollectionTest, KeySort){
	BSTCollection<string,double> c;
	c.insert("a", 10.0);
	c.insert("e", 50.0);
	c.insert("c", 30.0);
	c.insert("b", 20.0);
	c.insert("d", 40.0);
	vector<string>sorted_ks;
	c.sort(sorted_ks);
	//check if sort order
	// cout<<"6\n\n\n";
	// for(int i = 0; i < int(sorted_ks.size()); ++ i)
		// cout<<i<<" "<<sorted_ks[i]<<endl;
	for(int i = 0; i < int(sorted_ks.size()) - 1; ++ i)
		ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}

//Test 7: Test what happens if the range of keys is invalid, should have an empty vector
TEST(BasicCollectionTest, KeyBoundCheck){
	BSTCollection<string,double> c;
	c.insert("b", 20.0);
	c.insert("a", 10.0);
	c.insert("e", 50.0);
	c.insert("c", 30.0);
	c.insert("d", 40.0);
	vector<string> ks;
	c.find("d", "b", ks);
	ASSERT_EQ(ks.size(),0);
	vector<string>::iterator iter;
	iter = find(ks.begin(), ks.end(), "a");
	ASSERT_EQ(iter, ks.end());
	iter = find(ks.begin(), ks.end(), "b");
	ASSERT_EQ(iter, ks.end());
	iter = find(ks.begin(), ks.end(), "c");
	ASSERT_EQ(iter,ks.end());
	

	c.find("c","f",ks);
	ASSERT_EQ(ks.size(),3);
	iter = find(ks.begin(), ks.end(), "a");
	ASSERT_EQ(iter, ks.end());
	iter = find(ks.begin(), ks.end(), "b");
	ASSERT_EQ(iter, ks.end());
	iter = find(ks.begin(), ks.end(), "c");
	ASSERT_NE(iter, ks.end());
	iter = find(ks.begin(), ks.end(), "d");
	ASSERT_NE(iter, ks.end());
	iter = find(ks.begin(), ks.end(), "e");
	ASSERT_NE(iter, ks.end());
}

// Test 8: Empty Collection Tests, Edge Case testing
TEST(BasicCollectionTest, EmptyCollection){
	BSTCollection<string,double> c;
	vector<string>ks;
	vector<string>sorted_ks;
	double h;
	// c.remove("a");
	c.find("b",h);
	c.find("c","e",ks);
	ASSERT_EQ(c.size(),0);
	c.sort(sorted_ks);
	// check if sort order
	for(int i = 0; i < int(sorted_ks.size()) - 1; ++ i)
		ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
	double v;
	double v2 = v;
	ASSERT_FALSE(c.find("a",v));
	ASSERT_EQ(v,v2);
}

//Test 9: Identical Bounds Collection Tests
TEST(BasicCollectionTest, IdenticalBounds){
	BSTCollection<string,double> c;
	c.insert("a", 10.0);
	c.insert("b", 20.0);
	c.insert("c", 30.0);
	c.insert("d", 40.0);
	c.insert("e", 50.0);
	vector<string> ks;
	c.find("b", "b", ks);
	vector<string>::iterator iter;
	iter = find(ks.begin(), ks.end(), "b");
	ASSERT_NE(iter, ks.end());
	iter = find(ks.begin(), ks.end(), "a");
	ASSERT_EQ(iter, ks.end());
	iter = find(ks.begin(), ks.end(), "c");
	ASSERT_EQ(iter,ks.end());
}

//Test 10: copy constructor test and equals operator tests
TEST(BasicCollectionTest, Constructors){
	BSTCollection<string,double> c1;
	c1.insert("a", 10.0);
	c1.insert("b", 20.0);
	c1.insert("c", 30.0);
	c1.insert("d", 40.0);
	c1.insert("e", 50.0);
	BSTCollection<string,double> c2;
	c2.insert("a", 10.0);
	BSTCollection<string,double> c3 = c1;
	ASSERT_EQ(c3.size(),c1.size());
	c1 = c2;
	ASSERT_EQ(c1.size(),c2.size());
}
//Test 11, constructors with empty lists
TEST(BasicCollectionTest, EmptyConstructors){
	BSTCollection<string,double> c1;
	BSTCollection<string,double> c2;
	BSTCollection<string,double> c3;
	ASSERT_EQ(c1.size(), c2.size());
	c1 = c2;
	ASSERT_EQ(c1.size(),c2.size());
	c1.insert("a", 10.0);
	c1.insert("b", 20.0);
	c1.insert("c", 30.0);
	c1.insert("d", 40.0);
	c1.insert("e", 50.0);
	c2 = c1;
	ASSERT_EQ(c1.size(), c2.size());
	c1 = c3;
	ASSERT_EQ(c1.size(),c3.size());
}



int main (int argc , char ** argv ){
	testing::InitGoogleTest(& argc, argv);
	return RUN_ALL_TESTS ();
}
