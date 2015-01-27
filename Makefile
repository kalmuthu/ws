OBJS=server.o simple_http.o content.o main.o util.o thread_per_request.o linkedlist.o threadpool.o thread_pool_request.o
CFLAGS=-g -I. -Wall -Wextra -pthread
#DEFINES=-DTHINK_TIME
BIN=server
CC=gcc

%.o:%.c
	$(CC) $(CFLAGS) $(DEFINES) -o $@ -c $<

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(DEFINES) -o $(BIN) $^

clean:
	rm $(BIN) $(OBJS)

test0:
	./server 8080 0 &
	httperf --port=8080 --server=localhost --num-conns=1
	killall server

test1:
	./server 8080 1 &
	sleep 5
	httperf --port=8080 --server=localhost --num-conns=1000 --burst-len=100
	killall server

test2:
	./server 8080 2 &
	sleep 5
	httperf --port=8080 --server=localhost --num-conns=1000 --burst-len=100
	killall server

valgrind1:
	valgrind --leak-check=full --dsymutil=yes --track-origins=yes ./server 8080 1 &
	sleep 5
	httperf --port=8080 --server=localhost --num-conns=1000 --burst-len=100
	killall server

valgrind2:
	valgrind --leak-check=yes --dsymutil=no ./server 8080 2 &
	sleep 5
	httperf --port=8080 --server=localhost --num-conns=1000 --burst-len=100
	killall server
