#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 // The number digit limitation

typedef struct _btnode
{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode; // You should not change the definition of BTNode

typedef struct _node
{
    BTNode *item;
    struct _node *next;
} StackNode;

typedef struct _stack
{
    int size;
    StackNode *head;
} Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode **root, char *prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr, BTNode *item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

int main()
{
    char prefix[SIZE];
    BTNode *root = NULL;

    printf("Enter an prefix expression:\n");
    scanf("%[^\n]s", prefix);

    createExpTree(&root, prefix);

    printf("The Infix Expression:\n");
    printTree(root);
    printf("\n");
    printf("The Postfix (Reverse Polish) Expression:\n");
    printTreePostfix(root);
    printf("\n");
    printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
    return 0;
}

void createExpTree(BTNode **root, char *prefix)
{
    const char space[2] = " ";
    char *token;
    token = strtok(prefix, space);

    Stack S;
    S.head = NULL;
    S.size = 0;

    while (token != NULL)
    {
        BTNode *newNode = (BTNode *)malloc(sizeof(BTNode));
        newNode->left = NULL;
        newNode->right = NULL;

        if (*token == '+' || *token == '-' || *token == '/' || *token == '*')
        {
            // 
            newNode->item = *token;
            if (isEmptyStack(S))
            {
                *root = newNode;
            }
            else
            {
                if (peek(S)->left == NULL)
                {
                    peek(S)->left = newNode;
                }
                else
                {
                    peek(S)->right = newNode;
                    pop(&S);
                }
            }
            push(&S, newNode);
        }
        else
        {
            newNode->item = atoi(token);
            if (peek(S)->left == NULL)
            {
                peek(S)->left = newNode;
            }
            else
            {
                peek(S)->right = newNode;
                pop(&S);
            }
        }
        token = strtok(NULL, space);
    }
}

void printTree(BTNode *node)
{
    if (node == NULL)
    {
        return;
    }

    printTree(node->left);
    if (node->item == '+' || node->item == '-' || node->item == '/' || node->item == '*')
    {
        printf("%c", node->item);
    }
    else
    {
        printf("%d", node->item);
    }
    printTree(node->right);
}

void printTreePostfix(BTNode *node)
{
    if (node == NULL)
    {
        return;
    }

    printTreePostfix(node->left);
    printTreePostfix(node->right);
    if (node->item == '+' || node->item == '-' || node->item == '/' || node->item == '*')
    {
        printf("%c", node->item);
    }
    else
    {
        printf("%d", node->item);
    }
}

double computeTree(BTNode *node)
{
    if (node == NULL)
    {
        return 0.0;
    }

    if (node->item == '+')
    {
        return (computeTree(node->left) + computeTree(node->right));
    }
    else if (node->item == '-')
    {
        return (computeTree(node->left) - computeTree(node->right));
    }
    else if (node->item == '*')
    {
        return (computeTree(node->left) * computeTree(node->right));
    }
    else if (node->item == '/')
    {
        return (computeTree(node->left) / computeTree(node->right));
    }
    else
    {
        return node->item;
    }
}

void push(Stack *sPtr, BTNode *item)
{
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if (sPtr == NULL || sPtr->head == NULL)
    {
        return 0;
    }
    else
    {
        StackNode *temp = sPtr->head;
        sPtr->head = sPtr->head->next;
        free(temp);
        sPtr->size--;
        return 1;
    }
}

BTNode *peek(Stack s)
{
    return s.head->item;
}

int isEmptyStack(Stack s)
{
    if (s.size == 0)
        return 1;
    else
        return 0;
}

void deleteTree(BTNode **root)
{
    BTNode *temp;
    if (*root != NULL)
    {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}