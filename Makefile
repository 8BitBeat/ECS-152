SSQueue.out: phase1.o server.o event.o
	g++ -g -Wall -ansi -o testing.out phase1.o server.o event.o
	
phase1.o: phase1.cpp server.h event.h
	g++ -g -Wall -ansi -c phase1.cpp
	
server.o: server.cpp server.h 
	g++ -g -Wall -ansi -c server.cpp
	
event.o: event.cpp event.h 
	g++ -g -Wall -ansi -c event.cpp