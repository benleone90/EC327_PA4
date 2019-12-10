#ifndef MODEL_H
#define MODEL_H
#include "GameObject.h"
#include "Pokemon.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Rival.h"
#include "View.h"

class Model
{

public:
    //simulation time
    int time;
    //PA4 Linked Lists
    list<GameObject *> object_ptrs;
    list<GameObject *> active_ptrs;
    list<Pokemon *> pokemon_ptrs;
    list<Rival *> rival_ptrs;
    list<PokemonGym *> gym_ptrs;
    list<PokemonCenter *> center_ptrs;

public:
    Model();
    ~Model();
    Pokemon *GetPokemonPtr(int id);
    PokemonCenter *GetPokemonCenterPtr(int id);
    PokemonGym *GetPokemonGymPtr(int id);
    bool Update();
    void Display(View &view);
    void ShowStatus();
};

#endif
