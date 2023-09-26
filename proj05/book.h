/* DO NOT MODIFY FILE */

#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNUSED(x) ((void)x)
#define BUCKET_CAPACITY 23
#define PHONE_NUMBER_LEN 10
#define SUCCESS 1
#define FAILURE 0

typedef struct Node {
  char *name;
  char *address;
  long phone_number;
  struct Node *next;
} Node;

typedef struct AddressBook {
  int size;
  Node **buckets;
} AddressBook;

char *dynamic_string_copy(const char *str);
AddressBook *create_book(void);
Node* create_node(const char *name, const char* address, long phone_number);
Node* get(AddressBook *book, const char *name);
char* update_node(AddressBook *book, const char *name, const char* address, long phone_number);
int put(AddressBook *book, const char *name, const char *address, long phone_number);
char* remove_node(AddressBook *book, const char *name);
void destroy_bucket(AddressBook *book, int bucket);
void destroy_book(AddressBook *book);
int hash(const char *name);

#endif
