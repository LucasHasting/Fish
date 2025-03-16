compile:./main.cpp
	g++ -c -g -Wall ./main.cpp ./class_implementations/Stage.cpp ./class_implementations/NewSprite.cpp ./class_implementations/Game.cpp 
	g++ main.o Game.o NewSprite.o Stage.o -o app -lsfml-graphics -lsfml-window -lsfml-system

run:
	./app
