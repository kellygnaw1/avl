#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <vector>

using namespace std;

struct node{
	int data; 
	struct node* left;
	struct node* right;
};

class Tree
{
	node* root;
	int visitCount;
	int rotationCount;
	int insertCount;
	vector<pair<int, int> > ll;
	vector<pair<int, int> > lr;
	vector<pair<int, int> > rl;
	vector<pair<int, int> > rr;
	int height(node *);
	int diff(node *);
	void print(node *, int);
	void deconstructHelper(node *);

	void rotationPrintHelper(int, int, node*, int, int);
	void rangeChecker(vector<pair<int, int> >& , int, int);

	node* insert(node *, int); 
	node *rr_rotate(node *);
	node *ll_rotate(node *);
	node *lr_rotate(node *);
	node *rl_rotate(node *);

	node* balance(node *);

public:
	Tree(): ll(), lr(), rl(), rr() {
		root = NULL;
		visitCount = 0; 
		rotationCount = 0; 
		insertCount = 0;
	}
	~Tree();

	bool lookup(int value);
	bool insert(int value);
	void print();
	void printRotation();
	void reset();
	int getVisit();
	int getRotation();
	int getInsert();
	vector<pair<int, int> > get_llPair();
	vector<pair<int, int> > get_lrPair();
	vector<pair<int, int> > get_rlPair();
	vector<pair<int, int> > get_rrPair();
};

#endif