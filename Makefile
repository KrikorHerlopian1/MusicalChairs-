CC = g++
CFLAGS = -std=c++11 -Wall -g -lpthread
DEPS = Global.hpp Kid.hpp Model.hpp Mom.hpp tools.hpp

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

p5: main.o main.o Global.o Kid.o Model.o Mom.o tools.o
	$(CC) $(CFLAGS) -o p5 main.o Global.o Kid.o Model.o Mom.o tools.o

clean:
	rm -f *.o p5

