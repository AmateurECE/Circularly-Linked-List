/*******************************************************************************
 * NAME:	    clinkedlist.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Header file for the implementation of a doubly-linked-list.
 *
 * CREATED:	    05/05/17
 *
 * LAST EDITED:	    01/02/2018
 ***/

#ifndef __ET_CLINKEDLIST_H__
#define __ET_CLINKEDLIST_H__

/*******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct _CListElmt_ {

  void * data;
  struct _CListElmt_ * next;

} CListElmt;

typedef struct _CList_ {

  void (*destroy)(void *);
  int size;
  CListElmt * head;

} CList;

/*******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define clist_size(list) ((list)->size)
#define clist_isempty(list) ((list)->size == 0 ? 1 : 0)
#define clist_head(list) ((list)->head)

/*******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern void clist_init(CList *, void (*)(void *));
extern int clist_insnxt(CList *, CListElmt *, void *);
extern int clist_remnxt(CList *, CListElmt *, void **);
extern void clist_dest(CList *);

/* TODO: Implement clist_traverse
 */

#endif /* __ET_CLINKEDLIST_H__ */

/******************************************************************************/
