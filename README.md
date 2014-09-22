COMP64012014_2015S1-Assignment 1
Thesaurus

Write a program to read and store a thesaurus as follows.

Data for the program consists of lines of input.  Each line contains a (variable) number of distinct words, all of which are synonyms.  You may assume that words consist of letters only and are separated by one or more blanks. The data structure must be organized such that, given any word, all synonyms for that word can be quickly found.  A word can appear on more than one line. If a word appears on more than one line then all words on those lines are to be considered synonyms.

After the complete thesaurus has been built, print an alphabetical listing of the words and their synonyms.

Print another alphabetical listing but, this time, each word is printed once only.  That is, if a word is already printed as a synonym of another word then it does not appear in the listing again.

Sample input

blossom flower
bewilder confound confuse perplex
dwell live reside

Sample output

Words                Synonyms

bewilder             confound confuse perplex 
blossom              flower 
confound             bewilder confuse perplex 
confuse              bewilder confound perplex 
dwell                live reside 
flower               blossom 
live                 dwell reside 
perplex              bewilder confound confuse 
reside               dwell live 


Words                Synonyms

bewilder             confound confuse perplex 
blossom              flower 
dwell                live reside 
