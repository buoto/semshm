BINS=bootstrap debug_printer grzyb mieso ciasto wytwornia dyspozytornia
LIB=shared_queue.o

.PHONY: all clean example

all: $(BINS)

$(BINS): $(LIB)
	g++ shared_queue.o $@.cpp -o $@

$(LIB):
	g++ -c $(@:.o=.cpp)

clean:
	rm $(BINS) serv cli *.o

example: $(LIB)
	g++ shared_queue.o serv.cpp -o serv
	g++ shared_queue.o cli.cpp -o cli
