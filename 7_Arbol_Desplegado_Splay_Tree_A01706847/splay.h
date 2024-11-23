/*

Josemaria De Alba
A01706847

Splay Tree

*/

#ifndef SPLAY_H
#define SPLAY_H
#include <string>
#include <sstream>
#include <iostream>

template <class T> class SplayTree;

template <class T>
class Node {
private:
	T value;
	Node *left, *right, *parent;

	Node<T>* succesor();
	Node<T>* rot_right(Node<T>*);
	Node<T>* rot_left(Node<T>*);

public:
	Node(T);
	Node(T, Node<T>*, Node<T>* ,Node<T>*);
	Node<T>* add(T);
	Node<T>* find(T);
	Node<T>* remove(T);
	void removeChilds();
	void inorder(std::stringstream&) const;
	void print_tree(std::stringstream&) const;
	void preorder(std::stringstream&) const;
	Node<T>* splay(Node<T>*, Node<T>*);

	friend class SplayTree<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), parent(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, Node<T> *p)
	: value(val), left(le), right(ri), parent(p) {}

template <class T>
Node<T>* Node<T>::add(T val) {
    Node<T>* root = this; 
    Node<T>* current = root; 
    Node<T>* parent = 0; 

    while (current != 0) { 
        parent = current;
        if (val < current -> value) {
            current = current -> left;
        } 
				else if (val > current -> value) {
            current = current -> right;
        } 
				else {
            return splay(root, current);
        }
    }

    Node<T>* nuevo = new Node<T>(val, 0, 0, parent);
    if (parent == 0) {
        return nuevo;
    } 
		else if (val < parent -> value) {
        parent->left = nuevo;
    } 
		else {
        parent->right = nuevo;
    }

    return splay(root, nuevo);
}

template <class T>
Node<T>* Node<T>::find(T val) {
	Node<T>* root = this; 
	if (val == value) { 
		return root;
	} 
	else if (val < value) { 
		if(left != 0){
			return left -> find(val);
		} else{
			return 0;
		}
	} 
	else {
		if(right != 0){  
			return right -> find(val);
		} 
		else{
			return 0;
		}
	}
}

template <class T>
Node<T>* Node<T>::succesor() {
	Node<T> *le, *ri;

	le = left;
	ri = right;

	if (right -> left == 0) {
		right = right -> right;
		ri -> right = 0;
		return ri;
	}

	Node<T> *parent, *child;
	parent = right;
	child = right -> left;
	while (child -> left != 0) {
		parent = child;
		child = child -> left;
	}
	parent->left = child -> right;
	child->right = 0;
	return child;
}

template <class T>
Node<T>* Node<T>::remove(T val) {
	Node<T>* root = this; 
    Node<T>* target = find(val); 
	Node<T>* child; 

    if (!target) { 
        return root;
    }

    if (target -> left and target -> right) {
    Node<T>* succesor = target -> succesor(); 
    target -> value = succesor -> value;
    target = succesor; 
	}

	
	if (target -> left) {
    	child = target -> left;
	} 
	else {
    	child = target -> right;
	}

	if (target -> parent) {
		if (target -> parent -> left == target) { 
			target -> parent -> left = child;
		} 
		else { 
			target -> parent -> right = child;
		}
	}

	if (child != 0) {
		child -> parent = target -> parent;
	}

	Node<T>* parent = target -> parent;
	delete target;

	if (parent != 0) {
		return splay(root, parent);
	} 
	else if (child != 0) {
		return splay(root, child);
	}
	
	return root;
}

template <class T>
void Node<T>::removeChilds() {
	if (left != 0) {
		left -> removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right -> removeChilds();
		delete right;
		right = 0;
	}
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* x){
	Node<T> *y = x -> left;
	x -> left = y -> right;
	if( y-> right)
		y -> right -> parent = x;
	y -> right = x;
	y -> parent = x -> parent;
	x -> parent = y;
	if(y -> parent){
		if(y->parent -> left and y -> parent -> left -> value == x -> value){
			y->parent -> left = y;
		}
		else{
			y->parent -> right = y;
		}
	}
	return y;
}

template <class T>
Node<T>* Node<T>::rot_left(Node<T>* x){
	Node<T> *y = x -> right;
	x -> right = y -> left;
	if(y -> left)
		y -> left -> parent = x;
	y -> left = x;
	y -> parent = x -> parent;
	x -> parent = y;
	if(y -> parent){
		if(y -> parent -> left and y -> parent -> left -> value == x -> value)
			y -> parent -> left = y;
		else
			y -> parent -> right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
	while(x->parent != 0){

		if(x -> parent -> value == root -> value){
			if(x -> parent -> left and x -> parent -> left -> value == x -> value){
				rot_right(x -> parent);
			}
			else{
				rot_left(x -> parent);
			}
		}
		else{
			Node<T>*p = x -> parent; 
			Node<T>*g = p -> parent; 
			if(p->left and g -> left and
				x -> value == p -> left -> value and p -> value == g -> left -> value){
				rot_right(g);
				rot_right(p);
			}
			else if(p -> right and g -> right and
				x -> value == p -> right -> value and p -> value == g -> right -> value){
				rot_left(g);
				rot_left(p);
			}
			else	if(p -> left and g -> right and
				x -> value == p -> left -> value and p -> value == g -> right -> value){
				rot_right(p);
				rot_left(g);
			}
			else{
				rot_left(p);
				rot_right(g);
			}
		}
	}
	return x;
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left -> inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right -> inorder(aux);
	}
}

template <class T>
void Node<T>::print_tree(std::stringstream &aux) const {
	if (parent != 0){
		aux << "\n node " << value;
		aux << " parent " << parent -> value;
	}
	else{
		aux << "\n root " << value;
	}
	if (left != 0){
		aux << " left " << left -> value;
	}
	if (right != 0){
		aux << " right " << right -> value;
	}
	aux << "\n";

	if (left != 0) {
		left -> print_tree(aux);
	}
	if (right != 0) {
		right -> print_tree(aux);
	}
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left -> preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right -> preorder(aux);
	}
}

template <class T>
class SplayTree {
private:
	Node<T> *root;

public:
	SplayTree();
	~SplayTree();
	bool empty() const;
	void add(T);
	bool find(T);
	void remove(T);
	void removeAll();
	std::string inorder() const;
	std::string print_tree() const;
	std::string preorder() const;
};

template <class T>
SplayTree<T>::SplayTree() : root(0) {}

template <class T>
SplayTree<T>::~SplayTree() {
	removeAll();
}

template <class T>
bool SplayTree<T>::empty() const {
	return (root == 0);
}

template<class T>
void SplayTree<T>::add(T val) {
	if (root != 0) {
			Node<T>* added = root -> add(val);
			root = root -> splay(root,added);
	} else {
		root = new Node<T>(val);
	}
}

template <class T>
void SplayTree<T>::remove(T val) {
	if (root != 0) {
		if (val == root->value) {
			Node<T> *succ = root->succesor();
			if (succ != 0) {
					succ -> left = root -> left;
					succ -> right = root -> right;
					succ -> parent = 0;
					if(succ -> left){
						succ -> left->parent = succ;
					}
					if(succ -> right){
						succ -> right -> parent = succ;
					}
			}
			delete root;
			root = succ;
		} else {
			Node<T>* p = root -> remove(val);
			root = root -> splay(root,p);
		}
	}
}

template <class T>
void SplayTree<T>::removeAll() {
	if (root != 0) {
		root -> removeChilds();
	}
	delete root;
	root = 0;
}

template <class T>
bool SplayTree<T>::find(T val){
	if (root != 0) {
		Node<T>* found = root -> find(val);
		root = root -> splay(root,found);
		return (root -> value == val);
	} 
	else {
		return false;
	}
}

template <class T>
std::string SplayTree<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root -> inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string SplayTree<T>::print_tree() const {
	std::stringstream aux;

	aux << "\n ================================ ";
	if (!empty()) {
		root -> print_tree(aux);
	}
	aux << " ================================ \n";
	return aux.str();
}

template <class T>
std::string SplayTree<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root -> preorder(aux);
	}
	aux << "]";
	return aux.str();
}
#endif