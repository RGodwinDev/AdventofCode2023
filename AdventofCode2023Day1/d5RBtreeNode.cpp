#include "./headers/d5RBtreeNode.h"

d5RBtreeNode::d5RBtreeNode(d5RBtreeNode* parent, bool is_red, d5RBtreeNode* left, d5RBtreeNode* right, std::tuple<__int64, __int64, __int64> vals)
{
	if (parent != NULL) {
		this->parent = parent;
	}
	this->color = is_red ? "red" : "black";
	this->left = left;
	this->right = right;
	this->vals = std::make_tuple(get<0>(vals), get<1>(vals), get<2>(vals));
}

bool d5RBtreeNode::areBothChildrenBlack() {
	if(this->right && this->left){
		return this->right->isBlack() && this->left->isBlack();
	}
	return false;
}

bool d5RBtreeNode::isBlack() { return this->color == "black"; }
bool d5RBtreeNode::isRed() { return this->color == "red"; }

int d5RBtreeNode::count(){
	int count = 1;
	if (this->left != nullptr) { count += this->left->count(); }
	if (this->right != nullptr) { count += this->right->count(); }
	return count;
}

d5RBtreeNode* d5RBtreeNode::getGrandparent() { 
	if (this->parent == nullptr) { return nullptr; }
	return this->parent->parent;
}
d5RBtreeNode* d5RBtreeNode::getPredecessor() {
	d5RBtreeNode* node = this->left;
	while (node->right) { node = node->right; }
	return node;
}
d5RBtreeNode* d5RBtreeNode::getSibling() {
	if (this->parent) {
		if (this == this->parent->left) {
			return this->parent->right;
		}
		return this->parent->left;
	}
	return nullptr; //this node is root, siblings not possible
}

d5RBtreeNode* d5RBtreeNode::getUncle() {
	d5RBtreeNode* grandParent = this->getGrandparent();
	if (grandParent == nullptr) { return nullptr; }
	if (grandParent->left == this->parent) { return grandParent->right; }
	return grandParent->left;
}

bool d5RBtreeNode::replaceChild(d5RBtreeNode* curChild, d5RBtreeNode* newChild) {
	if (this->left == curChild) { return this->setChild("left", newChild); }
	else if (this->right == curChild) { return this->setChild("right", newChild); }
	return false;
}

bool d5RBtreeNode::setChild(std::string leftright, d5RBtreeNode* child) {
	if (leftright != "left" && leftright != "right") { return false; } //how'd we even get here then??
	if (leftright == "left") { this->left = child; }
	else { this->right = child; }
	if (child) { child->parent = this; }
	return true;
}


