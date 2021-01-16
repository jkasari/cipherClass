main:
	g++ -std=c++17 main.cpp -o run

test:
	g++ -std=c++17 test.cpp -o test
	./test

clean:
	rm -rf run test
	
.PHONY: main test clean
