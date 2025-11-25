#include "singly_linked_list.h"
#include <stddef.h>
#include <stdlib.h>

static Node *prev_node_at(Node *head, size_t n) {
  auto current = head;
  Node *prev = nullptr;

  if (current) {
    size_t i = 0;
    while (i != n && current) {
      prev = current;
      current = current->next;
      ++i;
    }
    if (i != n)
      return nullptr;
    else
      return prev;
  }
  return prev;
}

Node *insert_at(Node **head, size_t n, Node *node) {
  if (!n) {
    node->next = *head;
    *head = node;
    return node;
  }
  auto prev_node = prev_node_at(*head, n);
  auto next_node = prev_node->next;
  prev_node->next = node;
  node->next = next_node;
  return node;
}

size_t list_len(Node *head) {
  auto current = head;

  if (current) {
    size_t len = 1;
    while ((current = current->next)) {
      ++len;
    }
    return len;
  }
  return 0;
}

Node *node_at(Node *head, size_t n) {
  auto current = head;

  for (size_t i = 0; i < n;) {
    if (current) {
      current = current->next;
      ++i;
    } else
      return nullptr;
  }
  return current;
}
// Node *node_idx(Node *head, size_t n);

void *delete_at(Node **head, size_t n) {
  auto current = *head;
  if (!n) {
    if ((*head)->next)
      *head = current->next;
    else
      *head = nullptr;

    return nullptr;
  } else {
    auto prev = prev_node_at(*head, n);
    auto node_to_be_deleted = prev->next;
    prev->next = node_to_be_deleted->next;

    auto data = node_to_be_deleted->data;
    free(node_to_be_deleted);
    return data;
  }
}

Node *tail(Node *head) {
  auto current = head;
  if (current) {
    auto next = current->next;
    while (next) {
      current = current->next;
      next = current->next;
    }
    return current;
  }
  return current;
}