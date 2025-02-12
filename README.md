# Data Structures: Linked List, Binary Search Tree, and Hash Table

This repository contains implementations of three fundamental data structures:

- **Linked List**
- **Binary Search Tree (BST)**
- **Hash Table**

Each data structure is implemented in C with basic operations such as insertion, deletion, and search.

## 1. Linked List

A **Linked List** is a dynamic data structure consisting of nodes. Each node contains:

- **Data** (the actual information stored in the list)
- **Pointer** (a reference to the next node in the list)
<br>

![linkedlist](https://github.com/user-attachments/assets/7f7fc4f8-c2b1-4d37-a13e-591800f9a585)
### Linked List Operations

1. **Create a Node**
   ```c
   struct list* CreateNode(int key);
   ```
   - Allocates memory for a new node and initializes it with the given key.

2. **Print the Linked List**
   ```c
   void PrintLinkedList(struct list *root);
   ```
   - Iterates through the list and prints each node's key.

3. **Add a Node to the End**
   ```c
   void AddToEnd(struct list **root, int key);
   ```
   - Traverses the list and appends a new node at the end.

4. **Add a Node to the Head**
   ```c
   void AddToHead(struct list **root, int key);
   ```
   - Creates a new node and inserts it at the beginning of the list.

5. **Delete a Node from the End**
   ```c
   void DeleteFromEnd(struct list **root);
   ```
   - Removes the last node from the linked list.

6. **Delete a Node from the Head**
   ```c
   void DeleteFromHead(struct list **root);
   ```
   - Removes the first node from the linked list.

7. **Add a Node After a Given Key**
   ```c
   void AddNodeAfterKey(struct list **root, int key, int key2);
   ```
   - Finds a node with `key` and inserts a new node with `key2` after it.

8. **Delete a Node with a Given Key**
   ```c
   void DeleteNodeWithKey(struct list **root, int key);
   ```
   - Removes a node that matches the given key.

9. **Reverse the Linked List**
   ```c
   void ReverseLinkedList(struct list **root);
   ```
   - Reverses the linked list using an iterative approach.

---


## 2. Binary Search Tree (BST)

A **Binary Search Tree (BST)** is a hierarchical data structure where:

- Each node has at most two children (left and right).
- The left subtree contains nodes with values **less than** the parent.
- The right subtree contains nodes with values **greater than** the parent.
<br>

![binarysearchtree](https://github.com/user-attachments/assets/e91b2b9f-81f7-4ff0-ab38-9abed107f89f)

### BST Operations

1. **Create a Node**
   ```c
   struct list* CreateNode(int key);
   ```
   - Creates a new BST node with the given key.

2. **Print the Tree**
   ```c
   void printTree(struct Tree *root, int space);
   ```
   - Prints the BST structure in a hierarchical format.

3. **Insert a Node**
   ```c
   void AddToTree(struct Tree **root, int key);
   ```
   - Inserts a node into the BST while maintaining the BST properties.

4. **Delete a Node**
   ```c
   void DeleteFromTree(struct Tree **root, int key);
   ```
   - Deletes a node with the given key from the BST.

5. **Count Nodes with a Single Child**
   ```c
   int Count_Single_Child_Nodes(struct Tree *root);
   ```
   - Counts and returns the number of nodes with exactly one child.

6. **Free the Tree**
   ```c
   void FreeTree(struct Tree *root);
   ```
   - Frees all dynamically allocated nodes in the BST.

---


## 3. Hash Table

A **Hash Table** is a data structure that maps keys to values using a **hash function**. It provides fast lookups and efficient data storage.

### Components:
- **Hash Function** (converts a key into an index)
- **Collision Handling** (methods such as chaining or open addressing)
- **Buckets** (storage locations for key-value pairs)
<br>

![hashfunction](https://github.com/user-attachments/assets/d3dad6e1-4e5e-4698-bd09-47f356213be2)

### Hash Table Operations

1. **Create a Hash Table**
   ```c
   void initialize_hash_table(struct Hash_table **hashtable, int multiplier, int table_size);
   ```
   - Initializes a new hash table with the specified multiplier and table size.

2. **Insert a Key**
   ```c
   void insert_hash_table(struct Hash_table *hashtable, char *key);
   ```
   - Inserts a key into the hash table. If the key already exists, it will not be added again.

3. **Delete a Key**
   ```c
   void delete_from_table(char *key, struct Hash_table *hashtable);
   ```
   - Deletes a key from the hash table.

4. **Lookup a Key**
   ```c
   int lookup(char *key, struct Cell *list_head);
   ```
   - Checks if a key exists in the hash table. Returns 1 if found, 0 if not.

5. **Expand the Hash Table**
   ```c
   void expand_table(struct Hash_table **hashtable, int multiplier, int table_size);
   ```
   - Expands the hash table by creating a new table with the given size and rehashing all existing keys.

6. **Print the Hash Table**
   ```c
   void print_hash_table(struct Hash_table *hash_table);
   ```
   - Prints the entire hash table with keys in each bucket and the number of elements per bucket.

7. **Free the Hash Table**
   ```c
   void free_hash(struct Hash_table **htable);
   ```
   - Frees all dynamically allocated memory used by the hash table.

8. **Fill the Hash Table from a Linked List**
   ```c
   void Fill_table_from_list(struct Hash_table *htable, struct Cell **list_head);
   ```
   - Fills the hash table using elements from a linked list, inserting each key into the appropriate bucket.

9. **Fill the Linked List from a Hash Table**
   ```c
   void Fill_list_from_table(struct Hash_table *htable, struct Cell **list_head);
   ```
   - Fills a linked list using keys from a hash table, gathering all the keys into a single linked list.

---

## Installation and Usage

```bash
# Clone the repository
git clone https://github.com/yourusername/your-repo.git

# Navigate to the project directory
cd your-repo

# Compile the C files
gcc linked_list.c bst.c hash_table.c -o datastructures

# Run the executable
./datastructures
```
---