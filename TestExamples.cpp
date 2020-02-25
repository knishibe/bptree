#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "BpTree.h"


using namespace std;

void testInsertSlides(BpTree* tree);
void testRemoveSlides(BpTree* tree);

int main() {

	BpTree* tree = new BpTree(3);
	

	testInsertSlides(tree);
	cout << "\n\n";
	testRemoveSlides(tree);
	BpTree* tree2 = new BpTree(tree);
	cout << "\n";
	tree2->printKeys();

	cout << "\n\n\n" << (tree == tree2) << "\n\n\n";

	return 0;
}

void testInsertSlides(BpTree* tree) {

	tree->insert(2, "2");
	tree->insert(11, "11");
	tree->insert(21, "21");
	tree->insert(8, "8");
	tree->insert(64, "64");
	tree->insert(5, "5");
	tree->insert(23, "23");
	tree->insert(6, "6");
	tree->insert(19, "19");
	tree->insert(9, "9");
	tree->insert(7, "7");
	tree->insert(39, "39");
	tree->insert(45, "45");
	tree->insert(31, "31");
	tree->insert(51, "51");
	tree->insert(60, "60");
	tree->insert(93, "93");
	tree->insert(77, "77");

	cout << "Tree after insert:\n";
	tree->printKeys();


}

void testRemoveSlides(BpTree* tree) {

	tree->remove(9);
	tree->remove(6);
	tree->remove(8);
	tree->remove(23);
	tree->remove(31);

	cout << "Tree after remove:\n";
	tree->printKeys();


}