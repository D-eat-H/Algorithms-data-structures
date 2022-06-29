#include <bits/stdc++.h>

using namespace std;

struct Node{
	int data, height;
	Node* left, *right;
	
	Node(int x){
		data = x;
		left = right = NULL;
		height = 1;
	}
};

int getHeight(Node* n){
	return n != NULL ? n -> height : 0;
}   

int getBalance(Node* root){
    return root != NULL ? getHeight(root -> left) - getHeight(root -> right) : 0;
}

Node* leftRotate(Node* root){
    Node* b = root -> right;
    Node* b1 = b -> left;
    
	// Perform rotation
    b -> left = root;
    root -> right = b1;
    	
    // Update heights
    root -> height = max(getHeight(root -> left),
                        getHeight(root -> right)) + 1;
    b -> height = max(getHeight(b -> left),
                    getHeight(b -> right)) + 1;
                        
    // Return new root
    return b;
}

Node* rightRotate(Node* root){
    Node *b = root -> left;
    Node *b1 = b -> right;
    
    // Perform rotation
    b -> right = root;
    root -> left = b1;
     
    // Update heights
    root -> height = max(getHeight(root -> left),
                        getHeight(root -> right)) + 1;
    b -> height = max(getHeight(b -> left),
                    getHeight(b -> right)) + 1;
                        
    // Return new root
    return b;
}

Node* balanced(Node* node){
    node -> height = 1 + max(getHeight(node -> left), getHeight(node -> right));
    int balance = getBalance(node);
    if(balance == 2){
    	if(getBalance(node -> left) >= 0) return rightRotate(node); // LL
    	node -> left = leftRotate(node -> left);
    	return rightRotate(node); // LR
    }else if(balance == -2){
    	if(getBalance(node -> right) <= 0) return leftRotate(node); // RR
    	node -> right = rightRotate(node -> right);
    	return leftRotate(node); // RL
    }
    return node;
}
    
Node* insert(Node* node, int key){
    if(!node) return new Node(key);
    if(key < node -> data) node -> left = insert(node -> left, key);
    else if(key > node -> data) node -> right = insert(node -> right, key);
    else return node; // avoid duplications
    return balanced(node);
}

Node *minValueNode(Node* node){
    Node* mi = node;
    while (mi -> left) mi = mi -> left;
    return mi;
}

Node* deletion(Node* node, int key){
	if(!node) return node;
	if(node -> data > key) node -> left = deletion(node -> left, key);
	else if(node -> data < key) node -> right = deletion(node -> right, key);
	else{
	    if(node -> left == NULL || node -> right == NULL){ // 0 or 1 child case
		Node *temp = node -> left ? node -> left : node -> right;
            	if (temp == NULL){ // no child case
                    temp = node;
                    node = NULL;
            	}
            	else // one child case
            	*node = *temp;
            	free(temp);
	    }else{ // 2 children case
		Node* temp = minValueNode(node -> right);
                node -> data = temp -> data;
                node -> right = deletion(node -> right, node -> data);
	    }
	}
	if(!node) return node;
	return balanced(node);
}

int main(){
    return 0;
}
