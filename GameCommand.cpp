#include "GameCommand.h"
#include <iostream>

void DoMoveCommand(Model &model, int pokemon_id, Point2D p1)
{
    if (model.GetPokemonPtr(pokemon_id) != 0)
    {
        cout << "Moving " << model.GetPokemonPtr(pokemon_id)->GetName()
             << " to " << p1 << endl;
        model.GetPokemonPtr(pokemon_id)->StartMoving(p1);
    }
    else
        cout << "ERROR: Please enter a valid command!" << endl;
}

void DoMoveToCenterCommand(Model &model, int pokemon_id, int center_id)
{
    if (model.GetPokemonPtr(pokemon_id) != 0 && model.GetPokemonCenterPtr(center_id) != 0)
    {
        cout << "Moving " << model.GetPokemonPtr(pokemon_id)->GetName()
             << " to center " << center_id << endl;
        model.GetPokemonPtr(pokemon_id)->StartMovingToCenter(model.GetPokemonCenterPtr(center_id));
    }
    else
        cout << "ERROR: Please enter a valid command!" << endl;
}

void DoMoveToGymCommand(Model &model, int pokemon_id, int gym_id)
{
    if (model.GetPokemonPtr(pokemon_id) != 0 && model.GetPokemonGymPtr(gym_id) != 0)
    {
        cout << "Moving " << model.GetPokemonPtr(pokemon_id)->GetName()
             << " to gym " << gym_id << endl;
        model.GetPokemonPtr(pokemon_id)->StartMovingToGym(model.GetPokemonGymPtr(gym_id));
    }
    else
        cout << "ERROR: Please enter a valid command!" << endl;
}
void DoMoveToArenaCommand(Model &model, int pokemon_id, int arena_id)
{
    if (model.GetPokemonPtr(pokemon_id) != 0)
    {
        cout << "Moving " << model.GetPokemonPtr(pokemon_id)->GetName() << " to Battle Arena " << arena_id << endl;
        model.GetPokemonPtr(pokemon_id)->StartMovingToArena(model.GetBattleArenaPtr(arena_id));
    }
    else
        cout << "ERROR: Please enter a valid command!" << endl;
}

void DoStopCommand(Model &model, int pokemon_id)
{
    if (model.GetPokemonPtr(pokemon_id) != 0)
    {
        cout << "Stopping " << model.GetPokemonPtr(pokemon_id)->GetName() << endl;
        model.GetPokemonPtr(pokemon_id)->Stop();
    }
    else
        cout << "ERROR: Please enter a valid command!" << endl;
}

void DoTrainInGymCommand(Model &model, int pokemon_id, unsigned int training_units)
{
    if (model.GetPokemonPtr(pokemon_id) != 0)
    {
        cout << "Training " << model.GetPokemonPtr(pokemon_id)->GetName() << endl;
        model.GetPokemonPtr(pokemon_id)->StartTraining(training_units);
    }
    else
        cout << "ERROR: Please enter a valid command!" << endl;
}

void DoRecoverInCenterCommand(Model &model, int pokemon_id, unsigned int stamina_points)
{
    if (model.GetPokemonPtr(pokemon_id) != 0)
    {
        cout << "Recovering " << model.GetPokemonPtr(pokemon_id)->GetName() << "'s stamina" << endl;
        model.GetPokemonPtr(pokemon_id)->StartRecoveringStamina(stamina_points);
    }
    else
        cout << "ERROR: Please enter a valid command!" << endl;
}

void DoCreateNewObjects(Model &model, char type, int in_id, Point2D in_loc)
{
    if (type == 'g')
    {
        PokemonGym *g = new PokemonGym(15, 3, 5, 4, in_id, in_loc);
        if (model.GetPokemonGymPtr(in_id) == g)
        {
            cout << "A Pokemon Gym with this ID already exists" << endl;
            g->~PokemonGym();
        }
        else
        {
            model.object_ptrs.push_back(g);
            model.gym_ptrs.push_back(g);
        }
    }
    else if (type == 'c')
    {
        PokemonCenter *c = new PokemonCenter(in_id, 3, 3, in_loc);
        if (model.GetPokemonCenterPtr(in_id) == c)
        {
            cout << "A Pokemon Center with this ID already exits" << endl;
            c->~PokemonCenter();
        }
        else
        {
            model.object_ptrs.push_back(c);
            model.center_ptrs.push_back(c);
        }
    }
    else if (type == 'p')
    {
        Pokemon *p = new Pokemon("Pokemon", 2.0, 20, 5, 4, 15, 1, 'P', in_loc);
        if (model.GetPokemonPtr(in_id) == p)
        {
            cout << "A Pokemon with this ID alreay exists" << endl;
            p->~Pokemon();
        }
        else
        {
            model.object_ptrs.push_back(p);
            model.pokemon_ptrs.push_back(p);
            model.active_ptrs.push_back(p);
        }
    }
    else if (type == 'r')
    {
        Rival *r = new Rival("Rival", 10, 40, 10, 12, 15, 2, in_loc);
        if (model.GetRivalPtr(in_id) == r)
        {
            cout << "A Rival with this ID already exists" << endl;
            r->~Rival();
        }
        else
        {
            model.object_ptrs.push_back(r);
            model.rival_ptrs.push_back(r);
            model.active_ptrs.push_back(r);
        }
    }
    else
    {
        cout << "Type" << type << " does not exists" << endl;
    }
}

void DoGoCommand(Model &model, View &view)
{
    cout << "Advancing one tick." << endl;
    model.Update();
    model.ShowStatus();
    model.Display(view);
}

void DoRunCommand(Model &model, View &view)
{
    cout << "Advancing to next event." << endl;
    int count = 0;
    bool event = false;
    while (count < 5 && !event)
    {
        event = model.Update();
        count++;
    }
    model.ShowStatus();
    model.Display(view);
}
