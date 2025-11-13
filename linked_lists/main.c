#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
  int data;
  struct Node *previous;
  struct Node *next;
} Node;

void append_node(Node *head, Node *tail)
{
  if (head == NULL || tail == NULL)
    return;

  while (head->next != NULL)
  {
    head = head->next;
  }
  head->next = tail;
  tail->previous = head;
}

Node *start_insert(Node *new_head, Node *old_head)
{
  if (new_head == NULL || old_head == NULL)
    return NULL;
  new_head->next = old_head;
  old_head->previous = new_head;
  return new_head;
}

void read_linked_list(Node *head)
{
  if (head == NULL)
    return;
  while (head != NULL)
  {
    printf("%d %s ", head->data, head->next ? "->" : "");
    head = head->next;
  }
  printf("\n");
}

Node *find_head(Node *head)
{
  if (head == NULL)
    return NULL;
  while (head->previous)
  {
    head = head->previous;
  }
  return head;
}

Node *find_tail(Node *head)
{
  if (head == NULL)
    return NULL;
  while (head->next)
  {
    head = head->next;
  }
  return head;
}

int linked_list_len(Node *head)
{
  int linked_len = 0;
  if (head == NULL)
    return 0;
  while (head != NULL)
  {
    linked_len++;
    head = head->next;
  }
  return linked_len;
}

void join_linked_lists(Node *first_head, Node *second_head)
{
  if (first_head == NULL || second_head == NULL)
    return;
  Node *tail = find_tail(first_head);
  Node *head = find_tail(second_head);

  tail->next = second_head;
  second_head->previous = head;
}

void delete_node(Node *node_to_delete)
{
  if (node_to_delete == NULL)
    return;

  if (node_to_delete->previous != NULL)
    node_to_delete->previous->next = node_to_delete->next;
  if (node_to_delete->next != NULL)
    node_to_delete->next->previous = node_to_delete->previous;

  node_to_delete->previous = NULL;
  node_to_delete->next = NULL;

  free(node_to_delete);
}

int find_middle_element(Node *head)
{
  Node *fast = head;
  Node *slow = head;
  if (head == NULL)
    return -1;
  while (fast != NULL && fast->next != NULL)
  {
    fast = fast->next->next;
    slow = slow->next;
  }

  return slow->data;
}

/*
Finds first index of searched element

Args:
  *head (Node): pointer to Node struct
  number_to_find(int): searched number

Returns:
  int: index of searched element in linked_list if wasnt found then it will return -1
 */
int search_in_linked_list(Node *head, int number_to_find)
{
  if (head == NULL)
    return -1;
  int index = 0;
  while (head != NULL)
  {
    if (head->data == number_to_find)
    {
      return index;
    }
    index++;
    head = head->next;
  }
  return -1;
}

void detect_cycle()
{
}

Node *sorted_merge(Node *a, Node *b)
{
  Node dummy;
  Node *tail = &dummy;
  dummy.next = NULL;

  while (a != NULL && b != NULL)
  {
    if (a->data <= b->data)
    {
      tail->next = a;
      a = a->next;
    }
    else
    {
      tail->next = b;
      b = b->next;
    }
    tail = tail->next;
  }

  if (a != NULL)
    tail->next = a;
  else
    tail->next = b;

  return dummy.next;
}

void split_linked_list(Node *source, Node **frontref, Node **backref)
{
  if (source == NULL || source->next == NULL)
  {
    *frontref = source;
    *backref = NULL;
    return;
  }

  Node *slow = source;
  Node *fast = source->next;

  while (fast != NULL)
  {
    fast = fast->next;
    if (fast != NULL)
    {
      slow = slow->next;
      fast = fast->next;
    }
  }
  *frontref = source;
  *backref = slow->next;
  slow->next = NULL;
}

Node *sort_linked_list(Node *head)
{
  if (head->next == NULL)
    return head;

  Node *left = NULL;
  Node *right = NULL;

  split_linked_list(head, &left, &right);

  left = sort_linked_list(left);
  right = sort_linked_list(right);

  return sorted_merge(left, right);
}

/*
Removes duplicates from linked list

Args:
  Node *head of linked list we want to remove duplicates from
  Linked list needs to be sorted

Returns
  None
*/
void remove_duplicates(Node *head)
{
  if (!head || head->next == NULL)
    return;

  Node *unic = head;
  head = head->next;

  while (head)
  {
    if (head->data != unic->data)
    {
      unic->next = head;
      head->previous = unic;
      unic = head;
    }
    head = head->next;
  }
  unic->next = NULL;
}

void insert_after_node(Node *head_node, Node *node_after)
{
  if (!head_node || !node_after)
    return;

  node_after->next = head_node->next ? head_node->next : NULL;
  node_after->previous = head_node;
  if (head_node->next)
  {
    head_node->next->previous = node_after;
  }
  head_node->next = node_after;
}

Node *reverse_linked_list(Node *head)
{
  if (!head)
    return NULL;

  Node *temp;
  while (head)
  {
    temp = head->next;
    head->next = head->previous;
    head->previous = temp;

    if (!temp)
      break;
    head = temp;
  }

  return head;
}

bool check_loop(Node *head){
  Node *fast = head;
  Node *slow = head;
  while(fast && fast->next){
    fast = fast->next->next;
    slow = slow->next;
    if(fast == slow) return true;

  }
  return false;
}

int main()
{
  /*
  Node node_0 = {.data = 0};
  Node node_1 = {.data = 1};
  Node node_2 = {.data = 2};
  Node node_3 = {.data = 3};

  append_node(&node_0, &node_1);
  append_node(&node_0, &node_2);
  append_node(&node_1, &node_3);

  Node second_node_0 = {.data = 0};
  Node second_node_1 = {.data = 1};
  Node second_node_2 = {.data = 2};
  Node second_node_3 = {.data = 3};

  append_node(&second_node_0, &second_node_1);
  append_node(&second_node_0, &second_node_2);
  append_node(&second_node_1, &second_node_3);

  join_linked_lists(&node_0, &second_node_0);
  read_linked_list(&node_0);

  node_0 = *sort_linked_list(&node_0);
  read_linked_list(&node_0);

  remove_duplicates(&node_0);
  read_linked_list(&node_0);

  Node node_6 = {.data = 6};
  insert_after_node(&node_0, &node_6);
  read_linked_list(&node_0);

  Node node_reversed;
  node_reversed = *reverse_linked_list(&node_0);
  read_linked_list(&node_reversed);
  */

  Node node_0 = {.data = 0};
  Node node_1 = {.data = 1};
  Node node_2 = {.data = 2};
  Node node_3 = {.data = 3};
  Node node_4 = {.data = 4};

  append_node(&node_0, &node_1);
  append_node(&node_0, &node_2);
  append_node(&node_0, &node_3);
  node_3.next = &node_4; 
  node_4.previous = &node_3;
  node_4.next = &node_3;

  printf("%d\n", check_loop(&node_0));

  return 0;
}
