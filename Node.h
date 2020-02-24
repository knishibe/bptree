#ifndef NODE_H
#define NODE_H

#include <iostream> 
#include <vector>

using namespace std;

//struct AdjacentNodes {
//	Node* leftNode;
//	Node* rightNode;
//};

class Node {

	private:

		struct AdjacentNodes {
			Node* leftNode;
			Node* rightNode;
		};

		unsigned nodeSize = 0;
		bool isLeafNode;
		Node* parent;
		vector<int> elements;
		vector<Node*> pointers;
		AdjacentNodes adjacentNodes;
		vector<string> values;


	public:

		// constructor
		Node(int nodeSize, Node* parent, Node* left, Node* right, bool isLeaf);

		// destructor
		~Node();

		// overloaded operators
		bool operator==(Node* node);

		// main functions
		Node* insert(int key, Node* pointer);
		Node* insert(int key, string value);
		void insert(int key, Node* left, Node* right); // for special case: new internal node
		Node* remove(int key);
		Node* remove(Node* pointer);
		Node* find(int key);
		void printKeys();
		void printValues();

		// helper functions
		void removePointer(Node* pointer);
		void insertFront(int key, Node* pointer);
		void swapKey(int oldKey, int newKey);
		Node* getLeftMostNode(int level);
		vector<Node*> getRow();
		bool checkNodeSize();

		// getters
		Node* getParent();
		bool getIsLeafNode();
		unsigned getNodeSize();
		vector<int> getElements();
		vector<Node*> getPointers();
		string getValue(int key);
		vector<string> getValues();
		AdjacentNodes getAdjacentNodes();

		// setters
		void setParent(Node* node);
		void setIsLeafNode(bool isLeafNode);
		void setNodeSize(unsigned nodeSize);
		void setElements(vector<int> elements);
		void setPointers(vector<Node*> pointers);
		void setValues(vector<string> values);
		void setAdjacentNodes(AdjacentNodes adjacentNodes);
		

};

#endif
