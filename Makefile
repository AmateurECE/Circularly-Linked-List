###############################################################################
# NAME:		    Makefile
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    Makefile for the Circularly Linked List test code.
#
# CREATED:	    06/06/2017
#
# LAST EDITED:	    01/03/2018
###

CC=gcc
ifeq ($(MAKECMDGOALS),debug)
    CFLAGS = -g -O0 -Wall -D CONFIG_DEBUG_CLIST
else
    CFLAGS = -Wall -O3
endif

.PHONY: debug clean force

clist:

debug: clist

clean: force
	rm -f clist
	rm -f *.o
	rm -rf *.dSYM

force:

###############################################################################
