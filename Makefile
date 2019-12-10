CC=g++ -g -std=c++11

OBJS=main.o Building.o Point2D.o Vector2D.o GameObject.o GameCommand.o PokemonCenter.o Pokemon.o PokemonGym.o Rival.o BattleArena.o Model.o View.o

default: PA4

PA4: $(OBJS)
	$(CC) -o PA4.exe $(OBJS) 

Vector2D.o: Vector2D.cpp Vector2D.h
	$(CC) -c Vector2D.cpp -o Vector2D.o 
	
Point2D.o: Point2D.cpp Point2D.h
	$(CC) -c Point2D.cpp -o Point2D.o 

Building.o: Building.cpp Building.h
	$(CC) -c Building.cpp -o Building.o

GameObject.o: GameObject.cpp GameObject.h
	$(CC) -c GameObject.cpp -o GameObject.o 

PokemonCenter.o: PokemonCenter.cpp PokemonCenter.h
	$(CC) -c PokemonCenter.cpp -o PokemonCenter.o

Model.o: Model.cpp Model.h
	$(CC) -c Model.cpp -o Model.o 

PokemonGym.o: PokemonGym.cpp PokemonGym.h
	$(CC) -c PokemonGym.cpp -o PokemonGym.o

View.o: View.cpp View.h
	$(CC) -c View.cpp -o View.o 

Pokemon.o: Pokemon.cpp Pokemon.h
	$(CC) -c Pokemon.cpp -o Pokemon.o

Rival.o: Rival.cpp Rival.h
	$(CC) -c Rival.cpp -o Rival.o

BattleArena.o: BattleArena.cpp BattleArena.h
	$(CC) -c BattleArena.cpp -o BattleArena.o

GameCommand.o: GameCommand.cpp GameCommand.h Input_Handling.h
	$(CC) -c GameCommand.cpp -o GameCommand.o

main.o: main.cpp Building.h Point2D.h Vector2D.h GameCommand.h PokemonCenter.h Model.h Pokemon.h PokemonGym.h GameObject.h View.h Rival.h BattleArena.h Input_Handling.h
	$(CC) -c main.cpp

clean: 
	rm $(OBJS) PA4.exe