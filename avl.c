#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int valor;
	int height;
	struct node *left;
	struct node *right;
}Node;

int max(int a, int b){
	if (a > b){
		return a;
	}
	else{
		return b;
	}
}

int getHeight(Node* root){
	if(root == NULL){
		return 0;
	} 
	return root->height;

}

Node *rightRotate(Node *node){
	Node *T1 = node->left;
	Node *T2 = T1->right;

	T1->right = node;
	node->left = T2;

	node->height = max(getHeight(node->left), getHeight(node->right));
	T1->height = max(getHeight(T1->left), getHeight(T1->right));

	return T1;
}

Node *leftRotate(Node *node){
	Node *T1 = node->right;
	Node *T2 = T1->left;

	T1->left = node;
	node->right = T2;

	node->height = max(getHeight(node->left), getHeight(node->right));
	T1->height = max(getHeight(T1->left), getHeight(T1->right));

	return T1;
}

/*struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    // Return new root
    return x;
}*/

Node *newNode(int num){
	Node* node = (Node*)malloc(sizeof(Node));
	node->valor   = num;
	node->left   = NULL;
	node->right  = NULL;
	node->height = 1;  // new node is initially added at leaf
	return node;
}

int getBalance(Node* n){
	if(n==NULL){
		return 0;
	}
	return getHeight(n->left) - getHeight(n->right);
}

Node *insert(Node *node, int valor){
	if(node == NULL){
		return(newNode(valor));
	}
	if(valor < node->valor){
		node->left = insert(node->left, valor);
	}
	else if(valor > node->valor){
		node->right = insert(node->right, valor);
	}
	else{
		return node;
	}
	node->height = 1+ max(getHeight(node->left), getHeight(node->right));
	return node;

	 int balance = getBalance(node);

	 if(balance > 1 && valor < node->left->valor){
		 return rightRotate(node);
	 }
	 if(balance < -1 && valor > node->right->valor){
		 return leftRotate(node);
	 }
	 if(balance > 1 && valor > node->left->valor){
		 node->left = leftRotate(node->left);
		 return rightRotate(node);
	 }
	 if(balance < -1 && valor < node->right->valor){
		 node->right = rightRotate(node->right);
		 return leftRotate(node);
	 }

	return node;
}

void inOrder(Node *root)
{
    if(root != NULL)
    {
        inOrder(root->left);
	printf("%d ", root->valor);
        inOrder(root->right);
    }
}


void destroy(Node *root)
{
    Node *temp;
    temp = root;
    if(root != NULL)
    {
	
        destroy(temp->left);
	free(root);
        destroy(temp->right);
    }
}

int main(){
	Node *root = NULL;		

	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 30);
	root = insert(root, 40);
	root = insert(root, 50);
	root = insert(root, 25);

	inOrder(root);
	printf("\n");
	destroy(root);
	return 0;
}