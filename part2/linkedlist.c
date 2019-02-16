//
// Created by panos and amanda on 2/15/19.
//

pthread_mutex_t lockQ[4] = {PTHREAD_MUTEX_INITIALIZER}; // initializes lock
pthread_cond_t condQ[4] = PTHREAD_COND_INITIALIZER; // initilize condition

typedef struct Node
{
    argstruct *args;
    struct Node *next;
} Node;

int numOfQ[APPRMAX];
Node *q[APPRMAX] = {NULL};

Node *getLast(Node *n) {
    if (n == NULL)
        return n;
    while (n->next != NULL)
        n = n->next;
    return n;
}

Node *newNode() {
    Node *n = (Node *) malloc(sizeof(Node));
    n->args=NULL;
    n->next=NULL;
    return n;
}

int checkIfFirst(argstruct *args) {
    return q[args->approachDir]->args == args;
}

void addLast(argstruct *args, Node *queue) {
    Node *last = getLast(queue); // get last node
    Node *new = newNode(); // allocate new node
    new->args = args; // populate new node
    if (last == NULL)
        q[args->approachDir] = new;
    else
        last->next = new; // link last to new
}

void push(argstruct *args, Appr dir) {
    addLast(args, q[dir]);
    numOfQ[dir]++;
}

void pop(argstruct *args, Appr dir) {
    if (args == q[dir]->args) {
        Node *deleted = q[dir];
        q[dir] = q[dir]->next;
        free(deleted);
        numOfQ[dir]--;
    } else {
        printf("Error. Thread %d invalid pop\n", args->threadNum);
    }
}
