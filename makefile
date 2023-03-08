COMPILADOR = g++

LIBRERIAS_PATH = C:\SDL2MINGW\x86_64-w64-mingw32

SRC = src

CFLAGS = -std=c++17 -O2 -I"$(LIBRERIAS_PATH)\include\SDL2"

LDFLAGS = -L"$(LIBRERIAS_PATH)\lib" -lmingw32 -mwindows -mconsole -lSDL2main -lSDL2 -lSDL2_ttf 

PROG = main.exe

CPP_SOURCE = $(wildcard *.cpp) $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
CPP_HEADER = $(wildcard *.hpp) $(wildcard src/*.hpp) $(wildcard src/*/*.hpp)

$(PROG): $(CPP_SOURCE) $(CPP_HEADER)
	$(COMPILADOR) $(CFLAGS) -o $(PROG) $(CPP_SOURCE) $(LDFLAGS)

debug: $(CPP_SOURCE) $(CPP_HEADER)
	$(COMPILADOR) $(CFLAGSDEBUG) $(CPP_SOURCE) -o $(PROG)

correr:
	.\$(PROG)