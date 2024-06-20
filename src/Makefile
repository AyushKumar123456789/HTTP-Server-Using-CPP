# Target: server executable
server: server.o HttpRequestHandler.o RequestUtil.o ResponseUtil.o
	g++ server.o HttpRequestHandler.o RequestUtil.o ResponseUtil.o -o server -pthread -lz

# Compile server.cpp into server.o
server.o: server.cpp HttpRequestHandler.h RequestUtil.h ResponseUtil.h
	g++ -c server.cpp -o server.o -std=c++11 -Wall

# Compile HttpRequestHandler.cpp into HttpRequestHandler.o
HttpRequestHandler.o: HttpRequestHandler.cpp HttpRequestHandler.h RequestUtil.h ResponseUtil.h
	g++ -c HttpRequestHandler.cpp -o HttpRequestHandler.o -std=c++11 -Wall

# Compile RequestUtil.cpp into RequestUtil.o
RequestUtil.o: RequestUtil.cpp RequestUtil.h ResponseUtil.h
	g++ -c RequestUtil.cpp -o RequestUtil.o -std=c++11 -Wall

# Compile ResponseUtil.cpp into ResponseUtil.o
ResponseUtil.o: ResponseUtil.cpp ResponseUtil.h
	g++ -c ResponseUtil.cpp -o ResponseUtil.o -std=c++11 -Wall

# Clean target: remove executable and object files
clean:
	rm -f server *.o
