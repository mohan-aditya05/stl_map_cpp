CC = g++

test: test.o
	$(CC) -o test test.o -ldl
test.cpp:
	$(CC) -c test.cpp -o test.o -ldl

test-kec: test-kec.o
	$(CC) -o test-kec test-kec.o -ldl
test-kec.cpp: 
	$(CC) -c test-kec.cpp -o test-kec.o -ldl

minimal: minimal.o
	$(CC) -o minimal minimal.o -ldl
minimal.cpp: 
	$(CC) -c minimal.cpp -o minimal.o -ldl

morseex: morseex.o
	$(CC) -o morseex morseex.o -ldl
morseex.cpp: 
	$(CC) -c morseex.cpp -o morseex.o -ldl

test-scaling: test-scaling.o
	$(CC) -o test-scaling test-scaling.o -ldl
test-scaling.cpp: 
	$(CC) -c -O test-scaling.cpp -o test-scaling.o -ldl

clean:
	-rm *.o