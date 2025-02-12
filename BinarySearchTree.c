#include <stdio.h>
#include <stdlib.h>

// Hamza Gunes - 29/12/2024 - Binary Search Tree.

struct Tree{
	
	int key;
	struct Tree *left;
	struct Tree *right;
};

struct Tree* CreateNode(int key){
	
	struct Tree *New = (struct Tree*)malloc(sizeof(struct Tree));
	New->key= key;
	New->left = NULL;
	New->right = NULL;
	return New;
	
}

void printTree(struct Tree *root, int space) {
	
    if (root == NULL)
        return;

    space += 5;

    printTree(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("%d\n", root->key);

    printTree(root->left, space);
}

void AddToTree(struct Tree **root, int key){
	
	struct Tree *back = NULL;
	struct Tree *temp = *root;
	
	while(temp != NULL){
		
		back = temp;
	
	if(key > temp->key){
		
		temp = temp->right;
	}
	else if(key < temp->key){
		
		temp = temp->left;
	}
	else{
		
		temp->key = key;
		return;
	}
	
	}
	
	if(key > back->key){
		
		back->right = CreateNode(key);
	}
	else if(key < back->key){
		
		back->left = CreateNode(key);
	}
	
}

void DeleteFromTree(struct Tree **root, int key){
	
	struct Tree *temp = *root;
	
	if(temp->key == key && temp->left == NULL && temp->right == NULL){
		
		printf("You can't delete root... Please create nodes.");
		return;
	}
	if(temp->key == key && temp->left != NULL && temp->right == NULL){
		
		*root = temp->left;
		free(temp);
		return;
	}
	if(temp->key == key && temp->left == NULL && temp->right != NULL){
		
		*root = temp->right;
		free(temp);
		return;
	}
	
	struct Tree *parent = NULL;
	
	while(temp != NULL && temp->key != key){
		
		parent = temp;
		
		if(key > temp->key){
			
			temp = temp->right;
		}
		else if(key < temp->key){
			
			temp = temp->left;
		}
		
	}
	
	if(temp == NULL){
		
		printf("Key Error...");
		return;
	}
	
	if(temp->left == NULL && temp->right == NULL){
		
		free(temp);
		if(parent->left == temp){
			parent->left = NULL;
		}
		else if(parent->right == temp){
			parent->right = NULL;
		}
		
	}
	else if(temp->left != NULL && temp->right == NULL || temp->left == NULL && temp->right != NULL){
		
		struct Tree *next = temp;
		
		if(temp->left != NULL){
			
			next = temp->left;
		}
		else if(temp->right != NULL){
			
			next = temp->right;
		}
		
		free(temp);
		if(next->key > parent->key){
			
			parent->right = next;
		}
		else if(next->key < parent->key){
			
			parent->left = next;
		}
		
	}
	else if(temp->left != NULL && temp->right != NULL){
		
		struct Tree *iter = temp->right;
		
		struct Tree *parent2 = temp;
		while(iter->left != NULL){
			
			parent2 = iter;
			iter = iter->left;
		}
		
		temp->key = iter->key;
		
		if(iter->left == NULL && iter->right == NULL){
			
			parent2->left = NULL;
			free(iter);
		}
		else if (parent2 == temp){
					
			parent2->right = iter->right;
			free(iter);
		}
		else{
			
			parent2->left = iter->right;
			free(iter);
		}
		
		
	}
	
}

int Count_Single_Child_Nodes(struct Tree *root) {
	
    if (root == NULL) {
        return 0; 
    }


    int single_child = (root->left != NULL && root->right == NULL) || 
                    (root->left == NULL && root->right != NULL);
                    

    return single_child + Count_Single_Child_Nodes(root->left) + Count_Single_Child_Nodes(root->right);
}

void FreeTree(struct Tree *root) {
	
    if (root == NULL) {
    	
        return;
    }

    FreeTree(root->left);
    FreeTree(root->right);
    
    printf("Freeing node with key: %d\n", root->key);
    free(root);
}

int main(){
	
	struct Tree *root = CreateNode(10);
	root->left = CreateNode(5);
	root->right = CreateNode(15);
	AddToTree(&root,12);
	AddToTree(&root,2);
	AddToTree(&root,7);
	AddToTree(&root,12);
	AddToTree(&root,20);
	AddToTree(&root,22);
	AddToTree(&root,24);
	DeleteFromTree(&root,10);
	printTree(root,0);
	
	printf("\nnumber of single child nodes = %d\n\n",Count_Single_Child_Nodes(root));
	
	FreeTree(root);
	root = NULL;
	
	
	
}