#ifndef RIVAL_H
#define RIVAL_H
#include "GameObject.h"
#include "BattleArena.h"
#include <string>

enum RivalStates
{
    ALIVE_RIVAL = 0,
    FAINTED_RIVAL = 1
};

class Rival : public GameObject
{
public:
    Rival();
    Rival(string name, double speed, double hp, double phys_dmg, double magic_dmg, double def, int id, Point2D in_loc);
    ~Rival();
    void TakeHit(double physical_damage, double magical_damage, double defense);
    double get_phys_dmg();
    double get_magic_dmg();
    double get_defense();
    double get_health();
    bool Update();
    void ShowStatus();
    bool IsAlive();
    bool ShouldBeVisible();

protected:
    string name;
    double speed;
    double health;
    double physical_damage;
    double magical_damage;
    double defense;
    double stamina_cost_per_fight;
    bool is_in_arena;
    BattleArena *current_arena;
};

#endif //RIVAL_H