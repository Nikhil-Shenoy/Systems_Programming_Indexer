#include <stdio.h>
#include <stdlib.h>
#include "sl.h"
#include <string.h>

SortedListPtr SLCreate(CompareFuncT cf)
{
    SortedListPtr newPtr;
	newPtr = (SortedListPtr) malloc(sizeof(struct SortedList));
    
    newPtr->head = NULL;
    newPtr->compareTo = cf;
   
/*    newPtr->SortedListIteratorPtr = NULL;*/

	printf("Finished making the sorted list.\n");
 
	return newPtr;
}
        
    
void SLDestroy(SortedListPtr list)
{
    Node *cur = list->head;
    
    while(cur != NULL)
    {
	list->head = list->head->next; /*Move the head forward*/
	cur->next = NULL; /*Disconnect cur*/
	NodeDestroy(cur); /*Destroy the disconnected node*/
	cur = list->head; /*point cur to the new head*/ 
    }
 
    free(list);

	printf("Destroying myList\n");
    return;
}

NodePtr NodeCreate(void *newObj, char*name)
{
    
	NodePtr newPtr = (NodePtr) malloc(sizeof(Node));
   
    newPtr->name = name;
	newPtr->data = newObj;
	newPtr->next = NULL;
	newPtr->refcount = 0;

	printf("Finished making the node.\n");

	return newPtr;
}

void NodeDestroy(NodePtr myNode)
{
	free(myNode);
	printf("Destroying myNode\n");

	return;
}




/* Inserts given object into the list while maintaining sorted order. Success returns 1,
	failure returns 0 */
    
int SLInsert(SortedListPtr list, void *newObj, char*key)
{
	if(list->head == NULL)
	{
		NodePtr newNode = NodeCreate(newObj, key);
		list->head = newNode;
		list->head->refcount += 1;
		printf("Leaving SLInsert Data is: %d\n", *((int*)list->head->data));
			

		return 1;
	}
	else if(list->head != NULL)
	{


		NodePtr cur = list->head;
		NodePtr prev = NULL;
        int comp = (int)strcmp(cur->name, key);
        while (cur->next!=NULL && comp!=0) {
            prev = cur;
            cur = cur->next;
            comp = (int)strcmp(cur->name, key);
        }
		
        
        if (comp==0) {
           
            *((int*)cur->data) = *((int*)cur->data) + 1;
            printf("%d\n", *(int*)cur->data);
           
           SLRemove(list, key);
           Insert(list, cur->data , key);
        }
        else{
          
            NodePtr nu = NodeCreate(newObj, key);
            cur->next = nu;
        }


    }
    return 1;
}


int Insert(SortedListPtr list, void *newObj, char*key){
            if(list->head==NULL)
            {
                NodePtr newNode = NodeCreate(newObj, key);
                
                list->head = newNode;
                
                
                printf("Leaving SLInsert\n");
                
                
                return 1;
            }
            else 
            {
                
                
                NodePtr cur = (NodePtr)malloc(sizeof(Node));
                cur = list->head;
                
               
                NodePtr prev = NULL;
                
                
                /*Move the cur and prev pointers until cur points to the node where the newObj
                 should be inserted and prev points to the node before that point. */
                
                CompareFuncT comp  = list->compareTo;
                int aa = comp(newObj, cur->data);
                if(aa < 0)
                {
                    
                    
                    NodePtr newNode = NodeCreate(newObj, key);
                    
                    newNode->next = cur;
                    
                    list->head = newNode;
                    newNode->refcount += 1;
                    printf("Leaving SLInsert\n");
                    
                    
                    
                    return 1;
                }
                else
                {
                    
                    while((cur != NULL) && (list->compareTo(newObj,cur->data)) >= 0)
                    {
                        if(newObj == cur->data)
                        {
                            printf("Duplicates are not stored in this list\n");
                            return 1;
                        }
                        prev = cur;
                        cur = cur->next;
                    }
                    
                    
                    NodePtr newNode = NodeCreate(newObj, key);
                    /*Insert*/
                    
                    
                    prev->next = newNode;
                    
                    newNode->refcount += 1;
                    
                    newNode->next = cur;
                    
                    printf("Leaving SLInsert\n");
                    
                    return 1;
                }
            }
                    }
        
        


int SLRemove(SortedListPtr list, char * key)
{
	printf("Entering SLRemove\n");

	if(list->head==NULL)
	{
		printf("Leaving SLRemove\n");
		return 0; // remove failed
	}
	else 
	{
   
		NodePtr cur = list->head;
		NodePtr prev = NULL;
        int comp = strcmp(cur->name, key);
		while (cur->next!=NULL && comp!=0) {
            cur = cur->next;
            prev = cur;
            comp = (int)strcmp(cur->name, key);
        }

		if (comp==0 && prev!=NULL) {
            prev->next = NULL;
            prev->next = cur->next;
            cur->next = NULL;
            NodeDestroy(cur);
        }
        else{
            NodeDestroy(cur);
            list->head = NULL;
        }
    }
    return 1;
}


SortedListIteratorPtr SLCreateIterator(SortedListPtr list)
{
	printf("Enter SLCreateIterator\n");

	SortedListIteratorPtr  init = (SortedListIteratorPtr) malloc(sizeof(SortedListIterator));

	init->current = list->head;

	if(init->current != NULL)
		init->current->refcount += 1;

	printf("Leaving SLCreateIterator\n");
	
	return init;
}


void SLDestroyIterator(SortedListIteratorPtr iter)
{
	printf("Enter SLDestroyIterator\n");
	iter->current->refcount -= 1;
	iter->current = NULL; 
	free(iter);
	printf("Leaving SLDestroyIterator\n");
	return;
}



void *SNextItem(SortedListIteratorPtr iter)
{
	printf("Enter SLNextItem\n");
	if (iter->current->next==NULL)
    	{
		void *temp = iter->current->data;
		iter->current = iter->current->next;	
		printf("Here?\n");	
	
		return temp;
   	} 
	void *temp = iter->current->data;

	iter->current->refcount -= 1;

	if(iter->current->refcount==0)
	{
		printf("sup\n");
		NodePtr tomp = iter->current;

		iter->current = iter->current->next;
		iter->current->refcount += 1;
		tomp->next = NULL;
		NodeDestroy(tomp);
		printf("Leaving SLNextItem\n");
		return temp;
	} 

	else if(iter->current->refcount >= 1)
	{
		printf("sup2\n");

		iter->current = iter->current->next; // Move to the next node
		iter->current->refcount += 1;
		
		printf("Leaving SLNextItem\n");
		return temp;
	}
    return NULL;
}





