CC=g++
all: server client
client: client.cpp
	$(CC) -o client client.cpp -lpthread
server: server.cpp mysqlControler utils
	$(CC) -o server server.cpp ./out/mysqlControler.o ./out/utils.o -lmysqlclient -ljson
test: test.cpp
	$(CC) -o test test.cpp -lmysqlclient -ljson
mysqlControler: ./utils/mysqlControler.cpp
	$(CC) -c ./utils/mysqlControler.cpp -lmysqlclient -ljson -o ./out/mysqlControler.o
utils: ./utils/utils.cpp
	$(CC) -c ./utils/utils.cpp -o ./out/utils.o
clean:
	rm -rf ./out/*.o