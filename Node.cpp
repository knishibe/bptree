#include "Node.h"

using namespace std;

/*---------------------- Constructor ----------------------*/
Node::Node(int nodeSize, Node* parent, Node* left, Node* right, bool isLeaf) {
	this->nodeSize = nodeSize;
	this->parent = parent;
	this->isLeafNode = isLeaf;
	this->adjacentNodes.leftNode = left;
	this->adjacentNodes.rightNode = right;
}

/*---------------------- Destructor ----------------------*/
Node::~Node() {
	for (unsigned i = 0; i < (int)pointers.size(); i++) {
		delete pointers[i];
	}
}

/*---------------------- Overloaded Operators ----------------------*/
bool Node::operator==(Node* node) {
	if (this->parent == node->getParent() &&
		this->isLeafNode == node->getIsLeafNode() &&
		this->nodeSize == node->getNodeSize() &&
		this->pointers == node->getPointers() &&
		this->values == node->getValues() &&
		this->adjacentNodes.rightNode == node->getAdjacentNodes().rightNode &&
		this->adjacentNodes.leftNode == node->getAdjacentNodes().leftNode) {
		return true;
	} else {
		return false;
	}
}


/*---------------------- Main Functions ----------------------*/

Node* Node::remove(int key) {

	bool removed = false;
	int swappedKey = key;

	for (unsigned i = 0; i < elements.size() && i < nodeSize; i++) {
		if (key == elements[i]) {
			elements.erase(elements.begin() + i);
			values.erase(values.begin() + i);
			if (i == 0 && elements.size() > 0) {
				parent->swapKey(key, elements[0]);
				swappedKey = elements[0];
			}
			removed = true;
			break;
		}
	}

	if (removed == false) {
		elements.pop_back();
		values.pop_back();
		removed = true;
	}

	if (elements.size() < nodeSize / 2 + nodeSize % 2) {
		vector<int> keys;
		if (adjacentNodes.leftNode != NULL && adjacentNodes.leftNode->getParent() == parent && 
			adjacentNodes.leftNode->checkNodeSize()) {

			// redistribute from left sibling
			keys = adjacentNodes.leftNode->getElements();
			this->insert(keys[keys.size() - 1], adjacentNodes.leftNode->getValue(keys[keys.size() - 1]));
			parent->swapKey(swappedKey, keys[keys.size() - 1]);
			adjacentNodes.leftNode->remove(keys[keys.size() - 1]);

		} else if (adjacentNodes.rightNode != NULL &&adjacentNodes.rightNode->getParent() == parent && 
			adjacentNodes.rightNode->checkNodeSize()) {

			// redistribute from right sibling
			keys = adjacentNodes.rightNode->getElements();
			this->insert(keys[0], adjacentNodes.rightNode->getValue(keys[0]));
			adjacentNodes.rightNode->remove(keys[0]);
			keys = adjacentNodes.rightNode->getElements();
			parent->swapKey(swappedKey, keys[0]);

		} else {

			//coalece


		}
		
	}

	return this;
}

Node* Node::insert(int key, Node* pointer) {

	bool inserted = false;
	for (unsigned i = 0; i < elements.size() && i < nodeSize; i++) {
		if (key < elements[i]) {
			elements.insert(elements.begin() + i, key);
			pointers.insert(pointers.begin() + i + 1, pointer);
			inserted = true;
			break;
		}
	}

	if (inserted == false) {
		elements.push_back(key);
		pointers.push_back(pointer);
		inserted = true;
	}

	if (elements.size() > nodeSize) {
		Node* newNode = new Node(nodeSize, parent, this, adjacentNodes.rightNode, false);
		int half = nodeSize / 2;
		int halfVal = elements[half];

		newNode->insert(elements[half + 1], pointers[(half + 1)], pointers[(half + 2)]); 
		pointers[half + 1]->setParent(newNode);
		pointers[half + 2]->setParent(newNode);

		for (unsigned i = half +2; i < elements.size(); i++) {
			newNode->insert(elements[i], pointers[i + 1]); 
			pointers[i + 1]->setParent(newNode);
		}

		adjacentNodes.rightNode = newNode; 

		elements.erase(elements.begin() + half, elements.end());
		pointers.erase(pointers.begin() + half + 1, pointers.end());

		if (parent != NULL) {
			return parent->insert(halfVal, newNode);
		} else {
			// create a new root
			parent = new Node(nodeSize, NULL, NULL, NULL, false);
			parent->insert(halfVal, this, newNode);
			return parent;
		}

	}
	return NULL;

}

// only used when a new node is created
void Node::insert(int key, Node* pointer1, Node* pointer2) {

	elements.push_back(key);
	pointers.push_back(pointer1);
	pointers.push_back(pointer2);

}

Node* Node::insert(int key, string value) {
	bool inserted = false;
	for (unsigned i = 0; i < elements.size() && i < nodeSize; i++) {
		if (key < elements[i]) {
			elements.insert(elements.begin() + i, key);
			values.insert(values.begin() + i, value);
			inserted = true;
			break;
		}
	}

	if (inserted == false) {
		elements.push_back(key);
		values.push_back(value);
		inserted = true;
	}

	if (elements.size() > nodeSize) {
		Node* newNode = new Node(nodeSize, parent, this, adjacentNodes.rightNode, true);
		int half = elements.size()/ 2 + elements.size() % 2;
		int halfVal = elements[half];
		for (unsigned i = half; i < elements.size(); i++) {
			newNode->insert(elements[i], values[i]);
		}

		if (adjacentNodes.rightNode != NULL) {
			AdjacentNodes newNodes = adjacentNodes.rightNode->getAdjacentNodes();
			newNodes.leftNode = newNode;
			adjacentNodes.rightNode->setAdjacentNodes(newNodes);
		}
		adjacentNodes.rightNode = newNode;

		elements.erase(elements.begin() + half, elements.end());
		values.erase(values.begin() + half, values.end());

		if (parent != NULL) {
			return parent->insert(halfVal, newNode);
		}
		else {
			// create a new root
			parent = new Node(nodeSize, NULL, NULL, NULL, false);
			newNode->setParent(parent);
			parent->insert(halfVal, this, newNode);
			return parent;
		}

	}
	return NULL;
}


Node* Node::find(int key) {
	if (isLeafNode) {
		return this;
	} else {
		for (int i = 0; i < (int)elements.size(); i++) {
			if (key < elements[i]) {
				return pointers[i]->find(key);
			}
		}
		return pointers[elements.size()]->find(key);
	}

}

string Node::getValue(int key) {
	for (int i = 0; i < (int)elements.size(); i++) {
		if (elements[i] == key) {
			return values[i];
		}
	}
	return "";
} 

void Node::printKeys() {

	cout << "[";
	for (unsigned i = 0; i < elements.size()-1; i++) {
		cout << elements[i] << ", ";
	}

	cout << elements[elements.size() - 1] << "] ";

	if (adjacentNodes.rightNode != NULL) {
		adjacentNodes.rightNode->printKeys();
	}

}

void Node::printValues() {
	if (isLeafNode) {

		for (unsigned i = 0; i < elements.size(); i++) {
			cout << values[i] << "\n";
		}

		if (adjacentNodes.rightNode!= NULL) {
			adjacentNodes.rightNode->printValues();
		}
	}
}

Node* Node::getLeftMostNode(int level) {
	if (level == 0) {
		return this;
	} else {
		return pointers[0]->getLeftMostNode(level - 1);
	}
}

vector<Node*> Node::getRow() {

	vector<Node*> row;
	vector<Node*> temp;

	row.push_back(this);

	if (adjacentNodes.rightNode == NULL) {
		return row;
	} else {
		temp = adjacentNodes.rightNode->getRow();
		row.insert(row.end(), temp.begin(), temp.end());
		return row;
	}
}

void Node::swapKey(int oldKey, int newKey) {
	for (unsigned i = 0; i < elements.size(); i++) {
		if (elements[i] == oldKey) {
			elements.erase(elements.begin() + i);
			elements.insert(elements.begin() + i, newKey);
		}
	}
}

bool Node::checkNodeSize() {
	if (isLeafNode && elements.size() > nodeSize / 2 + nodeSize % 2) {
		return true;
	} else if (!isLeafNode && elements.size() > nodeSize / 2) {
		return true;
	} else {
		return false;
	}
}

/*---------------------- Getters ----------------------*/

Node* Node::getParent() {
	return parent;
}

bool Node::getIsLeafNode() {
	return isLeafNode;
}

unsigned Node::getNodeSize() {
	return nodeSize;
}

vector<int> Node::getElements() {
	return elements;
}

vector<Node*> Node::getPointers() {
	return pointers;
}

vector<string> Node::getValues() {
	return values;
}

Node::AdjacentNodes Node::getAdjacentNodes() {
	return adjacentNodes;
}


/*---------------------- Setters ----------------------*/

void Node::setParent(Node* node) {
	parent = node;
}

void Node::setIsLeafNode(bool isLeafNode) {
	this->isLeafNode = isLeafNode;
}

void Node::setNodeSize(unsigned nodeSize) {
	this->nodeSize = nodeSize;
}

void Node::setElements(vector<int> elements) {
	this->elements = elements;
}

void Node::setPointers(vector<Node*> pointers) {
	this->pointers = pointers;
}

void Node::setValues(vector<string> values) {
	this->values = values;
}

void Node::setAdjacentNodes(AdjacentNodes adjacentNodes) {
	this->adjacentNodes.leftNode = adjacentNodes.leftNode;
	this->adjacentNodes.rightNode = adjacentNodes.rightNode;
}
