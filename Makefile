
CC=g++
CFLAGS=-I. -g -Wall
%.o:%.cpp
	$(CC) -fPIC -c -o $@ $< $(CFLAGS)
all:clean client server select poll epoll net
	@echo "client ,server ,select,poll,epoll"
net:net.o
	$(CC)  --shared -fPIC  -o libnet.so $^
client:client.o
	$(CC) -o $@ $^
server:server.o
	$(CC) -o $@ $^

select:s_select.o
	$(CC) -o $@ $^

poll:s_poll.o
	$(CC) -o $@ $^

epoll:s_epoll.o
	$(CC) -o $@ 
test:clean  net test.o
	$(CC) -o test test.o -L. -lnet
.PHONY:clean

clean:
	rm *.o client server select poll epoll test -f
