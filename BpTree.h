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

		BpTree(unsigned nodeSize);
		~BpTree();
		bool insert(int key, string value);
		bool remove(int key);
		void printKeys(); 
		void printValues();
		string find(int key);
		void GetRowTest();


};

#endif