sh = min_heap.h
test:test.o
	gcc -o test ./test.o
test.o:test.c $(sh)
	gcc -c -o test.o test.c 
clean:
	rm -f test.o test
