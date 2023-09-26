#include "book.h"

/*
 * @brief Allocate a new string, copy  the passed-in string over to it, and
 * return the new string. This function might be helpful when implementing later functions.
 *
 * Should fail (return NULL) if the input string is NULL or malloc fails
 *
 * @param const char *str, the string to copy
 * @return char*, a pointer to a new string
 */
char *dynamic_string_copy(const char *str) {


  if(str == NULL){
      return NULL;
  }
  char *ptr;  // declares new variable for return 
  ptr = (char*) malloc(strlen(str) + 1); // allocates a block of memory with size = strlen(str) and assigns to ptr
  if(ptr == NULL){
    return NULL; //check if malloc fails
  }
  strcpy(ptr, str); // copies data from str to ptr
  return ptr; // return string ptr
}

/*
 * @brief Allocate a new AddressBook, and return a pointer to it. You should initialize
 * it to have a bucket array of size BUCKET_CAPACITY and a size of 0.
 *
 * Should fail (return NULL) if malloc fails
 *
 * @return AddressBook*, a pointer to the new address book. NULL if malloc fails
 */
AddressBook *create_book(void) { 

  AddressBook *var;
  var = (AddressBook*) calloc(sizeof(AddressBook), 1);
  if(var == NULL){
  return NULL;
  }
  var->buckets = (Node**) calloc(BUCKET_CAPACITY,sizeof(Node*));
  if (var->buckets == NULL){
  return NULL; }
  
  // var->size = (int) malloc(sizeof(BUCKET_CAPACITY));
  // if(var->size == NULL){
  //   return NULL;
  // }

  return var;
}

/*
 * @brief Allocate and initialize a new Node with a copy of the given data that's
 * passed in as arguments, and return a pointer to it. Don't forget to set the
 * next member for this new Node to NULL.
 *
 * Should fail (return NULL) if any input string is NULL or the number of digits of
 * phone_number does not match PHONE_NUMBER_LEN or malloc fails
 *
 * @param const char *name, copy this string and use it as the new Node's name
 * @param const char *address, copy this string and use it as the new Node's address
 * @param long phone_number, use it as the new Node's phone_number
 * @return Node*, a pointer to the new node. NULL if malloc fails
 */
Node *create_node(const char *name, const char *address, long phone_number) {
  int counter = 0;
  long phone = phone_number;
  for(int i = 0; i < PHONE_NUMBER_LEN + 1; i++){
    phone /= 10;
    counter++;
    if(phone == 0){
      break;
    }
  }
  // do{
  //   phone /= 10;
  //   ++counter;
  // } while(phone != 0);
  if (name == NULL || address == NULL || PHONE_NUMBER_LEN != counter){
    return NULL;
  }
  Node *var;
  var = (Node*) malloc(sizeof(Node));
  if (var == NULL){
    return NULL;
  }
  var->name = dynamic_string_copy(name);
  var->address = dynamic_string_copy(address);
  var->phone_number = phone_number;
  var->next =NULL;
  return var;

}

/*
 * @brief Create a new Node, put it into the AddressBook and increment the size of AddressBook. 
 *  
 * The bucket to put the node can be computed with hash(char *).
 * Add the node to the front of the bucket’s linked list.
 * If a node with the same name already exists, don’t make any changes to the table.
 *
 * Should fail if the given AddressBook is NULL, a node with the given name is found,
 * the given name or address is NULL, or phone_number does not have the right length. 
 * Should also fail if malloc fails at any point. Make sure to free things you have malloced along the way if you fail!
 *
 * @param AddressBook *book, the book to put the node
 * @param const char *name, the name of the node
 * @param const char *address, the address of the node
 * @param long phone_number, the phone_number of the node
 * @return int, returns SUCCESS if put is successful and FAILURE otherwise
 */
int put(AddressBook *book, const char *name, const char *address, long phone_number) {

  if(book == NULL){
    return FAILURE;
  }
  int temp = hash(name);
  Node *var = book->buckets[temp];

  int counter = 0;
  long phone = phone_number;
  for(int i = 0; i < PHONE_NUMBER_LEN + 1; i++){
    phone /= 10;
    counter++;
    if(phone == 0){
      break;
    }
  }
  if (PHONE_NUMBER_LEN != counter){
    return FAILURE;
  }
  while(var != NULL){
    if(strcmp(var->name,name) == 0){
      return FAILURE;
    }else{
      var = var->next;
    }
  }
  Node *node = create_node(name, address, phone_number);
  node->next = book->buckets[temp];
  book->buckets[temp] = node;
  book->size += 1;
  return SUCCESS;
}

/*
 * @brief Remove the Node with the given name. Assign the predecessor Node's next to be the successor 
 * of the removed Node, and return the removed node’s name. If the node being removed is the first node 
 * in the linked list of a bucket, you should update the bucket as well.
 * 
 * Watch out for memory leaks in your implementation! Make sure you free anything you malloced appropriately!
 *
 * Should fail if the given book is NULL, or a node with the given name is not found
 *
 * @param AddressBook *book, the book to look into
 * @param const char *name, the name of the node to be removed
 * @return char*, a pointer to the name of the removed node or NULL if failure
 */
char *remove_node(AddressBook *book, const char *name) {
  if(book == NULL || name == NULL){
    return NULL;
  }
  int temp = hash(name);
  Node *var = book->buckets[temp];
  Node *prev = NULL;
  char *storeName = NULL;

while(var != NULL){
    if(strcmp(var->name,name) == 0){
      if(var == book->buckets[temp]){
            book->buckets[temp] = var->next;
            storeName = dynamic_string_copy(var->name);
            free(var->address);
            free(var->name);
            free(var);
            book->size -= 1;
            return storeName;
      }
      prev->next = var->next;
      storeName = dynamic_string_copy(var->name);
      free(var->address);
      free(var->name);
      free(var);
      book->size -= 1;
      return storeName;

    }else{
      prev = var;
      var = var->next;
    }
  }
  return NULL;
}

/*
 * @brief Search for a node in the book with the given name and return a pointer to the node.
 * Return NULL if it does not exist.
 *
 * Should fail (return NULL) if the given book is NULL, the given name is NULL, or a node 
 * with the given name is not found. 
 *
 * @param AddressBook *book, the book to search in
 * @param char *name, the name to search for in the book
 * @return Node*, a pointer to the found node
 */
Node *get(AddressBook *book, const char *name) {
  if(book == NULL || name == NULL){
    return NULL;
  }
  int temp = hash(name);
  Node *var = book->buckets[temp];
  while(var != NULL){
    if(strcmp(var->name,name) == 0){
      return var;
    } else{
      var = var->next;
    }
  }
  return NULL;
}

/*
 * @brief Update the data of the Node with the given name. Return a pointer to the old name
 * 
 * Make sure you make copies of name and address when you update nodes!
 * 
 * Should fail (return NULL) if the given book is NULL，name or address is NULL, if the phone_number 
 * length isn't equal to PHONE_NUMBER_LEN or if a node with the given name is not found. Also fails 
 * if malloc fails.
 *
 * @param AddressBook *book, the book to look in
 * @param const char *name, the name to search for in the book
 * @param const char *address, the string to copy and update the node with
 * @param long phone_number, the int to copy and update the node with
 * @return char*, a pointer to the old name of the node. NULL if the method
 * fails
 */
char *update_node(AddressBook *book, const char *name, const char *address, long phone_number) {
  if(book == NULL || name == NULL || address == NULL){
    return NULL;
  }
  int counter = 0;
  long phone = phone_number;
  for(int i = 0; i < PHONE_NUMBER_LEN + 1; i++){
    phone /= 10;
    counter++;
    if(phone == 0){
      break;
    }
  }
  if (PHONE_NUMBER_LEN != counter){
    return NULL;
  }
  Node* var = book->buckets[hash(name)];
  while(var != NULL) {
    if (strcmp(name, var->name) == 0) {
      char *temp = var->address;
      var->address = dynamic_string_copy(address);
      free(temp);
      if (var->address == NULL) {
        return NULL;
      }
      var->phone_number = phone_number;
      return var->name;
    } else {
      var = var->next;
    }
  }
  return NULL;
}

/*
 * @brief Completely destroy the given bucket. Destroy all the nodes in the linked list
 * of the bucket. This means freeing any nodes linked to a specific bucket.
 * It will be in your best interest to reset the bucket's node pointer back to null.
 * If the index is out of bounds for BUCKET_CAPACITY, then simply return nothing.
 *
 * @param AddressBook *book, the book to look in
 * @param int bucket, the index of the bucket in the address book that will be destroyed
 */
void destroy_bucket(AddressBook *book, int bucket) {
  if(bucket < 0 || bucket >= BUCKET_CAPACITY || book == NULL){
    return;
  }
  Node *var = book->buckets[bucket];
  if(var == NULL){
    return;
  }
  Node *temp = NULL;
  while(var != NULL){
    temp = var;
    var = var->next;
    free(temp->name);
    free(temp->address);
    free(temp);

  }

  book->buckets[bucket] = NULL;

}

/*
 * @brief Completely destroy the given AddressBook. This means
 * freeing everything that the AddressBook references (all Nodes).
 * You can simply return nothing if the book is NULL.
 * 
 * @param AddressBook *book, the book to destroy
 */
void destroy_book(AddressBook *book) { 
  if(book == NULL){
    return;
  }
  for(int i = 0; i < BUCKET_CAPACITY; i++){
    destroy_bucket(book, i);
  }
  free(book->buckets);
  free(book);
}

/*
 * @brief Computes the hash of a string
 * 
 * @param const char *name, the name to be hashed
 * @return int, the hash result
 */
int hash(const char *name) {
  int hash = 0;
  for (int i = 0; i < (int)strlen(name); i++) {
    hash += name[i];
  }
  return hash % BUCKET_CAPACITY;
}
