#pragma once
#include <stddef.h>

/**
 * Node of the single list
 * @note Thanks to the `void` pointer the linked list can store any datatype.
 */
typedef struct Node {
  void *data;
  struct Node *next;
} Node;

/**
 * Inserts `node` at the 0-indexed position `n` on the list with the start
 * node`head`.
 * @return `Node *` that has been inserted.
 * @note `head` is a pointer to a pointer, because we need to be
able to modify the head of the provided linked list.
 */
Node *insert_at(Node **head, size_t n, Node *node);

/**
 * @return size of the list
 */
size_t list_len(Node *head);

/**
 * @return node at the index `n`
 */
Node *node_at(Node *head, size_t n);

/**
 * Deletes and deallocates node at index `n`.
 * @return node data
 * @note Data of the node has to be deallocated manually.
 */
void *delete_at(Node **head, size_t n);

/**
 * Deletes and deallocates node at index `n`.
 * @return the node at the tail of the list.
 * @note Can return `nullptr` if the list is empty.
 */
Node *tail(Node *head);