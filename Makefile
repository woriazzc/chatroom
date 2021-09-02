CC=g++
all: server client
client: client.cpp
	$(CC) -o client client.cpp -lpthread
server: server.cpp
	$(CC) -o server server.cpp
test: test.cpp
	$(CC) -o test test.cpp -I/usr/include/mysql -L/usr/lib64/mysql -lmysqlclient -ljson
clean:
	rm *.o