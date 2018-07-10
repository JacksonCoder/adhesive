app: main.o run.o execute.o
	clang++ -o adhesive main.o run.o execute.o
main.o: src/main.cpp
	clang++ -c -o main.o src/main.cpp --std=c++14 -g
run.o: src/run.cpp include/run.h
	clang++ -c -o run.o src/run.cpp --std=c++14 -g
execute.o: src/execute.cpp include/execute.h
	clang++ -c -o execute.o src/execute.cpp --std=c++14 -g
clean:
	rm *.o
