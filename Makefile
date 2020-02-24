a.out: main.o coroutine.o
	g++ -o a.out main.o coroutine.o
main.o: main.cpp coroutine.h
	g++ -c main.cpp
coroutine.o: coroutine.cpp coroutine.h
	g++ -c coroutine.cpp coroutine.h
clean:
	rm *.o 
