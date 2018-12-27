#pragma once
#include "Tests.h"
#include "BinaryTree.h"
#include <assert.h>
#include <iostream>
#include <string>
#include "UI.h"
void testConstructors()
{
	//test exceptions
	BinaryTree<int>o{};
	try {
		o.getRootValue();
		assert(false);
	}
	catch(std::exception&e){
	}
	try {
		o.left();
		assert(false);
	}
	catch (std::exception&e) {
	}
	try {
		o.right();
		assert(false);
	}
	catch (std::exception&e) {
	}
	//test adt

	/*BinaryTree<int>t;
	assert(t.isEmpty());
	t = BinaryTree<int>{ 6 };
	assert(t.getRootValue() == 6);
	assert(!t.isEmpty());
	BinaryTree<int>t1{ 7 };
	BinaryTree<int>t2{ 8 };
	assert(t.getRoot()->element = t.getRootValue());
	t.insertLeftSubtree(t1);
	t.insertRightSubtree(t2);
	assert(t1.getRootValue() == t.left().getRootValue());
	assert(t2.getRootValue() == t.right().getRootValue());
	t.insertLeftSubtree(t1);
	assert(t.left().getRootValue() == t1.getRootValue());*/
}


void testIterators()
{
	BinaryTree<std::string>ta;
	ta = BinaryTree<std::string>{ "A" };
	BinaryTree<std::string>tg{ "G" };
	BinaryTree<std::string>tt{ "T" };
	BinaryTree<std::string>tq{ "Q" };
	BinaryTree<std::string>tx{ "X" };
	BinaryTree<std::string>tn{ "N" };
	BinaryTree<std::string>to{ "O" };
	BinaryTree<std::string>ty{ "Y" };
	BinaryTree<std::string>tj{ "J" };
	BinaryTree<std::string>tk{ "K" };
	tj.insertLeftSubtree(tk);
	tx.insertRightSubtree(tj);
	tx.insertLeftSubtree(ty);
	tg.insertLeftSubtree(tq);
	tg.insertRightSubtree(tx);
	tt.insertLeftSubtree(tn);
	tt.insertRightSubtree(to);
	ta.insertLeftSubtree(tg);
	ta.insertRightSubtree(tt);
	std::string checkInOrderTraversal = "Q G Y X K J A N T O ";
	std::string auxString = "";
	AbstractIterator<std::string>* inOrder = ta.iterator("inorder");

	while (inOrder->valid()) {
		auxString += inOrder->getCurrent() + " ";
		inOrder->next();
	}
	assert(checkInOrderTraversal == auxString);

	std::string checkPreOrderTraversal = "A G Q X Y J K T N O ";
	auxString = "";
	AbstractIterator<std::string>* preOrder = ta.iterator("preorder");
	while (preOrder->valid()) {
		auxString += preOrder->getCurrent() + " ";
		preOrder->next();
	}
	assert(checkPreOrderTraversal == auxString);
	
	std::string checkPostOrderTraversal = "Q Y K J X G N O T A ";
	auxString = "";
	AbstractIterator<std::string>* postOrder = ta.iterator("postorder");
	while (postOrder->valid()) {
		auxString += postOrder->getCurrent() + " ";
		postOrder->next();
	}
	assert(checkPostOrderTraversal == auxString);


	std::string checkLevelOrderTraversal = "A G T Q X N O Y J K ";
	auxString = "";
	AbstractIterator<std::string>* levelOrder = ta.iterator("levelorder");
	while (levelOrder->valid()) {
		auxString += levelOrder->getCurrent() + " ";
		levelOrder->next();
	}
	assert(checkLevelOrderTraversal == auxString);

}
