#include <iostream>
#include "BattleArena.h"
using namespace std;

BattleArena::BattleArena() : Building('A', 0, Point2D(0, 0))
{
    this->state = RIVALS_AVAILABLE;
    this->pokemon_count = 0;
    this->max_num_rivals = 3;
    num_rivals_remaining = max_num_rivals;
    this->dollar_cost_per_fight = 4;
    this->stamina_cost_per_fight = 3;
    cout << "BattleArena default constructed." << endl;
};

BattleArena::BattleArena(unsigned int max_rivals, unsigned int stamina_cost, double dollar_cost, int in_id, Point2D in_loc) : Building('C', in_id, in_loc)
{
    this->state = RIVALS_AVAILABLE;
    this->pokemon_count = 0;
    this->max_num_rivals = 3;
    num_rivals_remaining = max_num_rivals;
    this->dollar_cost_per_fight = 4;
    this->stamina_cost_per_fight = 3;
    cout << "BattleArena constructed." << endl;
}

unsigned int BattleArena::GetNumRivalsRemaining()
{
    return num_rivals_remaining;
}

bool BattleArena::HasEnoughRivals()
{
    if (num_rivals_remaining >= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

double BattleArena::GetDollarCost()
{
    return dollar_cost_per_fight;
}

unsigned int GetStaminaCost()
{
    return stamina_cost_per_fight;
}

bool BattleArena::IsAbleToFight(double budget, unsigned int stamina)
{
    if ((budget >= dollar_cost_per_fight) && (stamina >= stamina_cost_per_fight))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool BattleArena::Update()
{
    if (num_rivals_remaining == 0 && state == RIVALS_AVAILABLE)
    {
        state = NO_RIVALS_AVAILABLE;
        display_code = 'r';
        cout << "Battle Arena " << GetId() << " has ran out of rivals" << endl;
        return true;
    }
    return false;
}

bool BattleArena::IsBeaten()
{
    if (num_rivals_remaining == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void BattleArena::ShowStatus()
{
    cout << "Battle Arena Status: ";
    Building::ShowStatus();
    cout << pokemon_count << " Pokemon are in this building" << endl;
    cout << "\tStamina cost per fight: " << stamina_cost_per_fight << endl;
    cout << "\tPokemon dollars per fight: " << dollar_cost_per_fight << endl;
    cout << num_rivals_remaining << " rival(s) are remaining for this arena" << endl;
}