exe:	main.cpp
	g++ *.cpp src/*.cpp src/*.c `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes 

a:      main.cpp
	g++ *.cpp -g -fsanitize=address src/*.cpp src/*.c `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes 
r:
	./a.out

clean:
	rm a.out

c:
	rm a.out
