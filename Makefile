
CC=g++
CFLAGS=-I. -g -Wall
%.o:%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)
all:clean client server
	@echo "client ,server"
client:client.o
	$(CC) -o $@ $^
server:server.o
	$(CC) -o $@ $^

.PHONY:clean

clean:
	rm *.o client server -f
