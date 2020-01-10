
output: main.o fullmonitor.o 
	g++ -o output main.o fullmonitor.o -lpthread
	
fullmonitor.o: fullmonitor.cpp fullmonitor.h monitor.h 
	g++ -c fullmonitor.cpp -lpthread

main.o: main.cpp fullmonitor.h
	g++ -c main.cpp -lpthread

clean:
	rm fullmonitor.o
	rm main.o
	rm output
