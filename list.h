#ifndef LIST_H
#define LIST_H

typedef struct Node{
    void *data;
    struct Node *next;
}Node;

Node *createNode(void)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    return newNode;
}

Node *insertNode(Node *list, void *data)
{
    Node *newNode;

    if(!list)
        return NULL;

    newNode = createNode();
    newNode->data = data;

    if(!(list->next))
        list->next = newNode;
    else{
        Node *it = list;
        while(it->next)
            it = it->next;
        it->next = newNode;
    }

    return list;
}



void printList(Node *list, void (*printer)(void *data))
{
    Node *it = list->next;
    while(it)
    {
        printer(it->data);
        it = it->next;
    }
}

#endif // LIST_H
