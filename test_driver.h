//----------------------------------------------------------------------
// AUTHOR: S. Bowers
// COURSE: CPSC 223, Fall 2019
//
// DESCRIPTION: Simple class for running key-value collection
// implementation performance tests. Instances of TestDriver take an
// input file name and a collection implementation. Tests are run
// calling the run_tests() functions. Test results are then printed to
// cout using print_results().
// ----------------------------------------------------------------------

#ifndef __TEST_DRIVER_H
#define __TEST_DRIVER_H

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include "collection.h"


template<typename K, typename V>
class TestDriver
{

public:
  TestDriver(const std::string& filename, Collection<K,V>* coll);
  void run_tests();
  void print_results() const;

private:
  // test file
  std::string filename;
  // collection under test
  Collection<K,V>* test_collection;
  // test results for printing
  int total_ins, ins_times;
  int total_rem, rem_times;
  int total_fnd, fnd_times;
  int total_rng, rng_times;
  int total_srt, srt_times;
  // helper functions to get timing results
  int timed_insert(std::fstream& in_file);
  int timed_remove(std::fstream& in_file);
  int timed_find(std::fstream& in_file);
  int timed_range(std::fstream& in_file);
  int timed_sort(std::fstream& in_file);
  // print helper function
  void print_one_result(std::string type, int total, int times) const;
};


template<typename K, typename V>
TestDriver<K,V>::TestDriver(const std::string& file, Collection<K,V>* coll)
  : filename(file), test_collection(coll)
{
}


template<typename K, typename V>
void TestDriver<K,V>::run_tests()
{			   
  // open the file
  std::fstream in_file;
  in_file.open(filename);
  // initialize data (all in microseconds)
  total_ins = 0, ins_times = 0;
  total_rem = 0, rem_times = 0;
  total_fnd = 0, fnd_times = 0;
  total_rng = 0, rng_times = 0;
  total_srt = 0, srt_times = 0;
  // run commands
  while (in_file) {
    std::string op;
    in_file >> op;
    if (op == "insert") {
      ins_times += timed_insert(in_file);
      total_ins += 1;
    }
    else if (op == "remove") {
      rem_times += timed_remove(in_file);
      total_rem += 1;
    }
    else if (op == "find") {
      fnd_times += timed_find(in_file);
      total_fnd += 1;
    }
    else if (op == "range") {
      rng_times += timed_range(in_file);
      total_rng += 1;
    }
    else if (op == "sort") {
      srt_times += timed_sort(in_file);
      total_srt += 1;
    }
  }
  in_file.close();
}


template<typename K, typename V>
void TestDriver<K,V>::
print_one_result(std::string type, int total, int times) const
{
  using namespace std;
  if (total <= 0)
    return;
  cout << "  " << type << " Calls...: " << total << endl;
  cout << "  " << type << " Time....: " << times
       << " microseconds" << endl;
  cout << "  " << type << " Average.: " << ((1.0 * times) / total)
       << " microseconds" << endl << endl;
}


template<typename K, typename V>
void TestDriver<K,V>::print_results() const
{
  using namespace std;
  cout << "TEST RESULTS:" << endl;
  cout << "=============" << endl << endl;
  print_one_result("Insert", total_ins, ins_times);
  print_one_result("Remove", total_rem, rem_times);
  print_one_result("Find", total_fnd, fnd_times);
  print_one_result("Range", total_rng, rng_times);
  print_one_result("Sort", total_srt, srt_times);
}


template<typename K, typename V>
int TestDriver<K,V>::timed_insert(std::fstream& in_file)
{
  using namespace std::chrono;
  K key;
  V val;
  in_file >> key;
  in_file >> val;
  auto start = high_resolution_clock::now();
  test_collection->insert(key, val);
  auto end = high_resolution_clock::now();
  auto time = duration_cast<microseconds>(end - start);
  int duration = time.count();
  return duration;
}


template<typename K, typename V>
int TestDriver<K,V>::timed_remove(std::fstream& in_file)
{
  using namespace std::chrono;
  K key;
  in_file >> key;
  auto start = high_resolution_clock::now();
  test_collection->remove(key);
  auto end = high_resolution_clock::now();
  auto time = duration_cast<microseconds>(end - start);
  int duration = time.count();
  return duration;
}

template<typename K, typename V>
int TestDriver<K,V>::timed_find(std::fstream& in_file)
{
  using namespace std::chrono;
  K key;
  V value;
  in_file >> key;
  auto start = high_resolution_clock::now();
  test_collection->find(key, value);
  auto end = high_resolution_clock::now();
  auto time = duration_cast<microseconds>(end - start);
  int duration = time.count();
  return duration;
}

template<typename K, typename V>
int TestDriver<K,V>::timed_range(std::fstream& in_file)
{
  using namespace std::chrono;
  K key1;
  K key2;
  in_file >> key1;
  in_file >> key2;
  std::vector<K> keys;
  auto start = high_resolution_clock::now();
  test_collection->find(key1, key2, keys);
  auto end = high_resolution_clock::now();
  auto time = duration_cast<microseconds>(end - start);
  int duration = time.count();
  return duration;
}

template<typename K, typename V>
int TestDriver<K,V>::timed_sort(std::fstream& in_file)
{
  using namespace std::chrono;
  std::vector<K> keys;
  auto start = high_resolution_clock::now();
  test_collection->sort(keys);
  auto end = high_resolution_clock::now();
  auto time = duration_cast<microseconds>(end - start);
  int duration = time.count();
  return duration;
}


#endif