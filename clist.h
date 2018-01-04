/******************************************************************************
 * NAME:	    clinkedlist.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Header file for the implementation of a
 *		    circulary-linked-list.
 *
 * CREATED:	    05/05/17
 *
 * LAST EDITED:	    01/03/2018
 ***/

#ifndef __ET_CLINKEDLIST_H__
#define __ET_CLINKEDLIST_H__

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct _clistelmt_ {

  void * data;
  struct _clistelmt_ * next;

} clistelmt;

typedef struct {

  void (*destroy)(void *);
  int size;
  clistelmt * head;

} clist;

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define clist_size(list) ((list)->size)
#define clist_isempty(list) ((list)->size == 0 ? 1 : 0)
#define clist_head(list) ((list)->head)

/* TODO: Implement more macros (found in Doubly-Linked-List)
 */

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern clist * clist_create(void (*destroy)(void *));
extern int clist_insnxt(clist * list, clistelmt * node, void * data);
extern int clist_remnxt(clist * list, clistelmt * node, void ** pData);
extern void clist_destroy(clist ** pList);

/* TODO: Implement clist_traverse
 */

#endif /* __ET_CLINKEDLIST_H__ */

/*****************************************************************************/
