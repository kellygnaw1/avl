#include "Tree.h"
/*
    Height of AVL Tree
*/
int Tree::height(node *temp){
    int h = -1; 
    if(temp != NULL){
        int left_height = height (temp->left);
        int right_height = height (temp->right);
        int max_height = max(left_height, right_height);
        h = max_height + 1; 
    }
    return h;
}

/*
    Height Difference
*/
int Tree:: diff(node *temp){
    int left_height = height(temp->left);
    int right_height = height(temp->right);
    int b_factor = left_height - right_height;
    return b_factor;
}

/*
    Right Right Rotate
*/
node *Tree::rr_rotate(node *parent){
    rotationCount++;
    node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

/*
    Left Left Rotate
*/
node *Tree::ll_rotate(node *parent){
    rotationCount++;
    node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

/*
    Left Right Rotate
*/
node *Tree::lr_rotate(node *parent){
    node *temp;
    temp = parent->left;
    parent->left = rr_rotate(temp);
    return ll_rotate(parent);
}

/*
    Right Left Rotate
*/
node *Tree::rl_rotate(node *parent){
    node *temp;
    temp = parent->right;
    parent->right = ll_rotate(temp);
    return rr_rotate(parent);
}

/*
    Balance
*/
node *Tree::balance(node *temp){
    int balance_factor = diff(temp);
    if(balance_factor > 1){
        if(diff(temp->left) > 0)
            temp = ll_rotate(temp);
        else
            temp = lr_rotate(temp);
    }
    else if(balance_factor < -1){
        if(diff(temp->right) > 0)
            temp = rl_rotate(temp);
        else
            temp = rr_rotate(temp);
    }
    return temp;
}


/*
    Insert
*/
bool Tree::insert(int value) {
    int cache = insertCount;
    root = insert(root, value);
    return cache != insertCount;
}

/*
    Insert helper
*/
node *Tree::insert(node *root, int value){
    if(root == NULL){
        insertCount++;
        root = new node; 
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    visitCount++;

    if(value < root->data){
        root->left = insert(root->left, value);
        root = balance(root);
    }

    else if(value > root->data){
        root->right = insert(root->right, value);
        root = balance(root);
    }

    return root;
}

/*
    print
*/
void Tree::print(){
    print(root, 0);
}

/*
    print helper
*/
void Tree::print(node* node, int depth) {
    string indent="";
    for(int i = 0; i < depth; i++){
        indent += "  ";
    }
    if(node == NULL) {
        cout << indent + "Null" << endl;
    }
    else if(height(node) == 0) {
        cout << indent + "Leaf(" + to_string(node->data) + ")" << endl;
    }
    else {
        cout << indent + "Node(" + to_string(node->data) + ", h=" + to_string(height(node)) +"):" << endl;
        print(node->left, depth + 1);
        print(node->right, depth + 1);
    }
}

/*
    rotation prints
*/
void Tree::printRotation(){
    int min = -2147483648;
    int max = 2147483647;
    rotationPrintHelper(min, max, root, 0, 0);
}

/*
    rotation print helper 
*/
void Tree::rotationPrintHelper(int min, int max, node*temp, int flag1, int flag2){
    //flag1: left = -1 right = 1 unset = 0;
    //flag2: equal path on left= -1; equal path on right = 1; unset = 0;
    /*
    FLAG 1: step 1 of finding the heavy path of tree 
    FLAG 2: step 2 of finding the heavy child, once reaching a balance node, flag 2 tells which direction we go
    */
    if(temp == NULL){
        return;
    }
    
    if(diff(temp) == -1){//right heavy
        rotationPrintHelper(min, temp->data-1, temp->left, 0, 0);
        rotationPrintHelper(temp->data+1, max, temp->right, 1, 0);
    }else if(diff(temp) == 1){//left heavy
        rotationPrintHelper(min, temp->data-1, temp->left, -1, 0);
        rotationPrintHelper(temp->data+1, max, temp->right, 0, 0);
    }else if(diff(temp) == 0){//find right or left balance
        if(flag2 == 0){
            rotationPrintHelper(min, temp->data-1, temp->left, flag1, -1);
            rotationPrintHelper(temp->data+1, max, temp->right, flag1, 1);
        }else{
            rotationPrintHelper(min, temp->data-1, temp->left, flag1, flag2);
            rotationPrintHelper(temp->data+1, max, temp->right, flag1, flag2);
        }
    }

    if(temp->right == NULL && temp->left == NULL){
        if(flag1 == 0){
            return;
        }
        else if(flag1 == -1){
            if(flag2 == 0){
                //left left OR
                rangeChecker(ll, min, temp->data-1);
                //left right
                rangeChecker(lr, temp->data+1, max);
            }else if(flag2 == -1){
                //left left
                rangeChecker(ll, min, temp->data-1);
                rangeChecker(ll, temp->data+1, max);
            }else{//if(flag2 == 1)
                //left right
                rangeChecker(lr, min, temp->data-1);
                rangeChecker(lr, temp->data+1, max);
            }

        }else if(flag1 == 1){
            if(flag2 == 0){
                //right left 
                rangeChecker(rl, min, temp->data-1);
                //right right
                rangeChecker(rr, temp->data+1, max);
            }else if(flag2 == -1){
                //right left
                rangeChecker(rl, min, temp->data-1);
                rangeChecker(rl, temp->data+1, max);
            }else{//if(flag2 == 1)
                //right right
                rangeChecker(rr, min, temp->data-1);
                rangeChecker(rr, temp->data+ 1, max);
            }

        }
    }

}


/*
    Range Check
    -to find if the min and max range are valid ie for a tree like 
            2
           / \
          1   4
             /
            3
*/
void Tree::rangeChecker(vector<pair<int, int> >& v, int min, int max){
    if (min <= max){
        v.push_back(pair<int, int> (min, max));
    }
}

/*
    Look up
*/
bool Tree::lookup(int key){
    if(root == NULL){
        return false;
    }
    node *temp = root; 
    while(temp != NULL){
        visitCount++;
        if(key < temp->data){
            temp = temp->left;
        }else if(key > temp->data){
            temp = temp->right;
        }else if(key == temp->data){
            return true;
        }
    }
    return false;
}

/*
    destructor helper
*/
void Tree:: destructHelper(node *temp){
    if(temp != NULL){
        destructHelper(temp->left);
        destructHelper(temp->right);
        delete temp;
    }
}

/*
    destructor
*/
Tree::~Tree(){
    destructHelper(root);
    root = NULL;
}

/*
    getter methods
*/
int Tree::getVisit(){
    return visitCount;
}
int Tree::getRotation(){
    return rotationCount;
}
int Tree::getInsert(){
    return insertCount;
}

vector<pair<int, int> > Tree::get_llPair(){
    return ll;
}

vector<pair<int, int> > Tree::get_lrPair(){
    return lr;
}

vector<pair<int, int> > Tree::get_rlPair(){
    return rl;
}

vector<pair<int, int> > Tree::get_rrPair(){
    return rr;
}

/*
    reset statistics
*/
void Tree::reset(){
    visitCount = 0; 
    rotationCount = 0; 
    insertCount = 0; 
    ll.clear();
    lr.clear();
    rl.clear();
    rr.clear();
}
