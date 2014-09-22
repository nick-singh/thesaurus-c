/*
	Assignment 1 Thesaurus

	Problem : 	Given a file with synonyms on each line, meaning that 
				on each line of the file any given word is a synonym 
				to another word on that line. Words may appear on other 
				lines, hence all words on those lines are also synonyms.

	Task : 	Build a thesaurus such that given any word all synonyms must 
			be found quickly.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORDSIZE 32
#define MAXLINE 100


//==================================
	//Structure Definations		
//==================================

typedef struct listNode
{
	char word[MAXWORDSIZE +1];
	struct listNode *next;
}ListNode, *ListNodePtr;


typedef struct 
{
	char word[MAXWORDSIZE+1];
	ListNodePtr synonym;
}NodeData;


typedef struct treeNode
{
	NodeData data;
	int print;
	int found;
	struct treeNode *left, *right;
}TreeNode, *TreeNodePtr;

typedef struct
{
	TreeNodePtr root;
}BinaryTree;


//==================================
	//Function Prototypes
//==================================


/*Binary Tree Functions*/
NodeData newNodeData(char[]);
ListNodePtr newListNode(char[]);
TreeNodePtr newTreeNode(NodeData d);
TreeNodePtr findOrInsert(BinaryTree, NodeData);
ListNodePtr addInPlace(ListNodePtr,char[]);

/* Utility type Functions*/
int getWord(char[], char[]);
int getWord2(char[], char[]);
void inOrder(FILE*,TreeNodePtr);
void inOrder2(FILE*,TreeNodePtr, BinaryTree);


//==================================
	//Main		
//==================================

int main()
{

	FILE *in = fopen("input.txt","r");
	FILE *out = fopen("output.txt","w");
	if(in == NULL)printf("Error reading input...\n");	

	char word[MAXWORDSIZE+1];
	char tempword[MAXWORDSIZE+1];
	char line[MAXLINE];
	char templine[MAXLINE];
	BinaryTree bst;	
	TreeNodePtr node;
	bst.root = NULL;
	int k = 0;
	
	while(fgets(line,MAXLINE,in)!= NULL){
		strcpy(templine,line);
		while(getWord(line,word)!=0){										
			if(bst.root == NULL){						
				bst.root = node = newTreeNode(newNodeData(word));					 
			}else{					
				node = findOrInsert(bst,newNodeData(word));	
				if(node->found){

					while(getWord2(templine,tempword)!=0){								
						if(strcmp(tempword,node->data.word)!=0){							
							node->data.synonym = addInPlace(node->data.synonym, tempword);			
						}
					}
				}
			}			
			while(getWord2(templine,tempword)!=0){								
				if(strcmp(tempword,node->data.word)!=0){
					node->data.synonym = addInPlace(node->data.synonym, tempword);			
				}
			}			
		}
		k = 0;				
	}
	fprintf(out, "Words \t\t\tSynonyms\n");
	fprintf(out, "\n\n");
	inOrder(out,bst.root);	
	fprintf(out, "\n\n");
	fprintf(out, "Words \t\t\tSynonyms\n");
	fprintf(out, "\n\n");
	inOrder2(out,bst.root,bst);	
	fclose(in);
	fclose(out);
	return 0;
}						


//==================================
	//Structure Creation FUnctions		
//==================================

NodeData newNodeData(char str[]){
	NodeData temp;
	strcpy(temp.word,str);
	temp.synonym = NULL;
	return temp;
}

ListNodePtr newListNode(char str[]){
	ListNodePtr p = (ListNodePtr)malloc(sizeof(ListNode));
	strcpy(p->word,str);
	p->next = NULL;
	return p;
}

TreeNodePtr newTreeNode(NodeData d){
	TreeNodePtr p = (TreeNodePtr)malloc(sizeof(TreeNode));
	p->data = d;
	p->print = 0;
	p->found = 0;
	p->left = p->right = NULL;
	return p;
}


//==================================
	//Inseration Functions	
//==================================


ListNodePtr addInPlace(ListNodePtr top, char word[]){
	ListNodePtr np, curr, prev;
	np = newListNode(word);
	prev = NULL;
	curr = top;
	int cmp;
	while(curr!= NULL && (cmp=strcmp(np->word,curr->word)) >0){		
		prev = curr;
		curr = curr->next;		
	}
	if(prev == NULL){
		np->next = top;
		return np;
	}
	if(cmp!=0){		
		np->next = curr;
		prev->next = np;
	}	

	return top;
}


TreeNodePtr findOrInsert(BinaryTree bt, NodeData d){		
	if(bt.root == NULL)return newTreeNode(d);
	TreeNodePtr curr = bt.root;
	int cmp;	
	while((cmp = strcmp(d.word,curr->data.word))!= 0){			
		if(cmp<0){
			if(curr->left == NULL)return curr->left = newTreeNode(d);
			curr = curr->left;			
		}else{
			if(curr->right == NULL)return curr->right = newTreeNode(d);
			curr = curr->right;			
		}
	}
	if(cmp ==0)curr->found = 1;
	return curr;
}


//==================================
	//Returns Each Word Given A Line
//==================================

int getWord(char line[], char str[]){
	static int p = 0;
	char ch;
	int n = 0;
	while(line[p] != '\0' && !isalpha(line[p]))p++;
	if(line[p] == '\0')return p = 0;
	str[n++] = line[p++];
	while(isalpha(line[p])){
		if(n < MAXWORDSIZE)str[n++] = line[p];
		p++;
	}
	str[n] = '\0';	
	return 1;
}

int getWord2(char line[], char str[]){
	static int p = 0;
	char ch;
	int n = 0;
	while(line[p] != '\0' && !isalpha(line[p]))p++;
	if(line[p] == '\0')return p = 0;
	str[n++] = line[p++];
	while(isalpha(line[p])){
		if(n < MAXWORDSIZE)str[n++] = line[p];
		p++;
	}
	str[n] = '\0';	
	return 1;
}



//==================================
	//Printing Synonyms 
//==================================


void inOrder(FILE*out,TreeNodePtr node){
	void printAword(FILE*,TreeNodePtr);
	if(node!=NULL){
		inOrder(out,node->left);
		printAword(out,node);
		fprintf(out, "\n");
		inOrder(out,node->right);
	}
}

void printAword(FILE *out, TreeNodePtr pt){
	void printSynonym(FILE*,ListNodePtr);
	fprintf(out, "%-15s ", pt->data.word);
	printSynonym(out,pt->data.synonym);	
}

void printSynonym(FILE*out, ListNodePtr top){
	if(top != NULL){		
		fprintf(out, "%s ",top->word);
		printSynonym(out,top->next);
	}
}


void inOrder2(FILE*out,TreeNodePtr node, BinaryTree root){	
	void printSynonym2(FILE*, BinaryTree, ListNodePtr);
	if(node!=NULL){
		inOrder2(out,node->left,root);				
		if(!node->print){
			node->print = 1;
			fprintf(out,"%-16s",node->data.word);					
			printSynonym2(out,root, node->data.synonym);
		}				
		inOrder2(out,node->right,root);
	}
}

void printSynonym2(FILE *out,BinaryTree root, ListNodePtr top) {
	ListNodePtr c2 = top;
	TreeNodePtr ptr;
	while(top != NULL){
		char word[MAXWORDSIZE];
		strcpy(word,top->word);
		ptr = findOrInsert(root, newNodeData(word));
		if(ptr != NULL){			
			ptr->print = 1;
		}		
		fprintf(out, "%s ", top->word);
		top = top->next;
	}
	fprintf(out, "\n");
}

