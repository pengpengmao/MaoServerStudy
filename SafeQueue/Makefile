test:test.o
	gcc -o test ./test.o -lpthread
test.o:test.c safe_queue.h
	gcc -c -o test.o test.c -lpthread
clean:
	rm -f test.o test
