//CODE JAM TEMPLATES

// #TREES

#include <iostream> 
using namespace std; 

struct Node 
{ 
    int data; 
    struct Node* left, *right; 
    Node(int data) 
    { 
        this->data = data; 
        left = right = NULL; 
    } 
}; 

void printPostorder(struct Node* node) 
{ 
    if (node == NULL) 
        return; 
    printPostorder(node->left); 
    printPostorder(node->right); 
    cout << node->data << " "; 
} 

void printInorder(struct Node* node) 
{ 
    if (node == NULL) 
        return; 
    printInorder(node->left); 
    cout << node->data << " "; 
    printInorder(node->right); 
} 

void printPreorder(struct Node* node) 
{ 
    if (node == NULL) 
        return; 
    cout << node->data << " "; 
    printPreorder(node->left);  
    printPreorder(node->right); 
}

void Tree(vector<int>data) 
{ 
    struct Node *root = new Node(1); 

    Node* temp=root;
    for(i=1; i<data.length(); i++){
    	if(data[i] > Node){
	    	Node->left = new Node(data[i]);
	    	temp=Node->left;
	    }
	    if(data[i] <= Node){
	    	Node->right = new Node(data[i]);
	    	temp=Node->right;
	    }
    }

    root->left->left = new Node(4); 
    root->left->right = new Node(5);  
    printPreorder(root); 
    printInorder(root);  
    printPostorder(root); 
  
    return 0; 
} 


// #BST #Binary Search Tree

struct node* search(struct node* root, int key) 
{ 
    // Base Cases: root is null or key is present at root 
    if (root == NULL || root->key == key) 
       return root; 
     
    // Key is greater than root's key 
    if (root->key < key) 
       return search(root->right, key); 
  
    // Key is smaller than root's key 
    return search(root->left, key); 
} 

#include<stdio.h> 
#include<stdlib.h> 
   
struct node 
{ 
    int key; 
    struct node *left, *right; 
}; 
   
// A utility function to create a new BST node 
struct node *newNode(int item) 
{ 
    struct node *temp =  (struct node *)malloc(sizeof(struct node)); 
    temp->key = item; 
    temp->left = temp->right = NULL; 
    return temp; 
} 
   
// A utility function to do inorder traversal of BST 
void inorder(struct node *root) 
{ 
    if (root != NULL) 
    { 
        inorder(root->left); 
        printf("%d \n", root->key); 
        inorder(root->right); 
    } 
} 

struct node* insert(struct node* node, int key) 
{ 
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key); 
  
    /* Otherwise, recur down the tree */
    if (key < node->key) 
        node->left  = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key);    
  
    /* return the (unchanged) node pointer */
    return node; 
} 

int main() 
{ 
    /* Let us create following BST 
              50 
           /     \ 
          30      70 
         /  \    /  \ 
       20   40  60   80 */
    struct node *root = NULL; 
    root = insert(root, 50); 
    insert(root, 30); 
    insert(root, 20); 
    insert(root, 40); 
    insert(root, 70); 
    insert(root, 60); 
    insert(root, 80); 
   
    // print inoder traversal of the BST 
    inorder(root); 
   
    return 0; 
} 


// #HEAPSORT

#include <iostream> 
  
using namespace std; 

void heapify(int arr[], int n, int i) 
{ 
    int largest = i; // Initialize largest as root 
    int l = 2*i + 1; // left = 2*i + 1 
    int r = 2*i + 2; // right = 2*i + 2 
  
    // If left child is larger than root 
    if (l < n && arr[l] > arr[largest]) 
        largest = l; 
  
    // If right child is larger than largest so far 
    if (r < n && arr[r] > arr[largest]) 
        largest = r; 
  
    // If largest is not root 
    if (largest != i) 
    { 
        swap(arr[i], arr[largest]); 
  
        // Recursively heapify the affected sub-tree 
        heapify(arr, n, largest); 
    } 
}

void heapSort(int arr[], int n) 
{ 
    // Build heap (rearrange array) 
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i); 
  
    // One by one extract an element from heap 
    for (int i=n-1; i>=0; i--) 
    { 
        // Move current root to end 
        swap(arr[0], arr[i]); 
  
        // call max heapify on the reduced heap 
        heapify(arr, i, 0); 
    } 
}

void printArray(int arr[], int n) 
{ 
    for (int i=0; i<n; ++i) 
        cout << arr[i] << " "; 
    cout << "\n"; 
}

int main() 
{ 
    int arr[] = {12, 11, 13, 5, 6, 7}; 
    int n = sizeof(arr)/sizeof(arr[0]); 
  
    heapSort(arr, n); 
  
    cout << "Sorted array is \n"; 
    printArray(arr, n); 
}

// #Matrix Multiplication

#include<iostream>
using namespace std; 
int main ()
{
    int r1, c1, r2, c2, i, j, k;
    int A[5][5], B[5][5], C[5][5];
    cout << "Enter number of rows and columns of matrix A : ";
    cin >> r1 >> c1;
    cout << "Enter number of rows and columns of matrix B : ";
    cin >> r2 >> c2; 
    if (c1 != r2)
    {
        cout << "Matrices cannot be multiplied!";
        exit(0);
    }	
    cout << "Enter elements of matrix A : ";
    for (i = 0; i < r1; i++)
        for (j = 0; j < c1; j++)
            cin >> A[i][j];
    cout << "Enter elements of matrix B : ";
    for (i = 0; i < r2; i++)
        for (j = 0; j < c2; j++)
            cin >> B[i][j];		
    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c2; j++)
        {
            C[i][j] = 0;
            for (k = 0; k < r2; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    cout << "Product of matrices\n";
    for (i = 0; i < r1; i++)
    {    
        for (j = 0; j < c2; j++)
            cout << C[i][j] << "  ";
        cout << "\n";
    }
    return 0;
}

// #Pointer Reference

