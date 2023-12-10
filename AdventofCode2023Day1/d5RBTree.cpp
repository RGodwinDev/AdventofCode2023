#include "./headers/d5RBTree.h"
#include <iostream>

d5RBTree::d5RBTree() {
	this->root = nullptr;
}

int d5RBTree::size() {
	if (this->root == nullptr) {
		return 0;
	}
	return this->root->count();
}



void d5RBTree::insertNode(d5RBtreeNode* node) {
	customTupleInsert(node);
	node->color = "red";
	this->insertion_balance(node);
}

void d5RBTree::customTupleInsert(d5RBtreeNode* node) {
	//write the actual insert logic here
	int stepsToPlace = 0;
	if (this->root == nullptr) {
		this->root = node;
		node->parent = nullptr;
		return;
	}

	d5RBtreeNode* cur = this->root;

	while (cur != nullptr) { //cur shouldnt become a nullptr as we'll insert left or right before then.
		stepsToPlace++;
		if (get<1>(node->vals) < get<1>(cur->vals)) {
			if (cur->left == nullptr) {
				cur->left = node;
				node->parent = cur; 
				return;
			}
			else {
				cur = cur->left;
			}
		}
		else {
			if (cur->right == nullptr) {
				cur->right = node;
				node->parent = cur;
				return;
			}
			else {
				cur = cur->right; 
			}
		}
	}	
}


//true if the node is null or black
bool d5RBTree::isNullOrBlack(d5RBtreeNode* node) {
	if (node) { return node->isBlack(); }
	return true;
}

//true if node isnt null and is red
bool d5RBTree::isNotNullAndRed(d5RBtreeNode* node) {
	if (node != nullptr) { return node->isRed(); }
	return false;
}




//searches the tree for the tuple
d5RBtreeNode* d5RBTree::search(std::tuple<__int64, __int64, __int64> key) {
	d5RBtreeNode* cur = this->root;

	while (cur) {
		if (get<1>(key) == get<1>(cur->vals)) { return cur; }
		else if (get<1>(key) < get<1>(cur->vals)) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}

	//didnt find node
	return nullptr;
}



/*
* BALANCING AFTER INSERTION
*/
void d5RBTree::insertion_balance(d5RBtreeNode* node) {
	//if node is root, color it black, we're done
	if (node->parent == nullptr) {
		node->color = "black";
		return; 
	}
	//node above is black, we're already balanced
	if (node->parent->isBlack()) { 
		return; 
	}
	//get the family together
	//if we are here, parent AND grandparent SHOULD EXIST by nature of the red/black tree
	//parent is RED grandpa color doesnt matter
	d5RBtreeNode* parent = node->parent;
	d5RBtreeNode* grandParent = node->getGrandparent();
	d5RBtreeNode* uncle = node->getUncle();
	//uncle exists and is red
	if (this->isNotNullAndRed(uncle)) {
		parent->color = "black";
		uncle->color = "black";
		grandParent->color = "red";
		this->insertion_balance(grandParent);
		return;
	}
	//uncle either doesn't exist, or is black

	if (node == parent->right && parent == grandParent->left) {
		this->rotateLeft(parent);
		node = parent;
		parent = node->parent;

	}
	else if (node == parent->left && parent == grandParent->right) {
		this->rotateRight(parent);
		node = parent;
		parent = node->parent;
	}

	parent->color = "black";
	grandParent->color = "red";


	if (node == parent->left) {
		this->rotateRight(grandParent);
	}
	else {
		this->rotateLeft(grandParent);
	}
} //end insertion_balance

void d5RBTree::rotateLeft(d5RBtreeNode* node) {
	d5RBtreeNode* rightLeftChild = node->right->left;
	if (node->parent) { node->parent->replaceChild(node, node->right); }
	else { //node is the root
		this->root = node->right;
		this->root->parent = nullptr;
	}
	node->right->setChild("left", node);
	node->setChild("right", rightLeftChild);
}

void d5RBTree::rotateRight(d5RBtreeNode* node) {
	d5RBtreeNode* leftRightChild = node->left->right;
	if (node->parent) { node->parent->replaceChild(node, node->left); }
	else { //node is the root
		this->root = node->left;
		this->root->parent = nullptr;
	}
	node->left->setChild("right", node);
	node->setChild("left", leftRightChild);
}




//removes a node with the key
bool d5RBTree::remove(std::tuple<__int64, __int64, __int64> key) {
	d5RBtreeNode* node = this->search(key);
	if (node) {
		this->removeNode(node);
		return true;
	}
	return false; //no node got removed
}

//do not call this with a nullptr
void d5RBTree::removeNode(d5RBtreeNode* node) {
	//if the node has 2 children 
	//copy the nodes predecessor to a temp value
	//recursively remove the predecessor from the tree
	//replace the nodes key with the temp value
	//return
	if (node->left != nullptr && node->right != nullptr) {
		d5RBtreeNode* predNode = node->getPredecessor();
		std::tuple<__int64, __int64, __int64> predKey = predNode->vals;
		this->removeNode(predNode);
		node->vals = predKey;
		return;
	}

	//black node, prepare the tree for removing the node
	if (node->color == "black") {
		this->prepareForRemoval(node);
	}
	
	//remove the node
	this->BSTRemove(node);
}

void d5RBTree::BSTRemove(d5RBtreeNode* node) {
	if (node) { //node exists
		if (node->left == nullptr && node->right == nullptr) { //it's a leaf
			if (node->parent == nullptr) { this->root = nullptr; } //it's also root, tree is donezo
			else if (node->parent->left == node) { node->parent->left = nullptr; } //node is parents left
			else { node->parent->right = nullptr; } //node is parents right
		}
		else if (node->right == nullptr) { //node has left child only
			if (node->parent == nullptr) { this->root = node->right; } //node is root, root = node->right
			else if (node->parent->left == node) { node->parent->left = node->left; } //node is left child
			else { node->parent->right = node->left; } //node is right child
		}
		else if (node->left == nullptr) { //node has right child only
			if (node->parent == nullptr) { this->root = node->left; } //node is root, root = node->left
			else if (node->parent->left == node) { node->parent->left = node->right; } //node is left child
			else { node->parent->right = node->right; } //node is right child
		}
		else { //node has 2 children
			d5RBtreeNode* successor = node->right;
			while (successor->left) { successor = successor->left; }
			node->vals = successor->vals;
			this->BSTRemove(successor);
		}
	}
}


void d5RBTree::rightSuccessorRemove(d5RBtreeNode* rightSuccessor) {
	if (rightSuccessor) { //node exists
		if (rightSuccessor->parent->left == rightSuccessor) {
			rightSuccessor->parent->left = rightSuccessor->right;
		}
		else {
			rightSuccessor->parent->right = rightSuccessor->right;
		}
	}
}


/*
* BALANCING FOR A REMOVAL
*/
void d5RBTree::prepareForRemoval(d5RBtreeNode* node) {
	if (this->tryCase1(node)) { return; } //node is red or the root, return
	//we know node is black
	d5RBtreeNode* sibling = node->getSibling();
	if(this->tryCase2(node, sibling)){ //sibling was red
		//we rotated in trycase2, re get sibling
		sibling = node->getSibling();
	}
	if (this->tryCase3(node, sibling)) { return; }
	if (this->tryCase4(node, sibling)) { return; }
	if (this->tryCase5(node, sibling)) {
		sibling = node->getSibling();
	}
	if (this->tryCase6(node, sibling)) {
		sibling = node->getSibling();
	}
	sibling->color = node->parent->color;
	node->parent->color = "black";
	if (node == node->parent->left) {
		sibling->right->color = "black";
		this->rotateLeft(node->parent);
	}
	else {
		sibling->left->color = "black";
		this->rotateRight(node->parent);
	}
}


/*
* ALL TRYCASE ARE HELPERS FOR prepareForRemoval
*/
bool d5RBTree::tryCase1(d5RBtreeNode* node) { return node->color == "red" || node->parent == nullptr; }
bool d5RBTree::tryCase2(d5RBtreeNode* node, d5RBtreeNode* sibling) { 
	if (sibling->color == "red") {
		//if sibling is red,
		//color parent red
		//color sibling black
		node->parent->color = "red";
		sibling->color = "black";

		//rotate at the parent
		if (node == node->parent->left) {
			this->rotateLeft(node->parent);
		}
		else { 
			this->rotateRight(node->parent);
		}
		return true;
	}
	return false; //sibling was black
}
bool d5RBTree::tryCase3(d5RBtreeNode* node, d5RBtreeNode* sibling) { 
	if (node->parent->color == "black" && sibling->areBothChildrenBlack()) {
		sibling->color = "red";
		this->prepareForRemoval(node->parent);
		return true;
	}
	return false; //parent was red or one of siblings children was red
}
bool d5RBTree::tryCase4(d5RBtreeNode* node, d5RBtreeNode* sibling) { 
	if (node->parent->color == "red" && sibling->areBothChildrenBlack()) {
		node->parent->color = "black";
		sibling->color = "red";
		return true;
	}
	return false;
}
bool d5RBTree::tryCase5(d5RBtreeNode* node, d5RBtreeNode* sibling) { 
	if (this->isNotNullAndRed(sibling->left) && 
		this->isNullOrBlack(sibling->right) && 
		node == node->parent->left) {
		sibling->color = "red";
		sibling->left->color = "black";
		this->rotateRight(sibling);
		return true;
	}
	return false;
}
bool d5RBTree::tryCase6(d5RBtreeNode* node, d5RBtreeNode* sibling) { 
	if (this->isNullOrBlack(sibling->left) &&
		this->isNotNullAndRed(sibling->right) &&
		node == node->parent->right) {
		sibling->color = "red";
		sibling->right->color = "black";
		this->rotateLeft(sibling);
		return true;
	}
	return false;
}




void d5RBTree::inOrderPrint() {
	inOrderTraversePrint(this->root);
}

void d5RBTree::inOrderTraversePrint(d5RBtreeNode* root) {
	if (!root) { return; }
	if (root->left) { 
		inOrderTraversePrint(root->left); 
	}
	std::cout << get<1>(root->vals) << std::endl;
	if (root->right) {
		inOrderTraversePrint(root->right);
	}
	return;
}

__int64 d5RBTree::part1Filter(__int64 key) {
	d5RBtreeNode* node = part1Search(key);
	//key should be >= source, + destination
	if (node) { key = (key - get<1>(node->vals)) + get<0>(node->vals); }
	return key;
}

//called by part1Filter
d5RBtreeNode* d5RBTree::part1Search(__int64 key) {
	//ez binary search on get<2>(cur->vals) (the source value)
	d5RBtreeNode* cur = this->root;

	while (cur != nullptr) {
		if (key < get<1>(cur->vals)) {
			cur = cur->left; continue;
		}
		if (key > get<1>(cur->vals) + get<2>(cur->vals)) {
			cur = cur->right; continue;
		}
		return cur;
	}
	return cur;


}