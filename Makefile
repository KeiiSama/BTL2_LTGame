all:
	g++ -Isrc/include -Lsrc/lib -o main main.cpp mainSDL.cpp startButton.cpp menu.cpp gamePlaying1.cpp -lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2