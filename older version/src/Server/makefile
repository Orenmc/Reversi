# 305164295

# cohenorx

a.out: Server.o main.o
	g++ Server.o main.o
Server.o: Server.cpp Server.h
	g++ -c Server.cpp -pthread
main.o: main.cpp Server.h
	g++ -c main.cpp -pthread

