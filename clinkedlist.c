/*
 * NAME: clinkedlist.c -- test script for the implementation of the
 *       circularly linked list in clinkedlist.h
 * AUTHOR: Ethan D. Twardy
 * CREATED: 05/05/17
 * LAST EDITED: 05/05/17
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "clinkedlist.h"

static inline void error_exit(char * msg)
{
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

int main(int argc, char * argv[])
{
  int * pNum;
  CList * list;

  if ((list = malloc(sizeof(CList))) == NULL)
    error_exit("Could not allocate memory for list!");

  srand((unsigned)time(NULL));

  // Populate the list
  printf("==== Inserting ====\n");
  for (int i = 0; i < 10; i++) {
    pNum = (int *)malloc(sizeof(int));
    *pNum = rand() % 10;
    printf("int %d @ %p\n", *pNum, pNum);
    clist_insnxt(list, clist_head(list), (void *)pNum);
  }

  // Remove from the list
  printf("==== Removing =====\n");
  for (int i = 0; i < 10; i++) {
    clist_remnxt(list, clist_head(list), (void **)&pNum);
    printf("int %d @ %p\n", *pNum, pNum);
    free(pNum);
  }

  clist_dest(list);
  free(list);

  return 0;
}
