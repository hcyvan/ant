CC=g++ -Wall -std=c++11
OBJECTS=main.o lib.o tcp.o http.o dns.o
ant:$(OBJECTS)
	$(CC) $(OBJECTS) -o ant
main.o:main.cc
	$(CC) -c main.cc -o main.o


# general rule
%.o:%.cc %.h makefile
	$(CC) -c $< -o $@

.PHONY:clean
clean:
	rm -f $(OBJECTS) ant
