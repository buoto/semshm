


all:
	g++ -c shared_queue.cpp
	g++ shared_queue.o bootstrap.cpp -o bootstrap
	g++ shared_queue.o debug_printer.cpp -o debug_printer
	g++ shared_queue.o grzyb.cpp -o grzyb
	g++ shared_queue.o mieso.cpp -o mieso
	g++ shared_queue.o ciasto.cpp -o ciasto
	g++ shared_queue.o wytwornia.cpp -o wytwornia
	g++ shared_queue.o dyspozytornia.cpp -o dyspozytornia

example:
	g++ -c shared_queue.cpp
	g++ shared_queue.o serv.cpp -o serv
	g++ shared_queue.o cli.cpp -o cli
