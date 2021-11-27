#include <stdio.h>
#include <stdlib.h>

#define SIZE 80 // The size of the array

enum ExpType
{
    OPT,
    OPERAND
};

typedef struct _stackNode
{
    char item;
    struct _stackNode *next;
} StackNode;

typedef struct _stack
{
    int size;
    StackNode *head;
} Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int item;
    enum ExpType type;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist
{
    int size;
    ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item, enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList(LinkedList ll);

void in2PreLL(char *infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];

    printf("Enter an infix expression:\n");
    scanf("%s", infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

// find priority of operator
int getPriority(char c)
{
    if (c == '-' || c == '+')
    {
        return 1;
    }
    else if (c == '*' || c == '/')
    {
        return 2;
    }
    return 0;
}

void in2PreLL(char *infix, LinkedList *inExpLL)
{
    Stack S;
    S.head = NULL;
    S.size = 0;

    int infixLength = 0;
    while (infix[infixLength] != '\0')
    {
        infixLength++;
    }

    for (int i = infixLength; i >= 0; i--)
    {
        if (infix[i] >= 48 && infix[i] <= 57)
        {
            int j = i;
            int currentOperand = 0;
            int currentMultiplier = 1;

            while (infix[j] > 47 && infix[j] != '\0' && j >= 0)
            {
                currentOperand += (infix[j] - '0') * currentMultiplier;
                currentMultiplier *= 10;
                j--;
            }
            insertNode(inExpLL, currentOperand, OPERAND);
            i = j + 1;
        }
        else if (infix[i] == ')')
        {
            push(&S, ')');
        }
        else if (infix[i] == '(')
        {
            while (peek(S) != ')')
            {
                insertNode(inExpLL, peek(S), OPT);
                pop(&S);
            }
            pop(&S);
        }
        else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '/' || infix[i] == '*')
        {
            while (!isEmptyStack(S) && (getPriority(peek(S)) > getPriority(infix[i])))
            {
                insertNode(inExpLL, peek(S), OPT);
                pop(&S);
            }
            push(&S, infix[i]);
        }
    }
    while (!isEmptyStack(S))
    {
        insertNode(inExpLL, peek(S), OPT);
        pop(&S);
    }
}

void printExpLL(LinkedList inExpLL)
{
    ListNode *temp = NULL;
    temp = inExpLL.head;
    while (temp != NULL)
    {
        if (temp->type == OPERAND)
            printf(" %d ", temp->item);
        else
            printf(" %c ", (char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type)
{
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if (newNode == NULL)
        exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head = newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr)
{
    if (LLPtr == NULL || LLPtr->size == 0)
    {
        return 0;
    }
    else
    {
        ListNode *temp = LLPtr->head;
        LLPtr->head = LLPtr->head->next;

        free(temp);
        LLPtr->size--;
        return 1;
    }
}

int isEmptyLinkedList(LinkedList ll)
{
    if (ll.size == 0)
        return 1;
    else
        return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
    while (deleteNode(LLPtr))
        ;
}

void push(Stack *sPtr, char item)
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

char peek(Stack s)
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