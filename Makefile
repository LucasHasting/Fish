compile:./main.cpp
	g++ -c -g -Wall ./main.cpp ./class_implementations/Stage.cpp ./class_implementations/Game.cpp ./class_implementations/NewSprite.cpp
	g++ main.o Stage.o Game.o NewSprite.o -o app -lsfml-graphics -lsfml-window -lsfml-system

run:
	./app
