/*
 * NAME: clinkedlist.h -- header file for a custom implementation of a circularly linked list!
 * AUTHOR: Ethan D. Twardy
 * CREATED: 05/05/17
 * LAST EDITED: 05/05/17
 */

#ifndef __ET_CLINKEDLIST__
#define __ET_CLINKEDLIST__

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

#endif /* __ET_CLINKEDLIST__ */
