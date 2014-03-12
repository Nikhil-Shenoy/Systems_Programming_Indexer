#ifndef SORTED_LIST_H
#define SORTED_LIST_H
#include <stdlib.h>

struct Node
{
    char * name;
	int refcount;
	void *data;
	struct Node *next;
};

typedef struct Node Node;
typedef Node* NodePtr;

typedef int (*CompareFuncT)(void *, void *);
struct SortedList
{
	Node *head;
	CompareFuncT compareTo;
};

typedef struct SortedList SortedList;
typedef struct SortedList* SortedListPtr;

struct SortedListIterator
{
    Node *current;
};
typedef struct SortedListIterator SortedListIterator;
typedef struct SortedListIterator* SortedListIteratorPtr;


/*----------------------------------------------------------------------*/

NodePtr NodeCreate(void *newObj, char*name); // done
void NodeDestroy(NodePtr myNode); // done


SortedListPtr SLCreate(CompareFuncT cf); // done
void SLDestroy(SortedListPtr list); // done
int SLInsert(SortedListPtr list, void *newObj, char*key); //done
int Insert(SortedListPtr, void*newObj, char*key);
int SLRemove(SortedListPtr list, char * key); //done



SortedListIteratorPtr SLCreateIterator(SortedListPtr list);
void SLDestroyIterator(SortedListIteratorPtr iter);
void *SNextItem(SortedListIteratorPtr iter);

#endif
