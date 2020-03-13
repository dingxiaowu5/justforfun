

object := $(patsubst %.cpp,%.o,$(wildcard *.cpp));

cflag := -pthread -std=c++11


all:main client

main:main.o socketpar.o socketserver.o 
	g++ $(cflag) -o $@ $^


client:client.o socketpar.o socketclient.o
	g++ $(cflag) -o $@ $^


%.o:%.c
	echo $(object)
	echo $(cflag)
	g++  -c $^ $(cflag) -o $@


clean:
	rm main
	rm client
	rm *.o

