//
//  process.h
//  Perg3a
//
//  Created by Abhishek Saha on 3/11/14.
//  Copyright (c) 2014 Abhishek Saha. All rights reserved.
//

#ifndef Perg3a_process_h
#define Perg3a_process_h

#include "uthash.h"
#include "sorted-list.h"


struct NNode{
    
    char * key;
    char * filename;
    
    
};

typedef struct NNode NNode;
typedef struct NNode* NNodePtr;



int compareStrings(void *p1, void *p2);

struct HashBucket {
    /* key */
    char * name;
    
    UT_hash_handle hh;         /* makes this structure hashable */
    SortedListPtr list;
};

typedef struct HashBucket HashBucket;
int compareInts(void *p1, void *p2);
void insert(NNodePtr item);
void process(char * str1, char * str2);
int printAll();

extern HashBucket * tokens;
extern SortedListPtr toks;

#endif
