//
//  main.c
//  Perg3a
//
//  Created by Abhishek Saha on 3/11/14.
//  Copyright (c) 2014 Abhishek Saha. All rights reserved.
//
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "process.h"
#include "uthash.h"
#include "sl.h"
#include "sorted-list.h"


HashBucket *tokens = NULL;
SortedListPtr toks = NULL;

int compareInts(void *p1, void *p2)
{
	int i1 = *(int*)p2;
	int i2 = *(int*)p1;
    
	return i1 - i2;
}

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;
	return strcmp(s1, s2);
}


void process(char *myToken, char *myFilePath) //Change the parameters to (char * str1, char * str2)
{
    toks = SLCreate(compareStrings);
    //^^^^^^^^Needs to be called in the main argument
    
    
    NNodePtr him = (NNodePtr)malloc(sizeof(NNode));
//    him->key = str1 ; him->filename = str2; // THIS IS THE ORIGINAL LINE
	him->key = myToken; him->filename = myFilePath;
 
    insert(him);
    Insert(toks, him->key, him->key);
    /*
    NNodePtr jim = (NNodePtr)malloc(sizeof(NNode));
    
     jim->key = "is"; jim->filename = "File2";
     insert(jim);
     Insert(toks, jim->key, jim->key);
    
     NNodePtr zim = (NNodePtr)malloc(sizeof(NNode));
     zim->key = "file"; zim->filename = "File2";
     insert(zim);
    Insert(toks, zim->key, zim->key);
    
   NNodePtr grim = (NNodePtr)malloc(sizeof(NNode));
    grim->key = "four"; grim->filename = "File2";
    insert(grim);
    Insert(toks, grim->key, grim->key);*/
    
//    printAll(); //Has to be called in your main method
  
    //return 1;

}

void insert(NNodePtr item){
    HashBucket * current_token;
    char * KEY = item->key;
    HASH_FIND_STR(tokens, KEY , current_token);
    
    
    if(current_token==NULL){
        current_token = (HashBucket*)malloc(sizeof(HashBucket));
        current_token->name = item->key;
        
        
        CompareFuncT c = compareInts;
        SortedListPtr temp = SLCreate(c);
        int * one = malloc(sizeof(int));
        *one  = 1;
        
        int success;
        success = SLInsert(temp, (void*)one, item->filename);
        current_token->list = temp;
        HASH_ADD_STR(tokens, name, current_token);
        printf("%s Success!\n", temp->head->name);
//        free(item);
    }
    else{
        SortedListPtr temp = current_token->list;
        int success = 0;
        int * one = malloc(sizeof(int));
        *one  = 1;
        
        void*zone = (void*)one;
        success = SLInsert(temp, zone, item->filename);
        current_token->list = temp;
        HASH_DEL(tokens, current_token);
        HASH_ADD_STR(tokens, name, current_token);
        //free(item);
    }
    
    return;
}


int printAll(){
    
    NodePtr temp = toks->head;
    
    while(temp!=NULL){
        
        HashBucket * current_token;
        char * KEY = temp->name;
        HASH_FIND_STR(tokens, KEY , current_token);
        
        
        if(current_token==NULL){
            break;
        }
        
        
        else{
            SortedListPtr buff = current_token->list;
            NodePtr ptr = buff->head;
            NodePtr prev;
            printf("<List> (%s)\n",KEY);
            
            while(ptr!=NULL){
                
                char * filename = ptr->name;
                int jer = *(int*)ptr->data;
                printf("(%s ,%d)", filename, jer);
                prev = ptr;
                ptr = ptr->next;
                
                if(ptr!=NULL){
                    printf("-> ");}
                
                free(prev);
            }
            printf("\n");
            free(current_token->list);
            temp = temp->next;
            continue;}
        
    }
    free(toks);
    free(tokens);
    
    return 1;
}
