SRCS := $(wildcard ./class_implementations/*.cpp)

OBJS := $(SRCS:.cpp=.o)

compile: $(OBJS)
	g++ -c -g -Wall ./driver/main.cpp ${SRCS}
	g++ main.o ${OBJS} -o app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

run:
	./app

clean:
	@rm *.o
	@rm ./class_implementations/*.o
	@rm app
