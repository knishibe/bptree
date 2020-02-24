#ifndef BPTREE_H
#define BPTREE_H

#include <iostream>
#include "Node.h"

using namespace std;

class BpTree {

	private:
		
		Node* root;
		int height;
	
	public:

		// constructors
		BpTree(unsigned nodeSize);
		BpTree(BpTree* tree);

		// destructor
		~BpTree();

		// overloaded operators
		bool operator==(BpTree* tree);

		// main functions
		bool insert(int key, string value);
		bool remove(int key);
		void printKeys(); 
		void printValues();
		string find(int key);

		// getters
		int getHeight();
		Node* getRoot();


};

#endif