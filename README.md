# Binary-tree-data-structure---Morse-code-decoder-encoder

For this project I had to implement a binary tree data structure with all the four iterators(pre-order, in-order, post-order, level-order) and use it to solve one problem(at my choice)

#### Here you can find the [project stage](https://github.com/alexnaiman/Binary-tree-data-structure---Morse-code-decoder-encoder/blob/master/Data%20structures%20and%20algorithms%20Project%20documentation%20--%20project%20stage.pdf) and also the [project documentation](https://github.com/alexnaiman/Binary-tree-data-structure---Morse-code-decoder-encoder/blob/master/Data%20structures%20and%20algorithms%20Project%20documentation.docx) for this project

### Problem statement

Morse code is a method of transmitting text information as a series of on-off tones, lights, or clicks that can be directly understood by a skilled listener or observer without special equipment. Each Morse code symbol represents either a text character (letter or numeral) or a prosign and is represented by a unique sequence of dots(“.”) and dashes(“_”). The coded letters are usually separated through empty blank spaces (“ “), and the words are separated through a special character (“/”).


Example:
	`-... .. -. .- .-. -.-- / - .-. . .  == binary tree`


As you are a big fan data encryption you want to create an application that is capable of encrypting and decrypting phrases of unspecified size from and into Morse code. You we’ll need to performs these operations on text stored on a file.	As the symbols (dash, dot, slash) appearance have no relevant meaning to the Morse code, you can change them to use any character of your like, with the condition that they are different two by two.


I choose to use an ADT Binary Tree for this application because, one can organize the Morse code as a binary tree, making it easy to retrieve data, using the iterators so we can encrypt/decrypt the letters one by one easily
