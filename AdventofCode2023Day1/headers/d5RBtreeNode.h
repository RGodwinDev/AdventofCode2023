#pragma once
#include<string>
#include<tuple>

class d5RBtreeNode
{
private:
	
public:
	d5RBtreeNode* parent = nullptr;
	d5RBtreeNode* left;
	d5RBtreeNode* right;
	std::string color;
	std::tuple<__int64, __int64, __int64> vals;


	//node constructor
	d5RBtreeNode(d5RBtreeNode* parent, bool is_red, d5RBtreeNode* left, d5RBtreeNode* right, std::tuple<__int64, __int64, __int64> vals);

	bool areBothChildrenBlack();

	//gets the # of nodes in the subtree O(n)
	int count();

	d5RBtreeNode* getGrandparent();
	d5RBtreeNode* getPredecessor();
	d5RBtreeNode* getSibling();
	d5RBtreeNode* getUncle();

	//true if the color is black
	bool isBlack();

	//true if the color is red
	bool isRed();

	//replaces the current child with the new child
	//return true if successful
	bool replaceChild(d5RBtreeNode* curChild, d5RBtreeNode* newChild);

	//sets child as left or right child or this node
	//returns true if successful
	bool setChild(std::string leftright, d5RBtreeNode* child);

};

