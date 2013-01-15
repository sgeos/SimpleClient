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

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: client server

client: $(OBJ) $(ODIR)/client.o
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

server: $(OBJ) $(ODIR)/sqlite3.o $(ODIR)/database.o $(ODIR)/server.o
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ client server *.db

