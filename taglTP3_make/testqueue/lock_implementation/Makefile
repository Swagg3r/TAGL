CC=gcc
CFLAGS= -O3 -fPIC
LDFLAGS= -lpthread -shared


sleeping_lock: sleeping_lock.o
	$(CC) -o libmylock.so $^ $(LDFLAGS)

spin_lock: spin_lock.o
	$(CC) -o libmylock.so $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -rf *.o libmylock.so