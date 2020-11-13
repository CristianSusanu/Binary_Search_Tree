//This program implements a binary search tree for integers

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include "bst.h"

//Function to create a new node
Node* newNode(int value){
    Node* root = (Node *)malloc(sizeof(Node));
    root->data = value;
    root->left = NULL;
    root->right = NULL;
    return root;
}

//Function used to insert a new node in the tree, as a leaf node
Node* insertNode(Node *root, int value){
    if(root == NULL) {
        root = newNode(value);
    } else{
        if(root != NULL){
            if(root->data < value){
                root->right = insertNode(root->right,value);
            }
            else if(root->data > value){
                    root->left = insertNode(root->left, value);
                }
        }
    }
    return root;
}

//Looks for the smallest value in the hierarchy, starting from node N
Node* minVal(Node* N){
    Node* temp = N;
    while(temp && temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}

//Function used to delete an existing node in the tree
Node* deleteNode(Node *root, int value){
    if (root == NULL){
        return root;
    }
    if  (value < root->data && root != NULL){
        root->left = deleteNode(root->left, value);
    } else if (value > root->data && root != NULL){
        root->right = deleteNode(root->right, value);
    }
    else{
        if(root->left == NULL){
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL){
            Node *temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = minVal(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

//function for Inorder printing of the node values
void printSubtree(Node *N){
    if(N != NULL){
        if(N->left){
            printSubtree(N->left);
        }
        printf("%d\n",N->data);
        if(N->right){
            printSubtree(N->right);
        }
    } else return;
}

//Function that returns the number of nodes in the subtree rooted at node N
int countNodes(Node *N){
    if(N == NULL){
        return;
    } else return 1 + countNodes(N->left) + countNodes(N->right);
}

//Function that deallocates the entire subtree rooted at N
Node* freeSubtree(Node *N){

    if(N != NULL){
        if(N->left != NULL){
            freeSubtree(N->left);
        }
        if(N->right != NULL){
            freeSubtree(N->right);
        }
    } else {
        return NULL;
    }
    free(N);
    return NULL;
}

//This function traverses the tree inorder and stores the node values into an array
int printSubtree2Array(Node *N, int ar[], int ind){
    if(N != NULL){
        if(N->left){
            ind = printSubtree2Array(N->left, ar, ind);
        }
        ar[ind] = N->data;
    	ind++;
        if(N->right){
            ind = printSubtree2Array(N->right, ar, ind);
        }
        return ind;
    } else return ind;
}

Node* sortedArray2BST(int ar[], int start, int end){
    if(start > end)
        return NULL;
    int middle = (start + end)/2;
    Node* root = newNode(ar[middle]);
    root->left = sortedArray2BST(ar,start,middle-1);
    root->right = sortedArray2BST(ar,middle+1,end);
    return root;
}

int sumSubtree(Node *N){
	if(N != NULL)
        return (N->data + sumSubtree(N->left) + sumSubtree(N->right));
    else return 0;
}

// This functions converts an unbalanced BST to a balanced BST
Node* balanceTree(Node* root)
{
    int i;
    int *arr=NULL;
    Node *root2=NULL;

    int size = countNodes(root);
    arr = calloc(size, sizeof(int));
    printSubtree2Array(root, arr, 0);
    root2 = sortedArray2BST(arr, 0, size-1);
    free(arr);
    return root2;
}
