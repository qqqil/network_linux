CC=g++
CFLAGS= --std=c++11 -I.

ODIR=.
LDIR =../lib

LIBS=-lm

BASE_DEPS=logger.h
DEPS=socket.h client.h server.h $(BASE_DEPS)
COBJS=logger.o socket.o threadutils.o clockutils.o

all:clean client server clean_objs
	@echo "finished"
client:client.o $(COBJS)
	@echo "client completed"
	$(CC) -o $@ $^ $(CFLAGS)
server:server.o $(COBJS) select.o
	@echo "server completed"
	$(CC) -o $@ $^ $(CFLAGS)

%.o:%.cc 
	$(CC) -c -o $@ $< $(CFLAGS)

%.o:%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean clean_objs

clean_objs:
	rm -f *.o

clean:
	rm -f *.o *~ core client server
