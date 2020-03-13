

object := $(patsubst %.cpp,%.o,$(wildcard *.cpp));

cflag := -pthread -std=c++11


all:main

main:$(object)
	g++ $(cflag) -o $@ $(object)


%.o:%.c
	echo $(object)
	echo $(cflag)
	g++  -c $^ $(cflag) -o $@


clean:
	rm *.o

