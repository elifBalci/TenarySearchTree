#include <stdio.h>
#include <stdlib.h>

struct ts_tree{
    int *data;
    struct ts_tree * right, * left, *middle;
};typedef struct ts_tree node;


int square(int data);
void print_preorder(node * tree);
void insert(node ** tree, int val);
node* search(node ** tree, int val);
void print_inorder(node * tree);
void print_postorder(node * tree);
int delete(node ** tree, int val); //ekstra function , alternative to remove
int removeFromList(int value);
node* returnValues(node * tree, int value);
node *removeNode (int key, node *p);
node * findMax(node *p);
node *findMaxOfLeft(node *p);


//variables for alternative delete function which has a alternative "remove" function. They do the same in different ways.
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
        //printf("in while number is %d\n", data);
        list[counter] = data;
        counter++;
    }

    int exit = 0;
    while(exit == 0) {
        printf(" Press 1 to print preorder \n 2 to print inorder \n 3 to print postorder \n 4 to search a node \n 5 to delete a node\n 6 to exit\n ");
        int choice;
        scanf("%d", &choice);

        if (choice == 1)
            print_preorder(tree);
        if (choice == 2)
            print_inorder(tree);
        if (choice == 3)
            print_postorder(tree);
        if (choice == 4) {
            printf("please enter the  value to be searched ");
            int val;
            scanf("%d", &val);
            node *node1;
            node1 = search(&tree, val);
            if (node1 != NULL) {
                printf("Node has been found.");
                printf("node's middle is: %d, node's left is: %d, node's right is: %d \n", node1->middle->data,
                       node1->left->data, node1->right->data);
            }

        }
        if (choice == 5) {
            printf("please enter the  value to be delete ");
            int val;
            scanf("%d", &val);
            //delete(&tree, val);
            tree = removeNode(val, tree);
            print_inorder(tree);
            printf("++++++++++++++++++++++++ post order\n");
            print_postorder(tree);
            printf("++++++++++++++++++++++++ preorder\n");
            print_preorder(tree);
        }
        if(choice == 6){
            exit = 1;
        }

    }
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
        if(tree->data != 0)
            printf("%d\n", tree->data);
        print_preorder(tree->left);
        print_preorder(tree->middle);
        print_preorder(tree->right);
    }
}

void print_postorder(node * tree){
    if (tree) {
        print_postorder(tree->left);
        print_postorder(tree->middle);
        print_postorder(tree->right);
        if(tree->data != 0)
            printf("%d\n",tree->data);

    }
}
void print_inorder(node * tree){
    if (tree) {
        print_inorder(tree->left);
        if(tree->data != 0)
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

    if(val < (*tree)->data && (*tree)->data != NULL) {
        search(&(*tree)->left, val);
    }
    else if(val > (*tree)->data && val< square((*tree)->data) && (*tree)->data != NULL) {
        search(&(*tree)->middle, val);
    }
    else if(val > square((*tree)->data)  && (*tree)->data != NULL) {
        search(&(*tree)->right, val);
    }
    else if(val == (*tree)->data  && (*tree)->data != NULL)
    {
        return *tree;
    }
}

node* returnValues(node *tree, int value){
    int array[100] ;
    node *newTree = search(&tree, value);
    if (tree) {
        returnValues(tree->left, value);
        returnValues(tree->middle, value);
        returnValues(tree->right, value);
        printf("++++++++++++++++++++++++++++++++++++++++++\n");
        printf("%d\n",tree->data);
        if(tree->data != value)
            insert(&newTree, tree->data);
        /* int i =0 ;
         while(array[i] != NULL)
             i++;
         array[i] = tree->data;*/
        return  &array;
    }
}


//An alternative way of removing nodes.
int delete(node ** tree, int val){
    node *tempTree = malloc(sizeof(node));
    int number =0;
    removeFromList(val);
    while(list[number] != NULL){
        insert(&tempTree, list[number]);
        number++;
    }
    print_preorder(tempTree);
    node * new =returnValues(tree, val);
    print_inorder(new);


}


node *removeNode (int key, node *p)
{// returns a pointer to node replacing the node removed.
    node *temp;
    node *tmp2;

    //Navigate to key's node
    if (p == NULL)
        return NULL;
    if (key < p->data)
        p->left = removeNode(key,p->left);
    else if (key > p->data && key < square (p->data)) {
        p->middle = removeNode(key, p->middle);
    }
    else if( key > square (p->data)){
        p ->right =removeNode(key, p->right);
    }

    //delete
    //if node only has one child
    else if(p->right && !p->middle && !p->left){
        p = p->right;
    }
    else if(!p->right && p->middle && !p->left){
        p = p->middle;
    }
    else if(!p->right && !p->middle && p->left){
        p = p->left;
    }
    //if node has more than one child
    else if(p->left){
        node *temp3;
        temp3 = findMax(p);
        p->data = temp3->data;
        printf("it will be replaced by : %d\n", temp3->data);
        free(temp3);
    }

    //if node is a leaf
    else if(!p->middle && !p->left && !p->right ){
        p = NULL;
    }
    return p;
}

node * findMax(node *p){
    node *temp;
    if (p->left) {
        temp = p->left;
        temp = findMaxOfLeft(p->left);
    }
    return temp ;
}


node *findMaxOfLeft(node *p){
    node * temp;
    temp = p;
    while(temp->right || temp->middle){
        if(temp->right)
            temp = temp->right;
        else if(temp->middle)
            temp = temp->middle;
    }

    return temp;
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
