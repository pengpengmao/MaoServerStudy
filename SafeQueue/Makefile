test:test.o
	gcc -o test ./test.o -lpthread
test.o:test.c safe_queue.h
	gcc -c -o test.o test.c -lpthread
wait_test:wait_test.o
	gcc -o wait_test wait_test.o -lpthread
wait_test.o:wait_test.c safe_queue.h
	gcc -c -o wait_test.o wait_test.c -lpthread
clean:
	rm -f test.o test wait_test.o wait_test
