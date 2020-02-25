#include "BpTree.h"

using namespace std;

BpTree::BpTree(unsigned nodeSize) {

	root = new Node(nodeSize, NULL, NULL, NULL, true);
	height = 1;

}

BpTree::BpTree(BpTree* tree) {

	root = new Node(tree->getRoot(), NULL);
	fixAdjacentNodePointers(root);
	height = tree->getHeight();

}

BpTree::~BpTree() {
	delete root;
}

bool BpTree::operator==(BpTree* tree) {
	if (this->getHeight() == tree->getHeight() &&
		*(this->getRoot()) == *(tree->getRoot())) {
		return true;
	} else {
		return false;
	}
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

int BpTree::getHeight() {
	return height;
}

Node* BpTree::getRoot() {
	return root;
}

void BpTree::fixAdjacentNodePointers(Node* root) {
	root->fixAdjacentNodePointers(root);
}