CC = g++
CFLAGS = -g -fexceptions


ifeq ($(OS),Windows_NT)
	INCLUDE_DIR_SDL = 	-Iextern/SDL2_mingw/SDL2-2.0.3/include \
						-Iextern/SDL2_mingw/SDL2_ttf-2.0.12/i686-w64-mingw32/include/SDL2 \
						-Iextern/SDL2_mingw/SDL2_image-2.0.0/i686-w64-mingw32/include/SDL2 \
						-Iextern/SDL2_mingw/SDL2_mixer-2.0.1/i686-w64-mingw32/include/SDL2
	LIBS_SDL = 	-Lextern \
			-Lextern/SDL2_mingw/SDL2-2.0.3/i686-w64-mingw32/lib \
			-Lextern/SDL2_mingw/SDL2_ttf-2.0.12/i686-w64-mingw32/lib \
			-Lextern/SDL2_mingw/SDL2_image-2.0.0/i686-w64-mingw32/lib \
			-Lextern/SDL2_mingw/SDL2_mixer-2.0.1/i686-w64-mingw32/lib \
			-lmingw32 -lSDL2main -lSDL2.dll -lSDL2_ttf.dll -lSDL2_image.dll -lSDL2_mixer.dll
else
	INCLUDE_DIR_SDL = -I/usr/include/SDL2
	LIBS_SDL = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
endif

NAME = exemple test sdl serveur
PATH_SRC = ./src/main/
PATH_SRC1 = ./src/txt/
PATH_SRC2 = ./src/test/
PATH_SRC3 = ./src/sdl2/
PATH_SRC4 = ./src/serveur/
PATH_SRC5 = ./src/socklib/
PATH_OBJ = ./obj/
PATH_INC = ./src/main/
PATH_INC_SDL = ./src/sdl2/
PATH_INC_SERV = ./src/serveur/
PATH_INC_SOCK = ./src/socklib/
FILES_BASE = ElementTD.cpp TableauDynamique.cpp push_swap.cpp jeu.cpp Sort.cpp client.cpp
FILES_SDL = affichage_SDL.cpp bouton_SDL.cpp main2_SDL.cpp
FILES_TEXT = main_text.cpp
FILES_TEST = maintest.cpp
FILES_SERVEUR = serveur.cpp
FILES_SOCKLIB = socklib.cpp readerwriter.cpp bufferedreaderwriter.cpp
FILES_H = ElementTD.h TableauDynamique.h push_swap.h jeu.h
FILES_H2 = affichage_SDL.h bouton_SDL.h
FILES_H3 = client.h
FILES_H4 = socklib.hpp readerwriter.hpp bufferedreaderwriter.hpp
OBJ_IMG = $(addprefix $(PATH_OBJ), $(FILES_BASE:.cpp=.o)) $(addprefix $(PATH_OBJ), $(FILES_TEXT:.cpp=.o)) $(addprefix $(PATH_OBJ), $(FILES_SOCKLIB:.cpp=.o))
OBJ_IMG2 = $(addprefix $(PATH_OBJ), $(FILES_BASE:.cpp=.o)) $(addprefix $(PATH_OBJ), $(FILES_TEST:.cpp=.o)) $(addprefix $(PATH_OBJ), $(FILES_SOCKLIB:.cpp=.o))
OBJ_IMG3 = $(addprefix $(PATH_OBJ), $(FILES_BASE:.cpp=.o)) $(addprefix $(PATH_OBJ), $(FILES_SDL:.cpp=.o)) $(addprefix $(PATH_OBJ), $(FILES_SOCKLIB:.cpp=.o))
OBJ_SERV = $(addprefix $(PATH_OBJ), $(FILES_SERVEUR:.cpp=.o)) $(addprefix $(PATH_OBJ), $(FILES_SOCKLIB:.cpp=.o)) ./obj/ElementTD.o ./obj/TableauDynamique.o ./obj/push_swap.o ./obj/jeu.o ./obj/Sort.o
SRC_IMG = $(addprefix $(PATH_SRC), $(FILES_BASE))
INC_IMG = $(addprefix $(PATH_INC), $(FILES_H))
INC_IMG2 = $(addprefix $(PATH_INC_SDL), $(FILES_H2))
INC_IMG3 = $(addprefix $(PATH_INC_SERV), $(FILES_H3))
INC_IMG4 = $(addprefix $(PATH_INC_SOCK), $(FILES_H4))

#******************************************************************************#
#                                    ALL                                       #
#******************************************************************************#

all: $(NAME)

#******************************************************************************#
#                             Compilation image                               #
#******************************************************************************#
serveur :$(OBJ_SERV)
	@$(CC) $(CFLAGS)  $(OBJ_SERV)  $(LIBS_SDL) -L ./ -o ./bin/serveur
	@echo "   👍  👍  👍 \033[1mSERVEUR CREATED\033[0m 👍  👍  👍"

sdl : $(OBJ_IMG3)
	@$(CC) $(CFLAGS)  $(OBJ_IMG3)  $(LIBS_SDL) -L ./ -o ./bin/sdl
	@echo "   👍  👍  👍 \033[1mSDL CREATED\033[0m 👍  👍  👍"

exemple : $(OBJ_IMG2)
	@$(CC) $(CFLAGS) $(OBJ_IMG2) $(LIBS_SDL) -L ./ -o ./bin/exemple
	@echo "   👍  👍  👍 \033[1mEXEMPLE CREATED\033[0m 👍  👍  👍"

test : $(OBJ_IMG)
	@$(CC) $(CFLAGS)  $(OBJ_IMG)  $(LIBS_SDL) -L ./ -o ./bin/test
	@echo "   👍  👍  👍 \033[1mTEST CREATED\033[0m 👍  👍  👍"

$(PATH_OBJ)%.o: $(PATH_SRC5)%.cpp $(INC_IMG4)
		@echo $(CC) $(CFLAGS) -c $< -o $@ -I $(PATH_INC_SOCK) $(INCLUDE_DIR_SDL)
		@$(CC) $(CFLAGS) -std=c++11 -c $< -o $@ -I $(PATH_INC_SOCK) $(INCLUDE_DIR_SDL)

$(PATH_OBJ)%.o: $(PATH_SRC4)%.cpp
		@echo $(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE_DIR_SDL)
		@$(CC) $(CFLAGS) -std=c++11 -c $< -o $@ -I $(INCLUDE_DIR_SDL)

$(PATH_OBJ)%.o: $(PATH_SRC3)%.cpp $(INC_IMG2)
	@echo $(CC) $(CFLAGS) -c $< -o $@ -I $(PATH_INC_SDL) $(INCLUDE_DIR_SDL)
	@$(CC) $(CFLAGS) -std=c++11 -c $< -o $@ -I $(PATH_INC_SDL) $(INCLUDE_DIR_SDL)

$(PATH_OBJ)%.o: $(PATH_SRC1)%.cpp
	@echo $(CC) $(CFLAGS) -c $< -o $@ -I $(PATH_INC) $(INCLUDE_DIR_SDL)
	@$(CC) $(CFLAGS) -std=c++11 -c $< -o $@ -I $(PATH_INC) $(INCLUDE_DIR_SDL)

$(PATH_OBJ)%.o: $(PATH_SRC2)%.cpp
	@echo $(CC) $(CFLAGS) -c $< -o $@ -I $(PATH_INC) $(INCLUDE_DIR_SDL)
	@$(CC) $(CFLAGS) -std=c++11 -c $< -o $@ -I $(PATH_INC) $(INCLUDE_DIR_SDL)

$(PATH_OBJ)%.o: $(PATH_SRC)%.cpp $(INC_IMG)
	@echo $(CC) $(CFLAGS) -c $< -o $@ -I $(PATH_INC) $(INCLUDE_DIR_SDL)
	@$(CC) $(CFLAGS) -std=c++11 -c $< -o $@ -I $(PATH_INC) $(INCLUDE_DIR_SDL)

#******************************************************************************#
#                                   OTHER                                      #
#******************************************************************************#

clean:
	@echo "\n\033[1mCLEAN of .o \n"
	@rm -f  obj/*.o
	@rm -f  bin/exemple
	@rm -f  bin/test
	@rm -f  bin/serveur
	@rm -f  bin/sdl

re: clean all

exe: all

exec: exe clean
