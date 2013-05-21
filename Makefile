################################################################
#
# Makefile
# A makefile.
#
################################################################
#
# This software was written in 2012 ~ 2013 by the following
# author(s):
# Brendan A R Sechter <bsechter@sennue.com>
#
# To the extent possible under law, the author(s) have
# dedicated all copyright and related and neighboring rights
# to this software to the public domain worldwide. This
# software is distributed without any warranty.
#
# You should have received a copy of the CC0 Public Domain
# Dedication along with this software. If not, see
# <http://creativecommons.org/publicdomain/zero/1.0/>.
#
# Please release derivative works under the terms of the CC0
# Public Domain Dedication.
#
################################################################

IDIR   = ./
CC     = gcc
CFLAGS = -Wall -I$(IDIR)

ODIR = ./
LDIR = ./

LIBS =

_DEPS = args.h error.h network.h command.h sqlite3.h database.h client.h server.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = args.o error.o network.o command.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all
all: client server

.PHONY: rebuild
rebuild: clean all

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

client: $(OBJ) $(ODIR)/client.o
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

server: $(OBJ) $(ODIR)/sqlite3.o $(ODIR)/database.o $(ODIR)/server.o
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ client server *.db

