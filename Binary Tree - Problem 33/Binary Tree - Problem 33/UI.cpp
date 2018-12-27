#include "UI.h"
#include <iostream>
#include <string>
#include <exception>
#include <fstream>
#include <sstream>

using namespace std;
UI::UI() : morseTree{ morseLetter("","") }
{
	BinaryTree<morseLetter>e{ morseLetter("e",".") };
	BinaryTree<morseLetter>t{ morseLetter("t","_") };
	BinaryTree<morseLetter>i{ morseLetter("i","..") };
	BinaryTree<morseLetter>a{ morseLetter("a","._") };
	BinaryTree<morseLetter>n{ morseLetter("n","_.") };
	BinaryTree<morseLetter>m{ morseLetter("m","__") };
	BinaryTree<morseLetter>s{ morseLetter("s","...") };
	BinaryTree<morseLetter>u{ morseLetter("u",".._") };
	BinaryTree<morseLetter>r{ morseLetter("r","._.")};
	BinaryTree<morseLetter>w{ morseLetter("w",".__") };
	BinaryTree<morseLetter>d{ morseLetter("d","_..") };
	BinaryTree<morseLetter>k{ morseLetter("k","_._") };
	BinaryTree<morseLetter>o{ morseLetter("o","___")};
	BinaryTree<morseLetter>h{ morseLetter("h","....") };
	BinaryTree<morseLetter>v{ morseLetter("v","..._") };
	BinaryTree<morseLetter>f{ morseLetter("f",".._.") };
	BinaryTree<morseLetter>l{ morseLetter("l","._..") };
	BinaryTree<morseLetter>p{ morseLetter("p",".__.") };
	BinaryTree<morseLetter>j{ morseLetter("j",".___") };
	BinaryTree<morseLetter>b{ morseLetter("b","_...") };
	BinaryTree<morseLetter>x{ morseLetter("x","_.._") };
	BinaryTree<morseLetter>c{ morseLetter("c","_._.") };
	BinaryTree<morseLetter>y{ morseLetter("y","_.__") };
	BinaryTree<morseLetter>z{ morseLetter("z","__..") };
	BinaryTree<morseLetter>q{ morseLetter("q","__._") };
	BinaryTree<morseLetter>g{ morseLetter("g","__.") };

	s.insertLeftSubtree(h);
	s.insertRightSubtree(v);
	u.insertLeftSubtree(f);
	i.insertLeftSubtree(s);
	i.insertRightSubtree(u);
	r.insertLeftSubtree(l);
	w.insertLeftSubtree(p);
	w.insertRightSubtree(j);
	a.insertLeftSubtree(r);
	a.insertRightSubtree(w);
	e.insertLeftSubtree(i);
	e.insertRightSubtree(a);
	d.insertLeftSubtree(b);
	d.insertRightSubtree(x);
	k.insertLeftSubtree(c);
	k.insertRightSubtree(y);
	n.insertLeftSubtree(d);
	n.insertRightSubtree(k);
	g.insertLeftSubtree(z);
	g.insertRightSubtree(q);
	m.insertLeftSubtree(g);
	m.insertRightSubtree(o);
	t.insertLeftSubtree(n);
	t.insertRightSubtree(m);
	morseTree.insertLeftSubtree(e);
	morseTree.insertRightSubtree(t);

	/*AbstractIterator<string>* levelOrder = morseTree.iterator("levelorder");
	while (levelOrder->valid()) {
		cout<< levelOrder->getCurrent().c_str() << " ";
		levelOrder->next();
	}*/
}
void UI::TextToMorseMenu()
{
	string inFile{ "" };
	cout << "Give filename to translate:  ";
	cin.ignore();
	getline(cin, inFile);
	ifstream in{ inFile };
	ofstream out;
	ofstream ofs;
	ofs.open("translation.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
	out.open("translation.txt", std::ios_base::app);
	string word{ "" };
	while (getline(in, word, ' ')) {
		stringstream buffer{ word };
		string codedWord = "";
		for (auto &i : word) {
			if (i == '\n')
				continue;
			else if (!isalpha(i))
					throw std::exception("Sorry cannot translate the given file!");
			codedWord += TextToMorse(morseTree,string(1,i)).getRootValue().morse + " ";
		}
		string toWrite = "";
		for (auto&i : codedWord) {
			if (i == '_')
				toWrite += dashSymbol;
			else if (i == '.')
				toWrite += dotSymbol;
			else
				toWrite += i;
		}
		out << toWrite.c_str() << wordSeparator;
	}
}
void UI::run()
{
	int command{ 0 };
	
	string stringCommand{ "" };
	while (true) {
		printMenu();
		command = read_input();
		switch (command) {
		case 0:
			return;
		case 1:
			try {
				MorseToTextMenu();
			}
			catch (exception& e) {
				cout << e.what() << endl;
			}
			cout << " ";
			break;
		case 2:
			try {
			TextToMorseMenu();
			}
			catch (exception& e) {
				cout << e.what() << endl;
			}
			break;
		case 3:
			changeSymbols();
			break;
		}
	}
}

void UI::MorseToTextMenu()
{
	string inFile{ "" };
	cout << "Give filename to translate:  ";
	cin.ignore();
	getline(cin, inFile);
	ifstream in{ inFile };
	ofstream out;
	ofstream ofs;
	ofs.open("translation.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
	out.open("translation.txt", std::ios_base::app);
	string codedWord{ "" };
	while (getline(in, codedWord, wordSeparator[0])) {
		stringstream buffer{ codedWord };
		string letter = "" ;
		while (getline(buffer, letter, separator[0]))
		{
			/*if (letter!=dashSymbol && letter!=dotSymbol)
				throw std::exception("Sorry cannot translate the given file!");*/
			out << MorseToText(letter).c_str();
		}
		out << " ";
	}
}

void UI::changeSymbols()
{
	std::string dot="", dash="", separator="";
	cout << "Dash symbol=";
	cin.ignore();
	getline(cin, dash);
	if (dash.size() > 1) {
		cout << "Error: give only one character" << endl;
		return;
	}
	cout << "Dot symbol=";
	//cin.ignore();
	getline(cin, dot);
	if (dot.size() > 1) {
		cout << "Error: give only one character" << endl;
		return;
	}
	cout << "Separator symbol=";
	//cin.ignore();
	getline(cin, separator);
	if (separator.size() > 1) {
		cout << "Error: give only one character";
		return;
	}
	if (dot == dash || dot == separator || separator == dash)
	{
		cout << "Error: characters must be different"<<endl;
	}
	dotSymbol = dot;
	dashSymbol = dash;
	wordSeparator = separator;

}

std::string UI::MorseToText(string codeWord)
{
	string decodedWord = "";
	BinaryTree<morseLetter> node{};
	if (codeWord.size() > 0) {
		if (codeWord[0] == dashSymbol[0]) {
			node = morseTree.right();
		}
		else if (codeWord[0] == dotSymbol[0]) {
			node = morseTree.left();
		}
		else {
			throw std::exception("Sorry cannot translate the given file!");
		}
	}
	codeWord.erase(0, 1);
	while (codeWord.size()-1 > 0) {
		char s = codeWord[0];
		if (s != dashSymbol[0] && s != dotSymbol[0])
			throw std::exception("Sorry cannot translate the given file!");
		if (s == dotSymbol[0]) {
			decodedWord += dotSymbol;
			node = node.left();
			codeWord.erase(0, 1);
			continue;
		}
		if (s == dashSymbol[0]) {
			decodedWord += dashSymbol;
			node = node.right();
			codeWord.erase(0, 1);
			continue;
		}
	}
	decodedWord = node.getRootValue().letter;
	//cout << decodedWord << endl;
	return decodedWord;
}



BinaryTree<morseLetter> UI::TextToMorseRec(BinaryTree<morseLetter>& bt, std::string search)
{

	if (!bt.isEmpty()) {
		if (bt.getRootValue().letter==search) {
			return bt;
		}
		else {
			auto left = bt.left();
			BinaryTree<morseLetter> foundNode = TextToMorseRec(left,search);
			if (foundNode.isEmpty()) {
				auto right = bt.right();
				foundNode = TextToMorseRec(right,search);
			}
			return foundNode;
		}
	}
	else {
		return BinaryTree<morseLetter>();
	}

	
}

BinaryTree<morseLetter> UI::TextToMorse(BinaryTree<morseLetter> bt, string search) {
	auto left = bt.left();
	if (!left.isEmpty()) {
		auto n = TextToMorseRec(left, search);
		if (!n.isEmpty())
			return n;
	}
	auto right = bt.right();
	if (!right.isEmpty()) {
		auto n = TextToMorseRec(right, search);
		if (!n.isEmpty())
			return n;
	}
	
}

void UI::printMenu()
{
	cout << "1. Translate Morse code to text" << endl;
	cout << "2. Translate text to morse code" << endl;
	cout << "3. Change Morse code's symbols" << endl;
	cout << "0. Exit" << endl;
}

int UI::read_input()
{
	int input = -1;
	bool valid = false;
	do
	{
		cout << "Enter a number: " << flush;
		cin >> input;
		if (cin.good())
		{
			//everything went well, we'll get out of the loop and return the value
			valid = true;
		}
		else
		{
			//something went wrong, we reset the buffer's state to good
			cin.clear();
			//and empty it
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input; please re-enter." << endl;
		}
	} while (!valid);

	return (input);
}