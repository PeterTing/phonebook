#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16
#define RANGE 400001

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
#define HASH 1
typedef struct __PHONE_BOOK_EXTRA_DATA {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} extra;

typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    struct __PHONE_BOOK_ENTRY *pNext;
    struct __PHONE_BOOK_EXTRA_DATA *pExtra;
} entry;

typedef struct __HASH_TABLE {
    entry *e[RANGE];
} HashTable;

entry *findName(char lastName[], HashTable *table);
entry* HashTableGet(HashTable *table, int hashCode, char lastName[]);
void append(char lastName[], HashTable *table);
int bkdr_hash(char lastName[]);
void HashTablePut(HashTable *table, int hashCode, char lastName[]);
void HashTableFree(HashTable *table);
#endif

