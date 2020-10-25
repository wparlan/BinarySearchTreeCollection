#ifndef BST_COLLECTION_H
#define BST_COLLECTION_H

#include <vector>
#include "collection.h"


template<typename K, typename V>
class BSTCollection:public Collection<K,V>{
	public:
		// create an empty linked list
		BSTCollection();

		// copy a linked list
		BSTCollection(const BSTCollection<K,V>& rhs);

		// assign a linked list
		BSTCollection<K,V>& operator =(const BSTCollection<K,V>& rhs);

		// delete a linked list
		~BSTCollection();

		// insert a key - value pair into the collection
		void insert(const K& key, const V& val);

		// remove a key - value pair from the collection
		void remove(const K& key);

		// find the value associated with the key
		bool find(const K& key, V& val) const;

		// find the keys associated with the range
		void find(const K& k1, const K& k2, std::vector<K>& keys) const;

		// return all keys in the collection
		void keys(std::vector<K>& keys) const;

		// return collection keys in sorted order
		void sort(std::vector<K>& keys) const;

		// return the number of keys in collection
		int size() const;

		// return the height of the tree
		int height() const;

	private:
		// binary search tree node structure
		struct Node {
			K key;
			V value;
			Node* left;
			Node* right;
		};

		// root node of the search tree
		Node* root;

		// number of k-v pairs in the collection
		int collection_size;

		// helper to recursively empty search tree
		void make_empty(Node* subtree_root);

		// helper to recursively build sorted list of keys
		void inorder(const Node* subtree, std::vector<K>& keys) const;

		// helper to recursively build sorted list of keys
		void preorder(const Node* subtree, std::vector<K>& keys) const;

		// helper to recursively find range of keys
		void range_search(const Node* subtree, const K& k1, const K& k2,
		std::vector<K>& keys) const;

		// return the height of the tree rooted at subtree_root
		int height(const Node* subtree_root) const;
};


template<typename K, typename V>
BSTCollection<K,V>::BSTCollection():
collection_size(0), root(nullptr){}

template<typename K, typename V>
void BSTCollection<K,V>::make_empty(Node* subtree_root){
	// ... TODO ...
	// this is a recursive helper function
	if(!subtree_root)
		return;
	make_empty(subtree_root->left);
	make_empty(subtree_root->right);
	delete subtree_root;
	subtree_root = nullptr;
}

template<typename K, typename V>
BSTCollection<K,V>::~BSTCollection(){
	make_empty(root);
}


template<typename K, typename V>
BSTCollection<K,V>::BSTCollection(const BSTCollection<K,V>& rhs)
:collection_size(0), root(nullptr){
	*this = rhs;
}


template<typename K, typename V>
BSTCollection<K,V>& BSTCollection<K,V>::operator =(const BSTCollection<K,V>& rhs){
	if(this == &rhs)
		return* this;
	// delete current
	//std::cout<<"is make empty the problem\n";
	make_empty(root);
	//std::cout<<"no make empty isn't\n";
	collection_size = 0;
	root = nullptr;
	// build tree
	std::vector<K> ks;
	preorder(rhs.root, ks);
	// ... TODO ...
	V v;
	//std::cout<<"for loop start\n";
	//std::cout<<ks.size()<<std::endl;
	for(int i=0;i<ks.size();i++){
		//std::cout<<"begin find\n";
		rhs.find(ks[i],v);
		//std::cout<<"begin insert\n";
		insert(ks[i],v);
	}
	//std::cout<<"for loop done\n";
	return* this;
}


template<typename K, typename V>
void BSTCollection<K,V>::insert(const K& key, const V& val){
	// ... TODO ...
	// NOTE:You cannot use recursion or any helpers for insert
	//create new node with given inputs
	Node* ptr = new Node;
	ptr->key = key;
	ptr->value = val;
	ptr->left = nullptr;
	ptr->right = nullptr;
	Node* iter = root;
	collection_size++;
	if (!root) //create new root if needede
		root = ptr;
	else{
		//loop through the tree and place lef or right until the desired spot is empty
		while (iter){ 
			if (ptr->key< iter->key)
				if (!iter->left){
					iter->left = ptr;
					return;
				}
				else 
					iter = iter->left;
			else if(ptr->key > root->key)
				if (!iter->right){
					iter->right = ptr;
					return;
				}
				else 
					iter = iter->right;
		}
	}
}


template<typename K, typename V>
void BSTCollection<K,V>::remove(const K& key){
	// ... Leave empty for now ...
	// ... SAVE FOR HW 9 ...
}


template<typename K, typename V>
bool BSTCollection<K,V>::find(const K& key, V& val) const{
	// ... TODO ...
	// NOTE:You cannot use recursion or any helpers for find
	Node* iter = root;
	while(iter){
		if (key == iter->key){
			val = iter->value;
			return true;
		}
		else if (key< iter->key)
			iter = iter->left;
		else 
			iter = iter->right;
	}
	return false;
}


template<typename K, typename V> void
BSTCollection<K,V>::
range_search(const Node* subtree, const K& k1, const K& k2, std::vector<K>& ks) const{
	// ... TODO ...
	// this is a recursive helper function
	if(k1 > k2 || !root)
		return;
	if (subtree->key <= k1){
		if(subtree->key == k1)
			ks.push_back(subtree->key);
		if(subtree->right)
			range_search(subtree->right, k1, k2, ks);
		
	}
	else if(subtree->key >= k1 && subtree->key <= k2){
		ks.push_back(subtree->key);
		if(subtree->left)
			range_search(subtree->left, k1, k2, ks);
		if(subtree->right)
			range_search(subtree->right, k1, k2, ks);
		
	}
	else if(subtree->key >= k2)
		if (subtree->left){
			range_search(subtree->left, k1, k2, ks);	
		if(subtree->key == k2)
			ks.push_back(subtree->key);			
	}
}


template<typename K, typename V> void
BSTCollection<K,V>::find(const K& k1, const K& k2, std::vector<K>& ks) const{
	// defer to the range search(recursive) helper function
	range_search(root, k1, k2, ks);
}


template<typename K, typename V>
void BSTCollection<K,V>::inorder(const Node* subtree, std::vector<K>& ks) const{
	// ... TODO ...
	// this is a recursive helper function
	if(!subtree)
		return;
	inorder(subtree->left,ks);
	ks.push_back(subtree->key);
	inorder(subtree->right,ks);
	
}


template<typename K, typename V>
void BSTCollection<K,V>::preorder(const Node* subtree, std::vector<K>& ks) const{
	// ... TODO ...
	// this is a recursive helper function
	if(!subtree)
		return;
	ks.push_back(subtree->key);
	preorder(subtree->left,ks);
	preorder(subtree->right,ks);
}


template<typename K, typename V>
void BSTCollection<K,V>::keys(std::vector<K>& ks) const{
	// defer to the inorder(recursive) helper function
	inorder(root, ks);
}



template<typename K, typename V>
void BSTCollection<K,V>::sort(std::vector<K>& ks) const{
	// defer to the inorder(recursive) helper function
	inorder(root, ks);
}


template<typename K, typename V>
int BSTCollection<K,V>::size() const{
	return collection_size;
}


template<typename K, typename V>
int BSTCollection<K,V>::height(const Node* subtree_root) const{
	// ... TODO ...
	// this is a recursive helper function
}


template<typename K, typename V>
int BSTCollection<K,V>::height() const{
	// defer to the height(recursive) helper function
	return height(root);
}

#endif