#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "phonebook_opt_hash.h"

entry *findName(char lastName[], HashTable *table)
{
    int hashCode, isSame;
    hashCode = bkdr_hash(lastName);//*
    isSame = strcmp(lastName, HashTableGet(table, hashCode, lastName)->lastName);

    if(!isSame)
        return HashTableGet(table, hashCode, lastName);
    else {
        printf("cannot find the lastName, error1");
        return 0;
    }

}
/*
 * Transform the lastName into hash code and put them into hash table
 *
*/
void append(char lastName[], HashTable *table)
{
    int hashCode;
    hashCode = bkdr_hash(lastName);
    HashTablePut(table, hashCode, lastName);

}

int bkdr_hash(char lastName[])
{
    char* str = lastName;//*
    int seed = 3; // 31 131 1313 13131 131313 etc.. 37
    int hashCode = 0;
    while (*str) {
        hashCode = hashCode * seed + (*str++);
    }

    hashCode %= RANGE;

    return hashCode;
}

void HashTablePut(HashTable *table, int hashCode, char lastName[])
{
    //if the column doesn't have anything, put lastName into the entry
    if(table->e[hashCode] == NULL) {
        table->e[hashCode] = (entry *) malloc(sizeof(entry));
        table->e[hashCode]->pNext = NULL;
        strcpy(table->e[hashCode]->lastName, lastName);
    }
    //if the column already has value. put lastName into the tail of the entry.
    else {
        entry *head;
        head = table->e[hashCode];
        while(table->e[hashCode]->pNext != NULL)
            table->e[hashCode] = table->e[hashCode]->pNext;

        table->e[hashCode]->pNext = (entry *) malloc(sizeof(entry));
        table->e[hashCode] = table->e[hashCode]->pNext;
        strcpy(table->e[hashCode]->lastName, lastName);
        table->e[hashCode]->pNext = NULL;
        table->e[hashCode] = head;
    }
}


entry* HashTableGet(HashTable *table, int hashCode, char lastName[])
{
    int isSame;

    isSame = strcmp(lastName, table->e[hashCode]->lastName);

    if(isSame == 0) {
        return table->e[hashCode];
    } else {
        while(isSame !=0 && table->e[hashCode]->pNext != NULL) {
            table->e[hashCode] = table->e[hashCode]->pNext;
            isSame = strcmp(lastName, table->e[hashCode]->lastName);
        }

        if(isSame != 0) {
            printf("cannot find the lastName, error\n");
            exit(0);
        } else
            return table->e[hashCode];
    }
}

void HashTableFree(HashTable *table)
{
    for(int i = 0; i < RANGE; i++) {
        entry *tmp;

        while(table->e[i] != NULL) {
            tmp = table->e[i];
            table->e[i] = table->e[i]->pNext;
            free(tmp);
        }

    }
}
