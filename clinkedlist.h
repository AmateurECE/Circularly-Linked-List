/*
 * NAME: clinkedlist.h -- header file for a custom implementation of a circularly linked list!
 * AUTHOR: Ethan D. Twardy
 * CREATED: 05/05/17
 * LAST EDITED: 05/05/17
 */

#ifndef __ET_CLINKEDLIST__
#define __ET_CLINKEDLIST__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/************* TYPE DEFINITIONS *************/
/********************************************/

typedef struct _CListElmt_ {

  void * data;
  struct _CListElmt_ * next;

} CListElmt;

typedef struct _CList_ {

  void (*destroy)(void *);
  int size;
  CListElmt * head;

} CList;

/************* MACRO DEFINITIONS ************/
/********************************************/

#define clist_size(list) ((list)->size)
#define clist_isempty(list) ((list)->size == 0 ? 1 : 0)
#define clist_head(list) ((list)->head)

/************* PUBLIC INTERFACE *************/
/********************************************/

// FUNCTION: clist_init O(1) -- initializes the list in list.
// PARAMETERS: list: (CList *) -- the list to be initialized
//             destroy: (void (*)(void *)) -- function pointer to free the data in the CListElmt.
// RETURN: void
void clist_init(CList * list, void (*destroy)(void *))
{
  list->head = NULL;
  list->destroy = destroy;
  list->size = 0;
}

// FUNCTION: clist_insnxt O(1) -- inserts the data in a new node after node parameter.
// PARAMETERS: list: (CList *) -- the list to be operated on.
//             node: (CListElmt *) -- the reference node.
//             data: (void *) -- the data to be inserted.
// RETURN: int -- -1 on failure, 0 on success.
int clist_insnxt(CList * list, CListElmt * node, void * data)
{
  CListElmt * new_elmt;
  if ((new_elmt = (CListElmt *)malloc(sizeof(CListElmt))) == NULL)
    return -1;

  new_elmt->data = data;

  if (clist_isempty(list)) {
    // Handle insertion when the list is empty.

    new_elmt->next = new_elmt;
    list->head = new_elmt;

  } else {
    // Handle insertion when it's not.

    new_elmt->next = node->next;
    node->next = new_elmt;

  }

  list->size++;
  return 0;
}

// FUNCTION: clist_remnxt O(1) -- remove the data after the reference node parameter.
// PARAMETERS: list: (CList *) -- the list to be operated on.
//             node: (CListElmt *) -- the reference node.
//             pData: (void **) -- data in the removed node is placed here.
// RETURN: int -- -1 on failure, 0 on success.
int clist_remnxt(CList * list, CListElmt * node, void ** pData)
{
  if (clist_isempty(list))
    return -1;

  *pData = node->next->data;
  CListElmt * old;

  if (node == clist_head(list)) {

    old = list->head->next;
    list->head->next = old->next;;
    
  } else {
    
    old = node->next;
    node->next = node->next->next;

  }

  list->size--;
  free(old);
  return 0;
}

// FUNCTION: clist_dest O(n) -- removes all nodes and sets the memory to 0.
// PARAMETERS: list: (CList *) -- the list to be destroyed.
// RETURN: void
void clist_dest(CList * list)
{
  if (clist_isempty(list))
    return;

  void * pData;
  while (!clist_isempty(list)) {

    clist_remnxt(list, clist_head(list), (void **)&pData);
    list->destroy(pData);

  }

  memset(list, 0, sizeof(CList));
}

#endif // __ET_CLINKEDLIST__
