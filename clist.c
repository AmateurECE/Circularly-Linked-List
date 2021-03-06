/******************************************************************************
 * NAME:	    clist.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    API functions and test code for the types and prototypes
 *		    outlined in clinkedlist.h; a circularly-linked list.
 *
 * CREATED:	    05/05/17
 *
 * LAST EDITED:	    03/08/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef CONFIG_DEBUG_CLIST
#include <time.h>
#include <assert.h>
#endif

#include "clist.h"

/******************************************************************************
 * LOCAL PROTOTYPES
 ***/

#ifdef CONFIG_DEBUG_CLIST
static inline void error_exit(char *);
#endif

/******************************************************************************
 * API FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    clist_create
 *
 * DESCRIPTION:	    Creates a new clist struct, and returns a pointer to it.
 *
 * ARGUMENTS:	    destroy: (void (*)(void *)) -- function pointer to free the
 *		    data held in a node.
 *
 * RETURN:	    (clist *) -- pointer to the new struct, or NULL if there
 *		    was an error.
 *
 * NOTES:	    O(1)
 ***/
clist * clist_create(void (*destroy)(void *))
{
  clist * list = NULL;
  if ((list = malloc(sizeof(clist))) == NULL)
    return NULL;
  
  list->head = NULL;
  list->destroy = destroy;
  list->size = 0;

  return list;
}

/******************************************************************************
 * FUNCTION:	    clist_insnxt
 *
 * DESCRIPTION:	    Inserts 'data' in a new node placed after 'node.'
 *
 * ARGUMENTS:	    list: (Clist *) -- the list to be operated on.
 *		    node: (clistelmt *) -- the reference node.
 *		    data: (void *) -- the data to be inserted.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(1)
 ***/
int clist_insnxt(clist * list, clistelmt * node, void * data)
{
  clistelmt * new_elmt;
  if ((new_elmt = (clistelmt *)malloc(sizeof(clistelmt))) == NULL)
    return -1;

  new_elmt->data = data;

  if (clist_isempty(list)) {
    /* Handle insertion when the list is empty. */

    new_elmt->next = new_elmt;
    list->head = new_elmt;

  } else {
    /* Handle insertion when it's not. */

    new_elmt->next = node->next;
    node->next = new_elmt;

  }

  list->size++;
  return 0;
}

/******************************************************************************
 * FUNCTION:	    clist_remnxt
 *
 * DESCRIPTION:	    Removes the node after 'node' and places its data in 'data'
 *
 * ARGUMENTS:	    list: (Clist *) -- the list to be operated on.
 *		    node: (clistelmt *) -- the reference node.
 *		    data: (void *) -- the data that was removed.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(1)
 ***/
int clist_remnxt(clist * list, clistelmt * node, void ** pData)
{
  if (clist_isempty(list))
    return -1;

  *pData = node->next->data;
  clistelmt * old;

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

/******************************************************************************
 * FUNCTION:	    clist_destroy
 *
 * DESCRIPTION:	    Removes all nodes and sets all bytes of memory in the clist
 *		    structure to 0. If 'destroy' is set to NULL, does not
 *		    destroy the data.
 *
 * ARGUMENTS:	    list: (Clist **) -- the list to be destroyed.
 *
 * RETURN:	    void.
 *
 * NOTES:	    O(n)
 ***/
void clist_destroy(clist ** list)
{
  if (list == NULL || *list == NULL)
    return;

  void * pData;
  while (!clist_remnxt(*list, clist_head(*list), (void **)&pData))
    (*list)->destroy(pData);

  free(*list);
  *list = NULL;
}

/******************************************************************************
 * MAIN
 ***/

#ifdef CONFIG_DEBUG_CLIST
int main(int argc, char * argv[])
{
  int * pNum;
  clist * list;

  if ((list = clist_create(free)) == NULL)
    error_exit("Could not allocate memory for list!");

  srand((unsigned)time(NULL));

  /* Populate the list */
  printf("==== Inserting ====\n");
  for (int i = 0; i < 10; i++) {
    pNum = (int *)malloc(sizeof(int));
    *pNum = rand() % 10;
    printf("int %d @ %p\n", *pNum, pNum);
    clist_insnxt(list, clist_head(list), (void *)pNum);
  }

  /* Remove from the list */
  printf("==== Removing =====\n");
  for (int i = 0; i < 10; i++) {
    clist_remnxt(list, clist_head(list), (void **)&pNum);
    printf("int %d @ %p\n", *pNum, pNum);
    free(pNum);
  }

  clist_destroy(&list);

  return 0;
}
#endif

/******************************************************************************
 * LOCAL FUNCTIONS
 ***/

#ifdef CONFIG_DEBUG_CLIST
static inline void error_exit(char * msg)
{
  fprintf(stderr, "%s\n", msg);
  exit(1);
}
#endif

/*****************************************************************************/
