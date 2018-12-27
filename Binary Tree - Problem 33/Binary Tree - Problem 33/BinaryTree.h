#pragma once
#include <stack>
#include <algorithm>
#include <queue>


template<typename TElem>
struct BTNode {
	TElem element;
	BTNode* right=nullptr;
	BTNode* left = nullptr;
	BTNode(TElem element) : element{ element }, left{ nullptr }, right{ nullptr } {};
	BTNode(TElem element, BTNode* left, BTNode* right) : element{ element }, right{ right }, left{ left } {};
};

template <typename T>
class BinaryTree;
template <typename T>
class AbstractIterator;
template <typename T>
class InOrderIterator;
template <typename T>
class PreOrderIterator;
template <typename T>
class PostOrderIterator;
template <typename T>
class LevelOrderIterator;


template <typename T>
class BinaryTree {
private:
	BTNode<T> * root;
	friend class AbstractIterator<T>;
	friend class InOrderIterator<T>;
	friend class PreOrderIterator<T>;
	friend class PostOrderIterator<T>;
	friend class LevelOrderIterator<T>;
	//desc: deletes the subtrees from a given node
	//pre: node ∈ ↑BTNode
	//post: the subtree is deleted
	void deleteSubTrees(BTNode<T>* node) {
		if (node != nullptr) {
			destroyNodesFromSubTree(node->left);
			destroyNodesFromSubTree(node->right);
		}
	}
	//desc: copies recursively the nodes from a subtree (node)
	//pre: node ∈ ↑BTNode
	//post: copySubTree<- the new subTree with all the elements copied from the given subtree
	BTNode<T>* copySubTree(BTNode<T>* subtree) const {
		if (subtree != nullptr) {
			BTNode<T>* pNew = new BTNode<T>(subtree->element, nullptr, nullptr);
			pNew->left = copySubTree(subtree->left);
			pNew->right = copySubTree(subtree->right);
			return pNew;
		}
			return nullptr;
		}
	//desc: deletes the subtrees and frees its nodes, from a given node
	//pre: node ∈ ↑BTNode
	//post: the subtree is deleted
	void destroyNodesFromSubTree(BTNode<T>* node) {
		if (node != nullptr) {
			destroyNodesFromSubTree(node->left);
			destroyNodesFromSubTree(node->right);
			delete node;
		}
	}
	BTNode<T>* getRoot() {
		return root;
	}
public:
	//descr: creates a new, empty binary tree
	//pre: true
	//post: bt ∈ BT , bt is an empty binary tree
	BinaryTree() { root = nullptr; }

	//descr: creates a new binary tree, having only the root with a given value
	//pre: e ∈ TElem
	//post: bt ∈ BT, bt is a binary tree with only one node (its root) which contains the value e
	BinaryTree(T elem){
		root = new BTNode<T>(elem);
	}
	BinaryTree(const BinaryTree& bt) {
		this->root = copySubTree(bt.root);
	}
	
	//descr: creates a new binary tree, having a given information in the root and two given binary trees as children
	//pre: left,right ∈ BT , e ∈ TElem
	//post: bt ∈ BT , bt is a binary tree with left child equal to left, right child equal to right and the information from the root is e
	BinaryTree(BinaryTree<T> left, T elem, BinaryTree<T> right) {
		root = new BTNode<T>(elem);
		root->left = copySubTree(left.root);
		root->right = copySubTree(right.root);
	}
	~BinaryTree() {
		destroyNodesFromSubTree(root);
	}
	BinaryTree operator=(const BinaryTree<T> other) {
		this->root = copySubTree(other.root);
		return *this;
	}

	//descr: sets the left subtree of a binary tree to a given value (if the tree had a left subtree, it will be changed)
	//pre: bt, left ∈ BT
	//post: bt’ ∈ BT , the left subtree of bt’ is equal to left
	void insertLeftSubtree(const BinaryTree<T> left) {
		deleteSubTrees(root->left);
		root->left = copySubTree(left.root);
	}

	//descr: sets the right subtree of a binary tree to a given value (if the tree had a right subtree, it will be changed)
	//pre: bt, right ∈ BT
	//post: bt’ ∈ BT , the right subtree of bt’ is equal to right

	void insertRightSubtree(const BinaryTree<T> rigt) {
		deleteSubTrees(root->right);
		root->right = copySubTree(rigt.root);
	}

	//descr: returns the information from the root of a binary tree
	//pre: bt ∈ BT , bt != Φ
	//post: root ← e, e ∈ TElem, e is the information from the root //of bt
	T getRootValue() const {
		if (root == nullptr) {
			throw std::exception("Tree is empty!");
		}
		return root->element;
	}

	//descr: returns the root of a binary tree
	//pre: bt ∈ BT , bt != Φ
	//post: root ← r, r ∈  ↑BTNode the root of bt
	//throws: an exception if bt is empty
	
	BinaryTree<T> left() {

		//descr: returns the left subtree of a binary tree
		//pre: bt ∈ BT , bt != Φ
		//post: left ← l, l ∈ BT, l is the left subtree of bt
		//throws: an exception
		if (root == nullptr) {
			throw std::exception("Tree is empty!");
		}
		if (root->left == nullptr) {
			return BinaryTree<T>{};
		}
		BinaryTree<T> aux{};
		aux.root = copySubTree(root->left);
		return aux;
	}
	BinaryTree right() {
		//descr: returns the right subtree of a binary tree
		//pre: bt ∈ BT , bt != Φ
		//post: right ← l, l ∈ BT, l is the right subtree of bt
		//throws: an exception
		if (root == nullptr) {
			throw std::exception("Tree is empty!");
		}
		if (root->right == nullptr) {
			return BinaryTree<T>{};
		}
		BinaryTree<T> aux{};
		aux.root = copySubTree(root->right);
		return aux;
	}
	//descr: checks if a binary tree is empty
	//pre: bt ∈ BT
	//post: empty ← {True, if bt = Φ, False, otherwise
	bool isEmpty() {
		return root == nullptr;
	}
	//descr: returns an iterator for a binary tree
	//pre: bt ∈ BT, traversal represents the order in which the tree //has to be traversed
	//post: i ∈ I, i is an iterator over bt that iterates in the order //given by traversal
	AbstractIterator<T>* iterator(std::string traversal) {
		AbstractIterator<T>* i = nullptr;
		if (traversal == "inorder") {
			i = new InOrderIterator<T>{*this};
		}
		else if (traversal == "preorder") {
			i = new PreOrderIterator<T>{ *this };
		}
		else if (traversal == "postorder") {
			i = new PostOrderIterator<T>{ *this };
		} 
		else if (traversal == "levelorder") {
			i = new LevelOrderIterator<T>{ *this };
		}
		return i;
	}
};


template <typename T>
class AbstractIterator {
protected:
	BinaryTree<T> bt;
	BTNode<T>* currentNode;
public:
	virtual ~AbstractIterator() {};
	AbstractIterator() {};
	AbstractIterator(BinaryTree<T>& bt) : bt(bt) {};
	virtual T getCurrent() = 0;
	virtual bool valid() = 0;
	virtual void next() = 0;
};

template <typename T>
class InOrderIterator : public  AbstractIterator<T> {
private:
	std::stack<BTNode<T>*> stack;
	
public:
	InOrderIterator() {}
	//descr: creates a new inorder iterator for a Binary tree (bt)
	//pre: bt ∈ BT
	//post: it ∈ I and it points to the root of the tree bt, if bt is neither empty nor valid
	InOrderIterator(BinaryTree<T>& bt) : AbstractIterator<T>(bt), stack{} {
		BTNode<T>* node = bt.root;
		while (node != nullptr) {
			stack.push(node);
			node = node->left;
		}
		if (!stack.empty()) {
			this->currentNode = stack.top();
		}
		else {
			this->currentNode = nullptr;
		}
	}

	//descr: returns the current node from the iterator
	//pre : it ∈ I, it is valid
	//post: getCurrent←current node from iterator
	T getCurrent() override {
		return this->currentNode->element;
	}

	//descr: verifies if the iterator is valid
	//pre: it ∈ I
	//post: valid←True, if the iterator poins to valid node of the binary tree, False,otherwise
	bool valid() override {
		return this->currentNode != nullptr;
	}

	//descr: moves the current element to the next node according to the way of the inorder traversal, or makes the iterator invalid if there are no more nodes
	//pre: it ∈ I, it is valid
	//post: the current element points to the next node of the tree
	void next() override {
		BTNode<T>* node = stack.top();
		stack.pop();
		if (node->right != nullptr) {
			node = node->right;
			while (node != nullptr) {
				stack.push(node);
				node = node->left;
			}
		}
		if (!stack.empty()) {
			this->currentNode = this->stack.top();
		}
		else {
			this->currentNode = nullptr;
		}
	}
};

template <typename T>
class PreOrderIterator : public  AbstractIterator<T> {
private:
	std::stack<BTNode<T>*> stack;

public:
	PreOrderIterator() {}

	//descr: creates a new preorder iterator for a Binary tree (bt)
	//pre: bt ∈ BT
	//post: it ∈ I and it points to the root of the tree bt, if bt is neither empty nor valid
	PreOrderIterator(BinaryTree<T>& bt) : AbstractIterator<T>(bt), stack{} {
		BTNode<T>* node = bt.root;
		if (node != nullptr) {
			stack.push(node);
		}
		if (!stack.empty()) {
			this->currentNode = stack.top();
		}
		else {
			this->currentNode = nullptr;
		}
	}
	//descr: returns the current node from the iterator
	//pre : it ∈ I, it is valid
	//post: getCurrent←current node from iterator
	T getCurrent() override {
		return this->currentNode->element;
	}

	//descr: verifies if the iterator is valid
	//pre: it ∈ I
	//post: valid←True, if the iterator poins to valid node of the binary tree, False,otherwise
	bool valid() override {
		return this->currentNode != nullptr;
	}

	//descr: moves the current element to the next node according to the way of the preorder traversal, or makes the iterator invalid if there are no more nodes
	//pre: it ∈ I, it is valid
	//post: the current element points to the next node of the tree
	void next() override {
		BTNode<T>* node = stack.top();
		stack.pop();
		if (node->right != nullptr) {
			stack.push(node->right);
		}
		if (node->left != nullptr) {
			stack.push(node->left);
		}
		if (!stack.empty()) {
			this->currentNode = stack.top();
		}
		else {
			this->currentNode = nullptr;
		}
	}
};


template <typename T>
class PostOrderIterator : public  AbstractIterator<T> {
private:
	std::stack<BTNode<T>*> stack;
	//descr: helper function used to build the stack for the iterator and to the next leaf we need to put on the stack
	//pre : it ∈ I, it is valid, node ∈ ↑BTNode
	//post: it.s contains all the nodes from the given to node to the next leaf we search for

	void findNextLeaf(BTNode<T>* current) {
		while (current != nullptr) {
			stack.push(current);
			if (current->left != nullptr) {
				current = current->left;
			}
			else {
				current = current->right;
			}
		}
	}
public:
	PostOrderIterator() {}

	//descr: creates a new postorder iterator for a Binary tree (bt)
	//pre: bt ∈ BT
	//post: it ∈ I and it points to the root of the tree bt, if bt is neither empty nor valid
	PostOrderIterator(BinaryTree<T>& bt) : AbstractIterator<T>(bt), stack{} {
		findNextLeaf(bt.root);
		if (!stack.empty()) {
			BTNode<T>* res = stack.top();
			stack.pop();
			if (!stack.empty()) {
				auto top = stack.top();
				if (res == top->left) {
					findNextLeaf(top->right);
				}
			}
			this->currentNode = res;
		}
		else {
			this->currentNode = nullptr;
		}

	}

	//descr: returns the current node from the iterator
	//pre : it ∈ I, it is valid
	//post: getCurrent←current node from iterator
	T getCurrent() override {
		return this->currentNode->element;
	}
	//descr: verifies if the iterator is valid
	//pre: it ∈ I
	//post: valid←True, if the iterator poins to valid node of the binary tree, False,otherwise
	bool valid() override {
		return this->currentNode!=nullptr;
	}

	//descr: moves the current element to the next node according to the way of the postorder traversal, or makes the iterator invalid if there are no more nodes
	//pre: it ∈ I, it is valid
	//post: the current element points to the next node of the tree
	void next() override {
		if (!stack.empty()) {
			BTNode<T>* res = stack.top();
			stack.pop();
			if (!stack.empty()) {
				auto top = stack.top();
				if (res == top->left) {
					findNextLeaf(top->right);
				}
			}
			this->currentNode = res;
		}
		else {
			this->currentNode = nullptr;
		}
	}
};


template <typename T>
class LevelOrderIterator : public  AbstractIterator<T> {
private:
	std::queue<BTNode<T>*> queue;

public:
	LevelOrderIterator() {}
	//descr: creates a new levelorder iterator for a Binary tree (bt)
	//pre: bt ∈ BT
	//post: it ∈ I and it points to the root of the tree bt, if bt is neither empty nor valid
	LevelOrderIterator(BinaryTree<T>& bt) : AbstractIterator<T>(bt), queue{} {
		queue.push(bt.root);
		if (!queue.empty()) {
			this->currentNode = queue.front();
		}
		else {
			this->currentNode = nullptr;
		}
	}

	//descr: returns the current node from the iterator
	//pre : it ∈ I, it is valid
	//post: getCurrent←current node from iterator
	T getCurrent() override {
		return this->currentNode->element;
	}

	//descr: verifies if the iterator is valid
	//pre: it ∈ I
	//post: valid←True, if the iterator poins to valid node of the binary tree, False,otherwise
	bool valid() override {
		return this->currentNode != nullptr;
	}

	//descr: moves the current element to the next node according to the way of the levelorder traversal, or makes the iterator invalid if there are no more nodes
	//pre: it ∈ I, it is valid
	//post: the current element points to the next node of the tree
	void next() override {
		auto node = queue.front();
		queue.pop();
		if (node->left != nullptr) {
			queue.push(node->left);
		}
		if (node->right != nullptr) {
			queue.push(node->right);
		}

		if (!queue.empty()) {
			this->currentNode = queue.front();
		}
		else {
			this->currentNode = nullptr;
		}
	}
};
