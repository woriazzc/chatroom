CC=g++
all: server client
client: client.cpp
	$(CC) -o client client.cpp -lpthread
server: server.cpp mysqlControler
	$(CC) -o server server.cpp ./out/mysqlControler.o -lmysqlclient -ljson
test: test.cpp
	$(CC) -o test test.cpp -lmysqlclient -ljson
mysqlControler: ./utils/mysqlControler.cpp
	$(CC) -c ./utils/mysqlControler.cpp -lmysqlclient -ljson -o ./out/mysqlControler.o
clean:
	rm *.o