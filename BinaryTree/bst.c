/*Author: Bobby Purcell
 *Course: CSC386    Date: 2/8/16
 *Desc: Creates Binary Tree of nodes holding integer values
 *      based on user input from command line. Traverses and
 *      prints tree after each addition.
 *      Adds iteratively, prints recursively.
 */
#include <stdlib.h>
#include <stdio.h>

/* declare struct type tree_node*/
typedef struct tree_node {
    int value;
    struct tree_node *left;
    struct tree_node *right;
} tree_node;

/* root of the tree */
tree_node *root = NULL;

/*Adds values to tree*/
void add(int element) {
    tree_node *temp;
    //temp = malloc(sizeof(tree_node));//
    tree_node *parent;
    parent = malloc(sizeof(tree_node));
    if (root == NULL) {
        root = malloc(sizeof(tree_node));
        root->value = element;
        root->left = NULL;
        root->right = NULL;
        //   printf("element assigned to root:\t%d\n", element);//feedback on root creation
    } else {
        temp = root;
        while (temp != NULL) {
            if (element <= temp->value) {
                parent = temp;
                temp = temp->left;
                //     printf("element\'%d\': moved left\t \n", element);//feedback on movement through tree
            } else {
                parent = temp;
                temp = temp->right;
                //printf("element \'%d\': moved right \n", element);//feedback on movement through tree
            }
        }
        tree_node *node = NULL;
        node = malloc(sizeof(tree_node));
        node->value = element;
        node->left = NULL;
        node->right = NULL;
        if (element <= parent->value) {
            parent->left = node;
        }
        else {
            parent->right = node;
        }
    }

}

/**
 *	This function performs a pre-order traversal of a tree whose root is
 *	pointed by the pointer parameter of the function.
 */
void preorder_traverse(tree_node *curr_node) {
    if (curr_node == NULL) {
        return;
    }
    printf("%d ", curr_node->value);
    preorder_traverse(curr_node->left);
    preorder_traverse(curr_node->right);
}

/* Recursively deletes tree from memory*/
tree_node *destroy_tree(tree_node *curr_node) {
    if (curr_node == NULL) return NULL;
    free(destroy_tree(curr_node->left));
    free(destroy_tree(curr_node->right));
    return curr_node;
}

int main() {
    int i = 0;
    printf("Binary Tree\nInput negative number to exit.\n");
    while (i >= 0) {
        printf("\nEnter an int: ");
        scanf("%d", &i);
        if (i >= 0) {
            add(i);
            preorder_traverse(root);
        } else {
            printf("Input negative: Exiting.");
        }
    }
    free(destroy_tree(root));
    return EXIT_SUCCESS;
}