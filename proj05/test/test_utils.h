#include "../book.h"

extern int mallocs_until_fail; 
extern int allow_realloc;

/* allow allow setters */
void allow_malloc(void);
void force_malloc_fail(void);
void force_realloc_fail_but_allow_malloc(void);
void force_realloc_and_malloc_fail(void);

/* solution implementations of functions, so that we can test in isolation */
extern char *_dynamic_string_copy(const char *str);

extern Node* _create_node(const char *name, const char* address, int phone_number);

extern int _num_digits(int num);

extern AddressBook *_create_book(void);

extern int _put(AddressBook *book, const char *name, const char *address, int phone_number);

extern Node *_get(AddressBook *book, const char *name);

extern void _destroy_book(AddressBook *book);

extern void _destroy_bucket(AddressBook *book, int bucket);

extern void _destroy_bucket_helper(Node *node);