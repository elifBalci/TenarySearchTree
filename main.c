/*
 *Elif BALCI 150117069
*/
#include <stdio.h>
#include <stdlib.h>

struct ts_tree{
    int data;
    struct ts_tree * right, * left, *middle;
};typedef struct ts_tree node;


int square(int data);
void print_preorder(node * tree);
void insert(node ** tree, int val);
node* search(node ** tree, int val);
void print_inorder(node * tree);
void print_postorder(node * tree);
int delete(node ** tree, int val);
int removeFromList(int value);

int number = 300;
int list[] ;

int main() {

    node *tree ;
    tree = NULL;
    char *str;
    int data;
    FILE *file;
    file = fopen( "input.txt" , "r");
    int counter =0;
    while (!feof(file)) {
        fscanf(file,"%s", str);
        data = atoi(str);
        insert(&tree, data);
        printf("in while number is %d\n", data);
        list[counter] = data;
        counter++;
    }

    printf(" Press 1 to print preorder \n 2 to print inorder \n 3 to print postorder \n 4 to search a node \n  5 to delete a node ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1)
        print_preorder(tree);
    if(choice == 2)
        print_inorder(tree);
    if(choice == 3)
        print_postorder(tree);
    if(choice == 4){
        printf("please enter the  value to be searched ");
        int val;
        scanf("%d",&val);
        node *node1;
        node1 = search(&tree,val);
        if(node1 != NULL){
            printf("Node has been found.");
            printf("node's middle is: %d, node's left is: %d, node's right is: %d \n", node1->middle->data, node1->left->data, node1->right->data);
        }

    }
    if(choice == 5){
        printf("please enter the  value to be delete ");
        int val;
        scanf("%d",&val);
        delete(&tree, val);
        print_inorder(tree);

    }


/*
    node *node1 = malloc(sizeof(node));
    node1 = search(&tree,40);
    printf("node's middle is : %d ", node1->middle->data);
    delete(&tree, 40);
*/

    return 0;
}



void insert(node ** tree, int val)
{
    node *temp = NULL;
    if(!(*tree)) {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        *tree = temp;
        return;
    }

    if(val < (*tree)->data) {
        insert(&(*tree)->left, val);
    }
    else if(val > (*tree)->data && val< square((*tree)->data)) {
        insert(&(*tree)->middle, val);
    }
    else if(val > square((*tree)->data)) {
        insert(&(*tree)->right, val);
    }

}

void print_preorder(node * tree) {
    if (tree) {
        printf("%d\n", tree->data);
        print_preorder(tree->left);
        print_preorder(tree->middle);
        print_preorder(tree->right);
    }
}

void print_postorder(node * tree){
    if (tree) {
        print_preorder(tree->left);
        print_preorder(tree->middle);
        print_preorder(tree->right);
        printf("%d\n",tree->data);

    }
}
void print_inorder(node * tree){
    if (tree) {
        print_inorder(tree->left);
        printf("%d\n",tree->data);
        print_inorder(tree->middle);
        print_inorder(tree->right);
    }
}

node* search(node ** tree, int val)
{
    if(!(*tree))
    {
        return NULL;
    }

    if(val < (*tree)->data) {
        search(&(*tree)->left, val);
    }
    else if(val > (*tree)->data && val< square((*tree)->data)) {
        search(&(*tree)->middle, val);
    }
    else if(val > square((*tree)->data)) {
        search(&(*tree)->right, val);
    }
    else if(val == (*tree)->data)
    {
        return *tree;
    }
}

int delete(node ** tree, int val){
    node *tempTree = malloc(sizeof(node));
    int number =0;
    removeFromList(val);
    while(list[number] != NULL){
        insert(&tempTree, list[number]);
        number++;
    }
    printf("HERE WE GO");
    print_preorder(tempTree);

}
int removeFromList(int value){
    int counter = 0;
    int counter2 = 0;
    while (list[counter] != NULL) {
        if (list[counter] == value) {
            list[counter] = NULL;
            counter2 = counter;
        }
        counter++;
    }
    while(list[counter2+1] != NULL){
        list[counter2] = list[counter2+1];
        counter2++;
    }

}

int square(int data) {
    return data*data;
}