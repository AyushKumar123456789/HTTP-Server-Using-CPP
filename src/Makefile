

server: server.o HttpRequestHandler.o
	g++ server.o HttpRequestHandler.o -o server -pthread -lz

server.o: server.cpp HttpRequestHandler.h
	g++ -c server.cpp -o server.o

HttpRequestHandler.o: HttpRequestHandler.cpp HttpRequestHandler.h
	g++ -c HttpRequestHandler.cpp -o HttpRequestHandler.o

clean:
	rm -f server *.o
