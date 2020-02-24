//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//
//#include <iostream>
//#include "BpTree.h"
//
//
//using namespace std;
//
//int main() {
//
//	bool validFunction = false;
//	char continueLoop = 'y';
//	int key;
//	string value;
//	char action;
//	BpTree* tree = new BpTree(3);
//
//	while (continueLoop != 'n') {
//		cout << "Would you like to find (f), insert (i), or remove (r) a value from the tree?\n";
//		cin >> action;
//		if (action == 'f') {
//
//			cout << "please input the key of the item you would like to find\n";
//			cin >> key;
//			cout << "the value corresponding to that key is: " + tree->find(key) + "\n";
//			validFunction = true;
//
//		} else if (action == 'i') {
//
//			cout << "please input the key you would like to insert\n";
//			cin >> key;
//			cout << "please input the value you would like to insert\n";
//			cin >> value;
//			tree->insert(key, value);
//			cout << "\nValues:\n";
//			tree->printValues();
//			cout << "\nKeys:\n";
//			tree->printKeys();
//			validFunction = true;
//
//		} else if (action == 'r') {
//
//			cout << "please input the key of the item you would like to remove\n";
//			cin >> key;
//			tree->remove(key);
//			cout << "\nValues: ";
//			tree->printValues();
//			cout << "\nKeys:\n";
//			tree->printKeys();
//			validFunction = true;
//
//		}	else if (action == 't') {
//			tree->GetRowTest();
//		}	else {
//			cout << "invalid input, please try again\n";
//			validFunction = false;
//		}
//
//		if (validFunction == true) {
//			cout << "would you like to continue? (y/n)\n";
//			cin >> continueLoop;
//		}
//	}
//
//	delete tree;
//	_CrtDumpMemoryLeaks();
//	return 0;
//}