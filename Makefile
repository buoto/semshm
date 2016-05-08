
all:
	g++ -c shared_queue.cpp
	g++ shared_queue.o serv.cpp -o serv
	g++ shared_queue.o cli.cpp -o cli
