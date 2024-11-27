/*

Josemaria De Alba
A01706847

5_Arbol_Busqueda_Binaria
*/

#ifndef BST_H_
#define BST_H_
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <class T> class BST;

template <class T>
class TreeNode {
private:
	T value;
	TreeNode *left, *right;

	TreeNode<T>* succesor();

public:
	TreeNode(T);
	TreeNode(T, TreeNode<T>*, TreeNode<T>*);
	void add(T);
	bool find(T);
	int height();

	void inorder(std::string&) const;
	void preorder(std::string&) const;
	void postorder(std::string&) const;

	int byLevel(std::string &, int);
	int whatLevelamI(T);
	std::string ancestors(T, std::string&);


	friend class BST<T>;
};

template <class T>
TreeNode<T>::TreeNode(T val) : value(val), left(0), right(0) {}

template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri) : value(val), left(le), right(ri) {}

template <class T>
void TreeNode<T>::add(T val) {
	if (val < value){
		if(left != 0){
			left -> add(val);
		}else{
			left = new TreeNode<T>(val);
		}
	} else{
		if(right != 0){
			right -> add(val);
		} else{
			right = new TreeNode<T>(val);
		}
	}
}

template<class T>
int TreeNode<T>::whatLevelamI(T val){
	if(value == val){
		return 1;
	}
	else if(value < val){
		return 1+ right -> whatLevelamI(val);
	}
	else if(value > val){
		return 1+ left -> whatLevelamI(val);
	}
	return 0;
}

template <class T>
bool TreeNode<T>::find(T val) {
	if (val == value){
		return true;
	} else if (val < value) {
		return (left != 0 && left->find(val));
	} else if (val > value) {
		return (right != 0 && right->find(val));
	}
	return false;
} 

template <class T>
TreeNode<T>* TreeNode<T>::succesor() {
	TreeNode<T> *le, *ri, *parent, *child;
	le = left;
	ri = right;

	if (left == 0) {
		if (right != 0) {
			right = 0;
		}
		return ri;
	}

	if (left->right == 0) {
		left = left->left;
		le->left = 0;
		return le;
	}

	parent = left;
	child = left->right;
	while (child->right != 0) {
		parent = child;
		child = child->right;
	}
	parent->right = child->left;
	child->left = 0;
	return child;
}

template <class T>
void TreeNode<T>::inorder(std::string &aux) const {
		if (left !=0){
			left -> inorder(aux);
		}
		aux += to_string(value);
		aux += " ";
		if (right !=0){
			right ->inorder(aux);
		}
	
}

template <class T>
void TreeNode<T>::preorder(std::string &aux) const {
	aux += to_string(value);
	if (left != 0) {
		aux+= " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux += " ";
		right->preorder(aux);
	}
}

template <class T>
void TreeNode<T>::postorder(std::string &aux) const {
	if (left != 0){
		left -> postorder(aux);
	}
	if (right != 0){
		right ->postorder(aux);
	}
	aux += to_string(value);
	aux += " ";
}

template <class T>
int TreeNode<T>::byLevel(std::string &res, int level){
	if(level == 1){
		res+=to_string(value) + " ";
	}
	else{
		if(left != 0){
			left -> byLevel(res, level - 1);
		}
		if(right != 0){
			right -> byLevel(res, level - 1);
		}
	}
	return 0;
}

template <class T>
int TreeNode<T>::height(){
	int rh = 1;
	int lh = 1;
	if (right == 0 && left == 0){
		return 1;
	}
	if(right != 0){
		rh = 1 + right->height();
	}
	if(left != 0){
		lh = 1 + left->height();
	}
	if(rh > lh){
		return rh;
	}
	else{
		return lh;
	}
}

template<class T>
std::string TreeNode<T>::ancestors(T val, std::string &res){
	if(val == value){
		return res;
	}
	else{
		res += to_string(value) + " ";
		if (val < value){
			left -> ancestors(val, res);
		}
		else if (val > value){
			right -> ancestors(val, res);
		}
		return res;
	}
	return " ";
}

template <class T>
class BST{
		private:
	TreeNode<T> *root;

		public:
		BST();

		void add(T val);
		std::string visit();
		bool find(T);
		int height();
		std::string ancestors(T val);
		T whatlevelamI(T val);
};

template <class T>
BST<T>::BST() : root(0) {}


template <class T>
void BST<T>::add(T val){
	if(root != 0){
		if (!root -> find(val)){
			root -> add(val);
		}
	}else{
		root = new TreeNode<T>(val);
	}
}

template <class T>
std::string BST<T>::visit(){
	std::string aux;
	int treeH;
	int level = 1;
	aux += "[";
	root ->preorder(aux);
	if (aux.back() == ' ') {  
			aux.pop_back();
	}
	aux += "]";
	aux += "\n";
	
	aux += "[";
	root ->inorder(aux);
	if (aux.back() == ' ') { 
			aux.pop_back(); 
	}
	aux += "]";
	aux += "\n";
	
	aux += "[";
	root ->postorder(aux);
	if (aux.back() == ' ') {  
			aux.pop_back(); 
	}
	aux += "]";
	aux += "\n";
	
	aux += "[";
	treeH=root->height();
	while (level<=treeH){
			root->byLevel(aux,level);
			level +=1;
	}
	if (aux.back() == ' ') {  
			aux.pop_back(); 
	}
	aux += "]";
	return aux;
}

template <class T>
bool BST<T>::find(T val) {
	if (root != 0) {
		return root->find(val);
	} 
		else {
		return false;
	}
}

template <class T>
std::string BST<T>::ancestors(T val){
	std::string aux;
		aux += "[";
		if (root != 0 && root->find(val)) {
		root->ancestors(val, aux);
	}
		if (aux.back() == ' ') {  
				aux.pop_back();
		}
		aux += "]";

		return aux;
}

template <class T>
T BST<T>::whatlevelamI(T val){
	return root -> whatLevelamI(val);
}

template <class T>
int BST<T>::height(){
		return root->height();
}

#endif
