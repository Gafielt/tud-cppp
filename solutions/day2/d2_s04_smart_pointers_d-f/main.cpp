#include "TreeNode.hpp"
#include <iostream>
using namespace std;

int main() {
	TreeNodePtr node = TreeNode::createNode(1, TreeNode::createNode(2), TreeNode::createNode(3));
	cout << "node created" << endl;
	
	node = TreeNode::createNode(4, TreeNode::createNode(5), TreeNode::createNode(6));
	cout << "exiting program" << endl;
}
