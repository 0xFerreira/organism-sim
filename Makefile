all:
	clang++ -std=c++11 -Wall -Wpedantic -I./include src/main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o build/mlevosim.out
