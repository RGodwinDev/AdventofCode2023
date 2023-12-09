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


//i dont think we need a custom remove
//once node is found, its just a simple bst remove
void d5RBTree::customTupleRemove(std::tuple<__int64, __int64, __int64> key) {

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

//another remove
bool d5RBTree::remove(std::tuple<__int64, __int64, __int64> key) {
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

/*
* BALANCING FOR A REMOVAL
*/
bool d5RBTree::prepareForRemoval(d5RBtreeNode* node) {
	return false;
}

void d5RBTree::removeNode(d5RBtreeNode* node) {

}

void d5RBTree::customTupleRemoveNode(d5RBtreeNode* node) {

}

/*
* ALL TRYCASE ARE HELPERS FOR prepareForRemoval
*/
bool d5RBTree::tryCase1(d5RBtreeNode* node) { return false; }
bool d5RBTree::tryCase2(d5RBtreeNode* node, d5RBtreeNode* sibling) { return false; }
bool d5RBTree::tryCase3(d5RBtreeNode* node, d5RBtreeNode* sibling) { return false; }
bool d5RBTree::tryCase4(d5RBtreeNode* node, d5RBtreeNode* sibling) { return false; }
bool d5RBTree::tryCase5(d5RBtreeNode* node, d5RBtreeNode* sibling) { return false; }
bool d5RBTree::tryCase6(d5RBtreeNode* node, d5RBtreeNode* sibling) { return false; }




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

d5RBtreeNode* d5RBTree::part1Search(__int64 key) {
	//ez binary search on get<2>(cur->vals)
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