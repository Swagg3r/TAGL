CC=gcc
CFLAGS= -O3 -fPIC
LDFLAGS= -lpthread
EXEC= moduleLib queue_test test
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
NB_THREAD= 5
TEST= sleeplock

all: $(EXEC)

moduleLib:
	@cd lock_implementation ; \
	make -f Makefile $(TEST); \
	cd ..

queue_test: $(OBJ) 
	$(CC) $^ -o $@ $(LDFLAGS) -L./lock_implementation -lmylock

main.o: queue.h

%.o: %.c
	$(CC) -c $^ $(CFLAGS)

test:
	./queue_test $(NB_THREAD) $(TEST)

clean:
	rm -rf *.o $(EXEC)
	@cd lock_implementation ; \
	make -f Makefile clean; \
	cd ..