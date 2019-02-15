//
// Created by panos and amanda on 2/15/19.
//

typedef struct Node
{
    argstruct *args;
    struct Node *next;
} Node;

Node *northQ = NULL;
Node *southQ = NULL;
Node *westQ = NULL;
Node *eastQ = NULL;

Node *getLast(Node *head) {
    Node *n = head;
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

void addLast(argstruct *args, Node *queue) {
    Node *last = getLast(queue); // get last node
    Node *new = newNode(); // allocate new node
    new->args = args; // populate new node
    last->next = new; // link last to new
}

void pushNorth(argstruct *args) {
    addLast(args, northQ);
}

void popNorth() {
    Node *deleted = northQ;
    northQ = northQ->next;
    free(deleted);
}

void pushSouth(argstruct *args) {
    addLast(args, southQ);
}

void popSouth() {
    Node *deleted = southQ;
    southQ = southQ->next;
    free(deleted);
}

void pushWest(argstruct *args) {
    addLast(args, westQ);
}

void popWest() {
    Node *deleted = westQ;
    westQ = westQ->next;
    free(deleted);
}

void pushEast(argstruct *args) {
    addLast(args, eastQ);
}

void popEast() {
    Node *deleted = eastQ;
    eastQ = eastQ->next;
    free(deleted);
}