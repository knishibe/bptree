#include "BpTree.h"

using namespace std;

BpTree::BpTree(unsigned nodeSize) {

	root = new Node(nodeSize, NULL, NULL, NULL, true);
	height = 1;

}

BpTree::~BpTree() {
	//vector<Node*> tempVector;
	//Node* tempNode;
	//for (int i = 0; i < height; i++) {
	//	tempVector = (root->getLeftMostNode(height - 1))->getRow();
	//	for (int i = 0; i < tempVector.size(); i++) {
	//		tempNode = tempVector.back();
	//		tempVector.pop_back();
	//		delete tempNode;
	//	}
	//}
	delete root;
}

void BpTree::GetRowTest() {
	vector<Node*> test;
	test = (root->getLeftMostNode(height - 1))->getRow();
}

bool BpTree::insert(int key, string value) {
	Node* node = root->find(key);
	if (node->getValue(key) != "") {
		return false;
	} else {
		Node* newRoot = node->insert(key, value);
		if (newRoot != NULL) {
			root = newRoot;
			height++;
		}
		return true;
	}
}

bool BpTree::remove(int key) {
	Node* node = root->find(key);
	if (node->getValue(key) == "") {
		return false;
	} else {
		Node* newRoot = node->remove(key);
		if (newRoot != NULL) {
			delete root;
			root = newRoot;
			height--;
		}
		return true;
	}
}

void BpTree::printKeys() {
	Node* node;
	for (int i = 0; i < height; i++) {
		node = root->getLeftMostNode(i);
		node->printKeys();
		cout << "\n";
	}
}

void BpTree::printValues() {
	Node* node = root->getLeftMostNode(height - 1);
	node->printValues();
	cout << "\n";
}

string BpTree::find(int key) {
	Node* node = root->find(key);
	return node->getValue(key);
} 