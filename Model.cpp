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
    //PokemonGym1
    //PokemonGym2
    //Rival1
    //Rival2


    cout << "Model default constructed. " << endl;
}

Model::~Model()
{
    for (int i = 0; i < num_objects; i++)
    {
        delete object_ptrs[i];
    }
    cout << "Model destructed. " << endl;
}

Pokemon *Model::GetPokemonPtr(int id)
{
    for (int i = 0; i < num_pokemon; i++)
    {
        if (id == pokemon_ptrs[i]->GetId())
        {
            return pokemon_ptrs[i];
        }
    }
    return 0;
}

PokemonCenter *Model::GetPokemonCenterPtr(int id)
{
    for (int i = 0; i < num_centers; i++)
    {
        if (id == center_ptrs[i]->GetId())
        {
            return center_ptrs[i];
        }
    }
    return 0;
}

PokemonGym *Model::GetPokemonGymPtr(int id)
{
    for (int i = 0; i < num_gyms; i++)
    {
        if (id == gym_ptrs[i]->GetId())
        {
            return gym_ptrs[i];
        }
    }
    return 0;
}

bool Model::Update()
{
    time++;
    int gyms_beaten = 0;
    int pokemon_exhausted = 0;
    //Calculating number of gyms beaten
    if (gyms_beaten != num_gyms)
    {
        for (int i = 0; i < num_gyms; i++)
        {
            if (gym_ptrs[i]->GetState() == BEATEN)
                gyms_beaten++;
        }
    }
    // Calculating number of pokemon that are tired
    if (pokemon_exhausted != num_pokemon)
    {
        for (int i = 0; i < num_pokemon; i++)
        {
            if (pokemon_ptrs[i]->IsExhausted())
                pokemon_exhausted++;
        }
    }
    bool event = false;
    // continue to update all
    if (gyms_beaten == num_gyms)
    {
        cout << "GAME OVER: You win! All Pokemon Gyms beaten!" << endl;
        exit(EXIT_SUCCESS);
    }
    if (pokemon_exhausted == num_pokemon)
    {
        cout << "GAME OVER: You lose! All of your Pokemon are exhausted!" << endl;
        exit(EXIT_SUCCESS);
    }
    // update if winning condition is not met
    for (int i = 0; i < num_objects; i++)
    {
        bool temp = object_ptrs[i]->Update();
        if (temp)
        {
            event = temp;
        }
    }
    return event;
}

void Model::Display(View &view)
{
    view.Clear();
    for (int i = 0; i < num_objects; i++)
    {
        if (object_ptrs[i]->ShouldBeVisible())
        {
            view.Plot(object_ptrs[i]);
        }
    }
    view.Draw();
}

void Model::ShowStatus()
{
    cout << "Time: " << time << endl;
    for (int i = 0; i < num_objects; i++)
    {
        object_ptrs[i]->ShowStatus();
    }
}
