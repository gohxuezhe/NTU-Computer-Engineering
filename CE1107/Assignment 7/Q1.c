#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
    struct _listnode *next;
} ListNode;

typedef struct _graph
{
    int V;
    int E;
    ListNode **list;
} Graph;

typedef ListNode QueueNode;

typedef struct _queue
{
    int size;
    QueueNode *head;
    QueueNode *tail;
} Queue;

int BFS(Graph G, int v, int w);

void printGraphList(Graph);

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);

int main()
{
    Graph g;
    int i, j;
    ListNode *temp;

    printf("Enter the number of vertices:\n");
    scanf("%d", &g.V);

    g.list = (ListNode **)malloc(g.V * sizeof(ListNode *));

    for (i = 0; i < g.V; i++)
        g.list[i] = NULL;

    printf("Enter two vertices which are adjacent to each other:\n");
    while (scanf("%d %d", &i, &j) == 2)
    {
        i = i - 1;

        if (g.list[i] == NULL)
        {
            g.list[i] = (ListNode *)malloc(sizeof(ListNode));
            g.list[i]->vertex = j;
            g.list[i]->next = NULL;
        }
        else
        {
            temp = (ListNode *)malloc(sizeof(ListNode));
            temp->next = g.list[i];
            temp->vertex = j;
            g.list[i] = temp;
        }
        g.E++;
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    scanf("%*c");
    printf("Enter two vertices for finding their shortest distance:\n");
    scanf("%d %d", &i, &j);

    int d = BFS(g, i, j);

    if (d == -1)
        printf("%d and %d are unconnected.\n", i, j);
    else
        printf("The shortest distance is %d\n", d);
    printGraphList(g);
    return 0;
}

int BFS(Graph g, int v, int w)
{
    Queue q;
    q.size = 0;
    q.head = NULL;
    q.tail = NULL;

    int currentVertex;
    ListNode *adjNode;

    int *visitV;
    visitV = (int *)malloc(sizeof(int) * g.V);
    for (int i = 0; i < g.V; i++)
    {
        visitV[i] = 0;
    }

    int *dist;
    dist = (int *)malloc(sizeof(int) * g.V);
    for (int i = 0; i < g.V; i++)
    {
        dist[i] = -1;
    }

    enqueue(&q, v);
    visitV[v - 1] = 1;
    dist[v - 1] = 0;

    while (!isEmptyQueue(q))
    {
        currentVertex = getFront(q);
        adjNode = g.list[currentVertex - 1];

        dequeue(&q);
        while (adjNode != NULL)
        {
            if (visitV[adjNode->vertex - 1] == 0)
            {
                enqueue(&q, adjNode->vertex);
                visitV[adjNode->vertex - 1] = 1;
                dist[adjNode->vertex - 1] = dist[currentVertex - 1] + 1;
            }
            adjNode = adjNode->next;
        }
    }
    return dist[w - 1];
}

void printGraphList(Graph g)
{
    int i;
    ListNode *temp;

    for (i = 0; i < g.V; i++)
    {
        printf("%d:\t", i + 1);
        temp = g.list[i];
        while (temp != NULL)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void enqueue(Queue *qPtr, int item)
{
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if (newNode == NULL)
        exit(0);

    newNode->vertex = item;
    newNode->next = NULL;

    if (isEmptyQueue(*qPtr))
        qPtr->head = newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr)
{
    if (qPtr == NULL || qPtr->head == NULL)
    { //Queue is empty or NULL pointer
        return 0;
    }
    else
    {
        QueueNode *temp = qPtr->head;
        qPtr->head = qPtr->head->next;
        if (qPtr->head == NULL) //Queue is emptied
            qPtr->tail = NULL;

        free(temp);
        qPtr->size--;
        return 1;
    }
}

int getFront(Queue q)
{
    return q.head->vertex;
}

int isEmptyQueue(Queue q)
{
    if (q.size == 0)
        return 1;
    else
        return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
    while (dequeue(qPtr))
        ;
}
