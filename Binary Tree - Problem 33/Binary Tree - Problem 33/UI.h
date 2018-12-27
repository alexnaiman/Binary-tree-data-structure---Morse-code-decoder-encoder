#pragma once
#include "BinaryTree.h"
#include <string>

struct morseLetter {
	std::string letter;
	std::string morse;
	morseLetter(std::string letter, std::string morse) :letter(letter), morse(morse) {};
};

class UI {
private:
	std::string dotSymbol = ".";
	std::string dashSymbol = "-";
	std::string separator = " ";
	std::string wordSeparator = "/";
	void TextToMorseMenu();
	BinaryTree<morseLetter> TextToMorseRec(BinaryTree<morseLetter>& bt, std::string search);
	BinaryTree<morseLetter> TextToMorse(BinaryTree<morseLetter> bt, std::string search);
	//BTNode<morseLetter>* TextToMorseRec(BinaryTree<morseLetter> bt, std::string search);
	std::string MorseToText(std::string codeWord);
	void printMenu();
	int read_input();
	void MorseToTextMenu();
	void changeSymbols();
	BinaryTree<morseLetter> morseTree;
public:
	UI();
	void run();
};