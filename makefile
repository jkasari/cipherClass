test: testCipher
	./testCipher

testCipher: cipherClasses
	g++ -std=c++17 cipherClasses.o testCipher.cpp -o testCipher

cipherClasses:
	g++ -std=c++17 -Wall -Wpedantic -c cipherClasses.cpp

clean:
	rm -rf testCipher *.o

.PHONY: test testCipher cipherClasses clean