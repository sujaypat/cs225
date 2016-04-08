#include "binarytree.h"

int BinaryTree::sumNodes() const {
    /* Your code here! */

	if(root == NULL)
 	   	return 0;
	else{
	 return sumHelp(root);
	}
}

int BinaryTree::sumHelp(BinaryTree::Node* croot) const{
	if(croot == NULL) return 0;

	else return croot->elem + sumHelp(croot->left) + sumHelp(croot->right);


}

