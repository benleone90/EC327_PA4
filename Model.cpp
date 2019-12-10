#include "Model.h"
#include "GameObject.h"
#include "Pokemon.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "BattleArena.h"
#include "View.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <list>

Model::Model()
{
    time = 0;
    //Pokemon 1
    Pokemon *p1 = new Pokemon("Pikachu", 2.0, 20, 5, 4, 15, 1, 'P', Point2D(5, 1));
    pokemon_ptrs.push_back(p1);
    object_ptrs.push_back(p1);
    active_ptrs.push_back(p1);
    //Pokemon 2
    Pokemon *p2 = new Pokemon("Bulbasaur", 1.0, 20, 5, 4, 15, 2, 'P', Point2D(10, 1));
    pokemon_ptrs.push_back(p2);
    object_ptrs.push_back(p2);
    active_ptrs.push_back(p2);
    //PokemonCenter 1
    PokemonCenter *c1 = new PokemonCenter(1, 1, 100, Point2D(1, 20));
    center_ptrs.push_back(c1);
    object_ptrs.push_back(c1);
    //PokemonCenter 2
    PokemonCenter *c2 = new PokemonCenter(2, 2, 200, Point2D(10, 20));
    center_ptrs.push_back(c2);
    object_ptrs.push_back(c2);
    //PokemonGym 1
    PokemonGym *g1 = new PokemonGym(10, 1, 2, 3, 1, Point2D(0, 0));
    gym_ptrs.push_back(g1);
    object_ptrs.push_back(g1);
    //PokemonGym 2
    PokemonGym *g2 = new PokemonGym(20, 5, 7.5, 8, 2, Point2D(5, 5));
    gym_ptrs.push_back(g2);
    object_ptrs.push_back(g2);
    //Rival 1
    Rival *r1 = new Rival("Charizard", 8, 20, 5, 4, 15, 1, Point2D(15, 12));
    rival_ptrs.push_back(r1);
    object_ptrs.push_back(r1);
    active_ptrs.push_back(r1);
    //Rival 2
    Rival *r2 = new Rival("Mewtwo", 10, 40, 10, 12, 15, 2, Point2D(15, 12));
    rival_ptrs.push_back(r2);
    object_ptrs.push_back(r2);
    active_ptrs.push_back(r2);
    //Rival 3
    Rival *r3 = new Rival("Articuno", 12, 41, 20, 15, 13, 3, Point2D(15, 12));
    rival_ptrs.push_back(r3);
    object_ptrs.push_back(r3);
    active_ptrs.push_back(r3);

    cout << "Model default constructed. " << endl;
}

Model::~Model()
{
    for (auto iter = object_ptrs.begin(); iter != object_ptrs.end(); iter++)
    {
        delete *iter;
    }
    cout << "Model destructed" << endl;
}

Pokemon *Model::GetPokemonPtr(int id)
{
    return 0;
}

PokemonCenter *Model::GetPokemonCenterPtr(int id)
{
    return 0;
}

PokemonGym *Model::GetPokemonGymPtr(int id)
{
    return 0;
}

Rival *Model::GetRivalPtr(int id)
{
    return 0;
}

BattleArena *Model::GetBattleArenaPtr(int id)
{
    return 0;
}

bool Model::Update()
{
    time++;
    bool updated = false;
    for (auto iter = object_ptrs.begin(); iter != object_ptrs.end(); ++iter)
    {
        GameObject *obj = *iter;
        if (obj->Update())
        {
            updated = true;
        }
    }
    int gyms_beaten = 0;
    for (auto iter = gym_ptrs.begin(); iter != gym_ptrs.end(); ++iter)
    {
        PokemonGym *gym = *iter;
        if (gym->IsBeaten() == true)
        {
            gyms_beaten++;
            if (gyms_beaten == gym_ptrs.size())
            {
                std::cout << "GAME OVER: You win! All Pokemon Gyms beaten!\n";
                std::exit(EXIT_SUCCESS);
            }
        }
    }
    int arenas_beaten = 0;
    for (auto iter = arena_ptrs.begin(); iter != arena_ptrs.end(); ++iter)
    {
        BattleArena *arena = *iter;
        if (arena->IsBeaten() == true)
        {
            arenas_beaten++;
            if (arenas_beaten == arena_ptrs.size())
            {
                std::cout << "GAME OVER: You win! All Battle Arenas beaten!\n";
                std::exit(EXIT_SUCCESS);
            }
        }
    }
    int tired_pokemon = 0;
    for (auto iter = pokemon_ptrs.begin(); iter != pokemon_ptrs.end(); ++iter)
    {
        Pokemon *pokemon = *iter;
        if (pokemon->IsExhausted() == true)
        {
            tired_pokemon++;
            if (tired_pokemon == pokemon_ptrs.size())
            {
                std::cout << "GAME OVER: You lose! All of your Pokemon are tired!\n";
                std::exit(EXIT_SUCCESS);
            }
        }
    }
    int fainted_pokemon = 0;
    for (auto iter = pokemon_ptrs.begin(); iter != pokemon_ptrs.end(); ++iter)
    {
        Pokemon *pokemon = *iter;
        if (pokemon->IsAlive() == false)
        {
            active_ptrs.remove(pokemon);
            fainted_pokemon++;
            if (fainted_pokemon == pokemon_ptrs.size())
            {
                std::cout << "GAME OVER: You lose! All of your Pokemon fainted!\n";
                std::exit(EXIT_SUCCESS);
            }
        }
    }
    for (auto iter = rival_ptrs.begin(); iter != rival_ptrs.end(); ++iter)
    {
        Rival *rival = *iter;
        if (rival->IsAlive() == false)
        {
            active_ptrs.remove(rival);
        }
    }
    return updated;
}
void Model::Display(View &view)
{
    view.Clear();
    for (auto iter = object_ptrs.begin(); iter != object_ptrs.end(); ++iter)
    {
        GameObject *obj = *iter;
        view.Plot(obj);
    }
    view.Draw();
}

void Model::ShowStatus()
{
    std::cout << "Time: " << time << '\n';
    for (auto iter = object_ptrs.begin(); iter != object_ptrs.end(); ++iter)
    {
        GameObject *obj = *iter;
        obj->ShowStatus();
    }
}