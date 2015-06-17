
CC=g++
CFLAGS=-I. -g -Wall
%.o:%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)
all:clean client server select poll epoll
	@echo "client ,server ,select,poll,epoll"
client:client.o
	$(CC) -o $@ $^
server:server.o
	$(CC) -o $@ $^

select:s_select.o
	$(CC) -o $@ $^

poll:s_poll.o
	$(CC) -o $@ $^

epoll:s_epoll.o
	$(CC) -o $@ $^
.PHONY:clean

clean:
	rm *.o client server select poll epoll -f
