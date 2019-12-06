#include <iostream>
#include <BattleArena.h>

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

using namespace std;