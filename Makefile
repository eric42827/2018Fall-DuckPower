CC = g++
OBJ = main.o BATTLE_SCENE.o BATTLE_SCENE_MULTI.o BATTLE_SETTING.o Change_scene.o define.o initial.o mainmap.o Map.o MULTI_PLAYER.o TUTORIAL.o GO_JUDGER.o BUTTON.o BUTTON_ARRANGE.o BUTTON_ARRANGE_CHA.o BUTTON_ARRANGE_LOOP.o music.o BUTTON_BATTLE.o men_with_arms.o LTexture.o base.o LButton.o

LIB = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
CFLAGS  = -Iinclude
SDL_FLAG = -I/usr/include/SDL2
VPATH = src:include


duckpower:$(OBJ)
	$(CC) $(OBJ) -o duckpower $(LIB)
	rm -f $(OBJ)

test.o:test.cpp BATTLE_SCENE.h
	$(CC) $(CFLAGS) $(SDL_FLAG) -c $< 

main.o:main.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG) -c $< 

BATTLE_SCENE.o:BATTLE_SCENE.cpp 
	$(CC) $(CFLAGS) $(SDL_FLAG) -c $<
BATTLE_SCENE_MULTI.o:BATTLE_SCENE_MULTI.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG) -c $<
BATTLE_SETTING.o:BATTLE_SETTING.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG) -c $<
Change_scene.o:Change_scene.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG) -c $<
define.o:define.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG) -c $<
initial.o:initial.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG) -c $<
mainmap.o:mainmap.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG) -c $<
Map.o:Map.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG) -c $<
MULTI_PLAYER.o:MULTI_PLAYER.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG) -c $<
TUTORIAL.o:TUTORIAL.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG) -c $<

GO_JUDGER.o:GO_JUDGER.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG) -c $<

BUTTON.o: BUTTON.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG) -c $<
BUTTON_BATTLE.o:BUTTON_BATTLE.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG) -c $<
BUTTON_ARRANGE.o:BUTTON_ARRANGE.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG) -c $<
BUTTON_ARRANGE_CHA.o:BUTTON_ARRANGE_CHA.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG) -c $<
BUTTON_ARRANGE_LOOP.o:BUTTON_ARRANGE_LOOP.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG) -c $<

music.o:music.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG)  -c $<

men_with_arms.o: men_with_arms.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG)  -c $<

LTexture.o:LTexture.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG)  -c $< 
base.o: base.cpp
	$(CC) $(CFLAGS) $(SDL_FLAG)  -c $<
LButton.o: LButton.cpp LButton.h 
	$(CC) $(CFLAGS) $(SDL_FLAG)  -c $<

clean:
	rm -f duckpower $(OBJ)