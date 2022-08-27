name    := spaget
outfol  := out
tocompil:= $(wildcard code/*.cpp)
# -D
defines  := -DOS_LINUX
defines-d:= -D_DEBUG
defines-r:= -D_RELEASE

w_defines:= -DOS_WINDOWS
# -I
include  := -I/usr/local/include -Icode

w_include:= -IC:/compilerAndLibs/sfml_2-5-1-x64/include
# -L
libspath  := -L/usr/local/lib
w_libspath:= -LC:/compilerAndLibs/sfml_2-5-1-x64/lib
# -l
libs-d  := $(libspath) -lsfml-window-d -lsfml-graphics-d -lsfml-system-d -lsfml-audio-d
libs-r  := $(libspath) -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio

libs-d-s:= $(libspath) -lsfml-window-s-d -lsfml-system-s-d -lsfml-graphics-s-d -lsfml-audio-s-d -ludev -lXrandr -lX11 -lGLX -lfreetype -lGL -lFLAC -logg -lvorbis -lvorbisenc -lvorbisfile
libs-r-s:= $(libspath) -lsfml-window-s -lsfml-system-s -lsfml-graphics-s -lsfml-audio-s -ludev -lXrandr -lX11 -lGLX -lfreetype -lGL -lFLAC -logg -lvorbis -lvorbisenc -lvorbisfile

w_libs-r-s:=$(libspath) -lsfml-main -lsfml-windows- -lsfml-system-s -lsfml-graphics-s -lsfml-audio-s -lopengl32 -lfreetype -lvorbis -lvorbisenc -lvorbisfile

all: linuxRelease

linuxDebug:
	@clear
	@echo Compiling Debug version for Linux via g++
	g++ -fdiagnostics-color=always -g $(defines) $(defines-d) $(include) $(tocompil) $(libs-r) -o $(outfol)/$(name)_debug
	@echo Done
linuxRelease:
	@clear
	@echo Compiling Release version for Linux via g++
	g++ $(defines) $(defines-r) $(include) $(tocompil) $(libs-r) -o $(outfol)/$(name)
	@echo Done
windows:
	@echo Compiling Release version for Windows via mingw64 g++
	g++ $(w_defines) $(defines-r) $(w_include) $(tocompil) $(w_libs-r-s) -o $(outfol)/$(name)

