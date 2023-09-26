#include "../book.h"
#include "test_utils.h"
#include "test.h"

/* test helpers */
char * default_name = "clementine";
char * default_address = "1600 Pennsylvania Avenue";
const long default_phone_number = 1234567890;

AddressBook* create_simple_address_book_no_hash(void){
    // each bucket is filled with default info
    // has external chains of lengh one
    AddressBook * b = _create_book();
    for (int i = 0; i < BUCKET_CAPACITY; i++){
        b->buckets[i] = _create_node(default_name, default_address, default_phone_number);
    }
    return b;
}

void free_simple_address_book_no_hash(AddressBook* b){
    for (int i = 0; i < BUCKET_CAPACITY; i++){
        free(b->buckets[i]->name);
        free(b->buckets[i]->address);
        free(b->buckets[i]);
    }

    // free the allocation of buckets
    free(b->buckets);
    // free the allocation of the AddressBook
    free(b);
}

AddressBook* create_simple_address_book_with_hash(void){
    AddressBook * b = _create_book();
    _put(b, default_name, default_address,default_phone_number);
    return b;
}

AddressBook* create_address_book_with_hash(void){
    AddressBook * b = _create_book();
    _put(b, default_name,default_address,default_phone_number);
    _put(b, "guava",default_address,default_phone_number);
    _put(b, "boconut",default_address,default_phone_number);
    _put(b, "sameer",default_address,default_phone_number);
    return b;
}

/* internal testing to ensure hashing has not been modified in student code */
START_TEST(internal_test_hashing)
{
    // internal test, awards 0 points for passing
    int a = hash("apple");      // 1
    int a2 = hash("Apple");     // 15
    int b = hash("orange");     // 15 (collision with Apple)
    int c = hash("guava");      // 3
    int d = hash("bannana");    // 6
    int e = hash("coconut");    // 4
    int f = hash("pear");       // 10
    int g = hash("watermelon"); // 5
    int h = hash("clementine"); // 2
   
    ck_assert_msg(a==1, "your hashing function may have been modified (!!) please restore its original code");
    ck_assert_int_eq(a2, 15);
    ck_assert_int_eq(b, 15);
    ck_assert_int_eq(c, 3);
    ck_assert_int_eq(d, 6);
    ck_assert_int_eq(e, 4);
    ck_assert_int_eq(f, 10);
    ck_assert_int_eq(g, 5);
    ck_assert_int_eq(h,2);
}
END_TEST

/* dynamimc_str_cpy() tests */

START_TEST(test_dynamic_str_cpy_malloc_failure)
{
    // Malloc till failure test
    char *str = "This should not be copied...";

    char *copy = dynamic_string_copy(str);
    ck_assert_ptr_ne(str, copy); // Checking that they didn't just return the src ptr
    ck_assert_msg(!copy, "Improperly handles malloc failure");
}
END_TEST

START_TEST(test_dynamic_str_cpy_tiny_string)
{
    // "" - string with just null terminator
    char null_term[] = {'\0'};
    char *ret = dynamic_string_copy(null_term);

    ck_assert_ptr_ne(null_term, ret);                        // Checking that they didn't just return the src ptr
    ck_assert_ptr_ne(NULL, ret);                              // Checking that it;s not NULL
    ck_assert_msg(ret[0] == '\0', "Forgot NULL Terminator"); // Check for NULL terminator

    free(ret); // Free Their String

    char src[] = {'H', 'i', '\0'};
    char *retVal = dynamic_string_copy(src);

    char *actual = _dynamic_string_copy(src);

    ck_assert_ptr_ne(src, retVal);                                               // Checking that they didn't just return the src ptr
    ck_assert_ptr_ne(NULL, retVal);                              // Checking that it;s not NULL
    ck_assert_msg(retVal[2] == '\0', "Forgot NULL Terminator");                  // Check for NULL terminator
    ck_assert_msg(!strcmp(retVal, src), "Expected \"%s\", Actual: \"%s\"", src, retVal); // Checking if strcmp returns 0

    // Free Their String
    free(retVal);
    free(actual);
}
END_TEST

START_TEST(test_dynamic_str_cpy_simple_string)
{

    // NULL case
    const char *str_to_cpy = NULL;
    char *copy1 = dynamic_string_copy(str_to_cpy);
    ck_assert_msg(!copy1, "Expected: NULL ptr");

    // Simple case
    const char *str = "cRaZZy_sSTrINg_to_oo_oo_copppppp_Y";
    char *copy = dynamic_string_copy(str);

    // Tests
    ck_assert_ptr_ne(str, copy); // Checking that they didn't just return the src ptr
    ck_assert_ptr_ne(NULL, copy);                              // Checking that it;s not NULL
    ck_assert_msg(strcmp(copy, str) == 0, "Expected: \"%s\", Actual: \"%s\"", str, copy);

    free(copy);
}
END_TEST

START_TEST(test_dynamic_str_cpy_big_string)
{

    const char *str = "LONG_STRING!!!! - aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";

    // BIGGGG String
    char *copy = dynamic_string_copy(str);
    ck_assert_ptr_ne(str, copy); // Checking that they didn't just return the src ptr
    ck_assert_ptr_ne(NULL, copy);                              // Checking that it;s not NULL
    ck_assert_msg(strcmp(copy, str) == 0, "Expected: \"%s\", Actual: \"%s\"", str, copy);
    free(copy);
}
END_TEST

/* end of dynamimc_str_cpy() tests */

/* create_book() tests */
START_TEST(test_create_book_malloc_failure) {
    // create a book using student's implementation
    AddressBook *b = create_book();
    ck_assert_msg(!b, "create_book should return NULL if malloc fails");
}
END_TEST

START_TEST(test_create_book_basic) {
    // create a book using student's implementation
    AddressBook *b = create_book();

    // just verify basic tests
    ck_assert_msg(b, "create_book should not return NULL");
    ck_assert_msg(!b->size, "create_book should initialize with size 0");
    ck_assert_msg(b->buckets, "create_book should return a book with buckets having a valid pointer");
    
    // free the allocation of buckets
    free(b->buckets);
    // free the allocation of the AddressBook
    free(b);
}
END_TEST

START_TEST(test_create_book_bucket_size) {
    // create a book using student's implementation
    AddressBook *b = create_book();

    // verify basic tests
    ck_assert_msg(b, "create_book should not return NULL");
    ck_assert_msg(!b->size, "create_book should initialize with size 0");
    ck_assert_msg(b->buckets, "create_book should return a book with buckets having a valid pointer");
    /*
        note: the size of an allocation cannot be tested directly
        see: https://stackoverflow.com/questions/24509509/how-to-get-the-size-of-memory-pointed-by-a-pointer
        instead, fill every bucket, and let valgrind (!!) determine if
        student has allocated sufficient space in buckets for BUCKET_CAPACITY elements.
    
        if you are passing the above assertions, but getting invalid writes/reads
        from valgrind then your buckets have not been allocated sufficient space
    */
    for (int i = 0; i < BUCKET_CAPACITY; i++){
        b->buckets[i] = _create_node(default_name, default_address, default_phone_number);
    }

    // free the nodes that have been created
    for (int i = 0; i < BUCKET_CAPACITY; i++){
        free(b->buckets[i]->name);
        free(b->buckets[i]->address);
        free(b->buckets[i]);
    }
    
    // free the allocation of buckets
    free(b->buckets);
    // free the allocation of the AddressBook
    free(b);
}
END_TEST

START_TEST(test_create_book_bucket_initialization) {
    // create a book using student's implementation
    AddressBook *b = create_book();

    ck_assert_msg(b, "create_book failed to get a pointer");
    ck_assert_msg(b->buckets, "create_book failed to make buckets");
    ck_assert_msg(b->size == 0, "create_book failed init size to 0");

    // ensure the buckets all have null pointers
    // implementing future funcs is very hard if there are garbage pointers in the buckets
    Node* n;
    for(int i = 0; i < BUCKET_CAPACITY; ++i){
        n = b->buckets[i];
        ck_assert_msg(n == NULL, "create book should init each pointer in buckets to null (!!)");
    }
    
    // free the allocation of buckets
    free(b->buckets);
    // free the allocation of the AddressBook
    free(b);
}
END_TEST
/* end of create_book() tests */

/* create_node() tests */
START_TEST(test_create_node_malloc_failure) {
    // create a node using student's implementation
    Node *n = create_node(default_name, default_address, default_phone_number);
    ck_assert_msg(!n, "create_node should return NULL if malloc fails");
}
END_TEST

START_TEST(test_create_node_invalid_name) {
    // create a node using student's implementation
    Node *n = create_node(NULL, default_address, default_phone_number);
    ck_assert_msg(!n, "create_node should return NULL if provided an invalid name");
}
END_TEST

START_TEST(test_create_node_invalid_address) {
    // create a node using student's implementation
    Node *n = create_node(default_name, NULL, default_phone_number);
    ck_assert_msg(!n, "create_node should return NULL if provided an invalid address");
}
END_TEST

START_TEST(test_create_node_invalid_phone_number) {
    // create a node using student's implementation
    long invalid_phone_number_1 = 404;
    long invalid_phone_number_2 = -404;
    long invalid_phone_number_3 = 999999999;
    long invalid_phone_number_4 = -539222978;
    long invalid_phone_number_5 = 01111111111;
    Node* n;
    n = create_node(default_name, default_address, invalid_phone_number_1);
    ck_assert_msg(!n, "create_node should return NULL if provided an invalid phone number: %d", invalid_phone_number_1);

    n = create_node(default_name, default_address, invalid_phone_number_2);
    ck_assert_msg(!n, "create_node should return NULL if provided an invalid phone number %d", invalid_phone_number_2);

    n = create_node(default_name, default_address, invalid_phone_number_3);
    ck_assert_msg(!n, "create_node should return NULL if provided an invalid phone number %d", invalid_phone_number_3);

    n = create_node(default_name, default_address, invalid_phone_number_4);
    ck_assert_msg(!n, "create_node should return NULL if provided an invalid phone number %d", invalid_phone_number_4);

    n = create_node(default_name, default_address, invalid_phone_number_5);
    ck_assert_msg(!n, "create_node should return NULL if provided an invalid phone number %d", invalid_phone_number_5);
}
END_TEST

START_TEST(test_create_node_basic) {
    // create a book using student's implementation
    Node *n = create_node(default_name, default_address, default_phone_number);
    ck_assert_msg(n, "create_node should not return NULL");
    ck_assert_msg(strcmp(n->name, default_name) == 0, "create_node should correctly assign the name");
    ck_assert_msg(strcmp(n->address, default_address) == 0, "create_node should correctly assign the address");
    ck_assert_msg(_num_digits(n->phone_number) == PHONE_NUMBER_LEN, "create_node should correctly assign phone number");
    ck_assert_msg(!n->next, "create_node should correctly set next to null");

    // free allocations, so test case does not memory leak
    free(n->name);
    free(n->address);
    free(n);
}
END_TEST
/* end of create_node() tests */

/* get() tests */
START_TEST(test_get_invalid_book) {
    Node* n = get(NULL, "ribbit");
    ck_assert_msg(!n, "get should return NULL if address book is null");
}
END_TEST

START_TEST(test_get_invalid_name) {
    AddressBook* b = create_simple_address_book_no_hash();
    Node* n = get(b, NULL);
    ck_assert_msg(!n, "get should return NULL if queried name is null");
    free_simple_address_book_no_hash(b);
}
END_TEST

START_TEST(test_get_nonexistant_name) {
    AddressBook* b = create_simple_address_book_with_hash();
    Node* n = get(b, "watermelon");
    ck_assert_msg(!n, "get should return NULL if name does not exist in book");
    _destroy_book(b);
}
END_TEST

START_TEST(test_get_existing_name) {
    AddressBook* b = create_address_book_with_hash();
    char * query_name = "guava";
    Node* n = get(b, query_name);
    
    ck_assert_msg(n, "get should return node if name exists in book");
    
    // verify the same pointer is returned (notice: there was a collision, so it was externally chained)
    ck_assert_ptr_eq(n, b->buckets[hash(query_name)]->next);
    _destroy_book(b);
}
END_TEST
/* end of get() tests */

/* put() tests */
START_TEST(test_put_malloc_failure) {
    AddressBook* b = create_simple_address_book_no_hash();
    int err_code = put(b, default_name, default_address, default_phone_number);
    ck_assert_msg(err_code == FAILURE, "put should return FAILURE if malloc fails");
    free_simple_address_book_no_hash(b);
}
END_TEST

START_TEST(test_put_invalid_book) {
    int err_code = put(NULL, default_name, default_address, default_phone_number);
    ck_assert_msg(err_code == FAILURE, "put should return FAILURE if address book is null");
}
END_TEST

START_TEST(test_put_duplicate) {
    AddressBook* b = create_address_book_with_hash();
    int err_code = put(b, default_name, default_address, default_phone_number);
    ck_assert_msg(b->size == 4, "exp book size %d, act book size: %d", 4, b->size);
    ck_assert_msg(err_code == FAILURE, "put should return FAILURE if name already exists in book");
    _destroy_book(b);
}
END_TEST

START_TEST(test_put_basic) {
    int put_status = -1;
    
    AddressBook* b = _create_book();
    ck_assert_msg(b, "create_book failed to get a pointer");
    ck_assert_msg(b->buckets, "create_book failed to make buckets");
    ck_assert_msg(b->size == 0, "create_book failed init size to 0");

    // once again, make sure that the buckets are initialized to null
    // for brevity only check the first bucket, however if this test is failing here
    // fix the test_create_book_bucket_initialization test case!
    Node *n = b->buckets[0];
    ck_assert_ptr_eq(n, NULL);

    // should not exist yet
    Node* apple_node = _get(b, "apple");
    ck_assert_msg(!apple_node, "book should not have an apple node yet");

    put_status = put(b, "apple", default_address, default_phone_number);
    ck_assert_msg(put_status == SUCCESS, "put did not return a SUCCESS status code");

    // apple should exist
    apple_node = _get(b, "apple");
    ck_assert_msg(apple_node, "book should have an apple node now");

    // check next is null 
    ck_assert_msg(!apple_node->next, "next node should be null");

    ck_assert_msg(b->size == 1, "Exp book size: %d Act book size: %d", 1, b->size);

    // free all the allocations we have made so far !!
    _destroy_book(b);
}
END_TEST

START_TEST(test_put_external_chain_buckets) {
    // test the external chaining ability of hash table
    int put_status = -1;
    
    AddressBook* b = _create_book();
    ck_assert_msg(b, "create_book failed to get a pointer");
    ck_assert_msg(b->buckets, "create_book failed to make buckets");
    ck_assert_msg(b->size == 0, "create_book failed init size to 0");

    // once again, make sure that the buckets are initialized to null
    // for brevity only check the first bucket, however if this test is failing here
    // fix the test_create_book_bucket_initialization test case!
    Node *n = b->buckets[0];
    ck_assert_ptr_eq(n, NULL);

    // Apple should not exist yet
    Node* apple_node = _get(b, "Apple");
    ck_assert_msg(!apple_node, "book should not have an Apple node yet");

    // put Apple
    put_status = put(b, "Apple", default_address, default_phone_number);
    ck_assert_msg(put_status == SUCCESS, "put did not return a SUCCESS status code for Apple");

    // orange should not exist yet
    Node* orange_node = _get(b, "orange");
    ck_assert_msg(!orange_node, "book should not have an orange node yet");

    // put orange
    put_status = put(b, "orange", default_address, default_phone_number);
    ck_assert_msg(put_status == SUCCESS, "put did not return a SUCCESS status code for orange");

    // orange should exist
    apple_node = _get(b, "orange");
    ck_assert_msg(apple_node, "book should have an orange node now");

    // Apple should exist
    apple_node = _get(b, "Apple");
    ck_assert_msg(apple_node, "book should still be able to get Apple now. Otherwise, put may not be setting next ptr correctly");

    // manually verify they were sent to the correct bucket
    Node *A = b->buckets[hash("Apple")];
    Node *o = b->buckets[hash("orange")];

    // since they have hasing collision, they should index into the same bucket
    ck_assert_msg(A==o, "Hasing collision did not result in the same bucket");

    ck_assert_msg(b->size == 2, "Exp book size: %d Act book size: %d", 2, b->size);

    // free all the allocations we have made so far !!
    _destroy_book(b);
}
END_TEST

START_TEST(test_put_external_chain_add_to_front) {
    // test the external chaining order of hash table
    
    AddressBook* b = _create_book();

    char* name1 = "Apple";
    char* name2 = "Jason J";
    char* name3 = "orange";
    char* name4 = "Ruby G";

    put(b, name1, default_address, default_phone_number);
    put(b, name2, default_address, default_phone_number);
    put(b, name3, default_address, default_phone_number);
    put(b, name4, default_address, default_phone_number);

    Node *A = b->buckets[hash(name1)];
    Node *r = b->buckets[hash(name4)];
    ck_assert_msg(A==r, "Hasing collision did not result in the same bucket");

    int collision_index = hash(name3);
    Node* collision_bucket = b->buckets[collision_index];

    // each put collision should add to front, so name4 should appear first
    ck_assert_msg(strcmp(collision_bucket->name, name4) == 0, "External chaining order incorrect. Exp name: %s Got Name: %s", name4, collision_bucket->name);

    // each put collision should add to front, so name4 should appear first
    ck_assert_msg(strcmp(collision_bucket->name, name4) == 0, "External chaining order incorrect. Exp name: %s Got Name: %s", name4, collision_bucket->name);

    // check another element in external chain
    ck_assert_msg(strcmp(collision_bucket->next->next->name, name2) == 0, "External chaining order incorrect. Exp name: %s Got Name: %s", name2, collision_bucket->name);

    ck_assert_msg(b->size == 4, "Exp book size: %d Act book size: %d", 4, b->size);

    // free all the allocations we have made so far !!
    _destroy_book(b);
}
END_TEST
/* end of put() tests */

/* update_node() tests */
START_TEST(test_update_node_invalid_book) {
    char *old_name = update_node(NULL, default_name, default_address, default_phone_number);
    ck_assert_msg(!old_name, "update should return NULL if address book is null");
}
END_TEST

START_TEST(test_update_node_invalid_name) {
    AddressBook* b = _create_book();
    char *old_name = update_node(b, NULL, default_address, default_phone_number);
    ck_assert_msg(!old_name, "update should return NULL if name is null");
    _destroy_book(b);
}
END_TEST

START_TEST(test_update_node_invalid_address) {
    AddressBook* b = _create_book();
    char *old_name = update_node(b, default_name, NULL, default_phone_number);
    ck_assert_msg(!old_name, "update should return NULL if address is null");
    _destroy_book(b);
}
END_TEST

START_TEST(test_update_node_invalid_phone_number) {
    AddressBook* b = _create_book();
    char *old_name = update_node(b, default_name, default_address, 123);
    ck_assert_msg(!old_name, "update should return NULL if phone number is invalid");
    _destroy_book(b);
}
END_TEST

START_TEST(test_update_node_nonexistant_name) {
    AddressBook* b = create_address_book_with_hash();
    char *old_name = update_node(b, "notseenthisnamebefore", default_address, default_phone_number);
    ck_assert_msg(!old_name, "udpate should return NULL if queried name does not exist in book");
    _destroy_book(b);
}
END_TEST

START_TEST(test_update_node_new_allocation_fails) {
    AddressBook* b = create_address_book_with_hash();
    char *old_name = update_node(b, default_name, default_address, default_phone_number);
    ck_assert_msg(!old_name, "udpate should return NULL if allocating memory fails");
    _destroy_book(b);
}
END_TEST

/* test case segfaulting */
START_TEST(test_update_node) {
    AddressBook* b = create_address_book_with_hash();
    long new_phone_number = 4041239030;
    char * new_address = "42 Wallaby Way";

    // get the default values and verify they are what we expect
    Node *n = _get(b, default_name);
    ck_assert_int_eq(n->phone_number, default_phone_number);
    ck_assert_msg(strcmp(n->name, default_name)==0, "not the same name");
    
    // use the student implementation to update the address book with new values
    char *s = update_node(b, default_name, new_address, new_phone_number);

    // check if the return value, name, is the same
    ck_assert_ptr_eq(s, n->name);

    // create a sentry node to check our modifications in the table
    Node *check_node = b->buckets[hash(default_name)];
    // first verify that our original pointer that Node in memory was updated
    ck_assert_msg(strcmp(n->address, new_address) == 0, "update should modify the address to the new value. Exp: %s, Got %s", new_address, n->address);
    ck_assert_msg(n->phone_number == new_phone_number, "Exp phone number: %d Got phone number: %d", new_phone_number, n->phone_number);
    
    // now crosscheck by indexing into the address book using a hash
    ck_assert_msg(strcmp(check_node->address, n->address) == 0, "update should modify the address to the new value. Exp: %s, Got %s", new_address, n->address);

    // ensure the next pointer is unchanged
    ck_assert_ptr_eq(n->next, NULL);
    _destroy_book(b);
}
END_TEST
/* end of update_node() tests */

/* remove_node() tests */
START_TEST(test_remove_node_invalid_book) {
    char *old_name = remove_node(NULL, default_name);
    ck_assert_msg(!old_name, "remove should return NULL if address book is null");
}
END_TEST

START_TEST(test_remove_node_invalid_name) {
    AddressBook* b = _create_book();
    char *old_name = remove_node(b, NULL);
    ck_assert_msg(!old_name, "remove should return NULL if name is null");
    _destroy_book(b);
}
END_TEST

START_TEST(test_remove_node_nonexistant_name) {
    AddressBook* b = create_address_book_with_hash();
    char *old_name = remove_node(b, "notseenthisnamebefore");
    ck_assert_msg(!old_name, "remove should return NULL if queried name does not exist in book");
    _destroy_book(b);
}
END_TEST

START_TEST(test_remove_node_simple) {
    AddressBook* b = create_address_book_with_hash();
    char *old_name = remove_node(b, default_name);
    ck_assert_msg(strcmp(old_name, default_name) == 0, "remove should return name of entry in book");
    ck_assert_msg(b->size == 3, "Exp book size: %d Act book size: %d", 3, b->size);
    free(old_name);
    _destroy_book(b);
}
END_TEST

START_TEST(test_remove_node_advanced) {
    AddressBook* b = create_address_book_with_hash();
    // add a third collision to the 3rd bucket
    char* new_person = "Adam";
    _put(b, new_person, default_address, default_phone_number);

    char * name_to_rm = "boconut";
    char *old_name = remove_node(b, name_to_rm);
    ck_assert_msg(strcmp(old_name, name_to_rm) == 0, "remove should return name of queried entry in book");
    Node* first = _get(b, new_person);
    Node* second = _get(b, "guava");
    // make sure we maintain linkage between existing nodes which were externally chained
    ck_assert_ptr_eq(first->next, second);
    ck_assert_msg(b->size == 4, "Exp book size: %d Act book size: %d", 4, b->size);
    free(old_name);
    _destroy_book(b);
}
END_TEST
/* end of remove_node() tests */

/* destroy_book() tests */
START_TEST(test_destroy_book_invalid_book) {
    destroy_book(NULL);
    ck_assert_msg(1, "Yay, do nothing !!");
}
END_TEST

START_TEST(test_destroy_book_complete) {
    AddressBook* b = create_address_book_with_hash();
    destroy_book(b);
    // valgrind hint: if you are strugging with this test case,
    // you should consider freeing all the memory the book has
    // allocated from the "inside out". If you dont follow
    // a logical order, then you will leave behind memory leaks
    // or attempt a free-after-free error.
    ck_assert_msg(1, "Yay, check nothing !!");
}
END_TEST
/* end of destroy_book() tests */

/* destroy_bucket() tests */
START_TEST(test_destroy_bucket_invalid_book) {
    destroy_bucket(NULL, 8);
    ck_assert_msg(1, "Yay, do nothing !!");
}
END_TEST

START_TEST(test_destroy_bucket_out_of_bounds) {
    AddressBook* b = create_simple_address_book_with_hash();
    destroy_bucket(b, BUCKET_CAPACITY);
    ck_assert_msg(strcmp(b->buckets[hash(default_name)]->address, default_address) == 0, "For an index out of bounds, do not destroy the address data of the nodes in a bucket");
    ck_assert_msg(strcmp(b->buckets[hash(default_name)]->name, default_name) == 0, "For an index out of bounds, do not destroy the name data of the nodes in a bucket");
    ck_assert_msg(b->buckets[hash(default_name)]->phone_number == default_phone_number, "For an index out of bounds, do not destroy the phone_number data of the nodes in a bucket");
    _destroy_book(b);
}
END_TEST

START_TEST(test_destroy_bucket_complete) {
    AddressBook* b = create_address_book_with_hash();
    destroy_bucket(b, 3);
    ck_assert_msg(b->buckets[3] == NULL, "Set bucket to null after destroying it");
    _destroy_book(b);
    // valgrind hint: if you are strugging with this test case,
    // you should consider freeing all the memory that the bucket has.
    // Be sure to follow a logical order so you do not get a free-after-free error.
}
END_TEST

START_TEST(test_destroy_bucket_then_add) {
    AddressBook* b = create_address_book_with_hash();
    destroy_bucket(b, 3);
    ck_assert_msg(b->buckets[3] == NULL, "Set bucket to null after destroying it");
    
    char * another_name = "gauva";
    char* another_address = "42 Wallaby Way";
    long another_phone_number = 1234567890;
    // after your implementation of destroy bucket, the working implmentation of put should still function as normal
    // for the same bucket we just destroyed.
    int err_code =_put(b, another_name, another_address, another_phone_number);
    ck_assert_msg(err_code == SUCCESS, "put should succeed with no problems after you destroy a bucket");
    ck_assert_msg(strcmp(b->buckets[hash(another_name)]->name, another_name) == 0, "Put should place a new name in the bucket");
    ck_assert_msg(strcmp(b->buckets[hash(another_name)]->address, another_address) == 0, "Put should place a new address in the bucket");
    ck_assert_msg(b->buckets[hash(another_name)]->phone_number == another_phone_number, "Put should place a new phone_number in the bucket");

    _destroy_book(b);
}
END_TEST
/* end of destroy_book() tests */

/* create test suite */
Suite *book_suite(void)
{
    Suite *s = suite_create("Book");

    /* dynamimc_str_cpy() tests */
    tcase_add(s, force_malloc_fail, NULL, test_dynamic_str_cpy_malloc_failure);
    tcase_add(s, allow_malloc, NULL, test_dynamic_str_cpy_tiny_string);
    tcase_add(s, allow_malloc, NULL, test_dynamic_str_cpy_simple_string);
    tcase_add(s, allow_malloc, NULL, test_dynamic_str_cpy_big_string);
    
    /* create_book() tests */
    tcase_add(s, force_malloc_fail, NULL, test_create_book_malloc_failure);
    tcase_add(s, allow_malloc, NULL, test_create_book_basic);
    tcase_add(s, allow_malloc, NULL, test_create_book_bucket_size);
    tcase_add(s, allow_malloc, NULL, test_create_book_bucket_initialization);

    /* create_node() tests */
    tcase_add(s, force_malloc_fail, NULL, test_create_node_malloc_failure);
    tcase_add(s, allow_malloc, NULL, test_create_node_invalid_name);
    tcase_add(s, allow_malloc, NULL, test_create_node_invalid_address);
    tcase_add(s, allow_malloc, NULL, test_create_node_invalid_phone_number);
    tcase_add(s, allow_malloc, NULL, test_create_node_basic);

    /* get() tests */
    tcase_add(s, allow_malloc, NULL, test_get_invalid_book);
    tcase_add(s, allow_malloc, NULL, test_get_invalid_name);
    tcase_add(s, allow_malloc, NULL, test_get_nonexistant_name);
    tcase_add(s, allow_malloc, NULL, test_get_existing_name);
    
    /* put() tests */
    tcase_add(s, force_malloc_fail, NULL, test_put_malloc_failure);
    tcase_add(s, allow_malloc, NULL, test_put_invalid_book);
    tcase_add(s, allow_malloc, NULL, test_put_basic);
    tcase_add(s, allow_malloc, NULL, test_put_external_chain_buckets);
    tcase_add(s, allow_malloc, NULL, test_put_external_chain_add_to_front);
    tcase_add(s, allow_malloc, NULL, test_put_duplicate);

    /* update() tests */
    tcase_add(s, allow_malloc, NULL, test_update_node_invalid_book);
    tcase_add(s, allow_malloc, NULL, test_update_node_invalid_name);
    tcase_add(s, allow_malloc, NULL, test_update_node_invalid_address);
    tcase_add(s, allow_malloc, NULL, test_update_node_invalid_phone_number);
    tcase_add(s, allow_malloc, NULL, test_update_node_nonexistant_name);
    tcase_add(s, force_realloc_and_malloc_fail, NULL, test_update_node_new_allocation_fails);
    tcase_add(s, allow_malloc, NULL, test_update_node);

    /* remove() tests */
    tcase_add(s, allow_malloc, NULL, test_remove_node_invalid_book);
    tcase_add(s, allow_malloc, NULL, test_remove_node_invalid_name);
    tcase_add(s, allow_malloc, NULL, test_remove_node_nonexistant_name);
    tcase_add(s, allow_malloc, NULL, test_remove_node_simple);
    tcase_add(s, allow_malloc, NULL, test_remove_node_advanced);

    /* destroy_book() tests */
    tcase_add(s, allow_malloc, NULL, test_destroy_book_invalid_book);
    tcase_add(s, allow_malloc, NULL, test_destroy_book_complete);

    /* destroy_bucket() tests */
    tcase_add(s, allow_malloc, NULL, test_destroy_bucket_invalid_book);
    tcase_add(s, allow_malloc, NULL, test_destroy_bucket_out_of_bounds);
    tcase_add(s, allow_malloc, NULL, test_destroy_bucket_complete);
    tcase_add(s, allow_malloc, NULL, test_destroy_bucket_then_add);

    /* hash() test */
    tcase_add(s, allow_malloc, NULL, internal_test_hashing);
    return s;
}
