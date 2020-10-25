/*
Name: William Parlan
Assignment: Homework 3
Description: Pure Virtual Parent Class for VectorCollection
*/
#ifndef COLLECTION_H
#define COLLECTION_H

#include <vector>

template <typename K, typename V>
class Collection{
	public:
		// insert a key - value pair into the collection
		virtual void insert(const K& key, const V& val) = 0;

		// remove a key - value pair from the collectiona
		virtual void remove(const K& key) = 0;

		// find and return the value associated with the key
		virtual bool find(const K& key, V& val) const = 0;

		// find and return the list of keys >= to k1 and <= to k2
		virtual void find(const K& k1, const K& k2, std::vector<K>& keys) const = 0;

		// return all of the keys in the collection
		virtual void keys(std::vector<K>&keys) const = 0;

		// return all of the keys in ascending ( sorted ) order
		virtual void sort(std::vector<K>&keys) const = 0;

		// return the number of keys in the collection
		virtual int size() const = 0;
};

#endif