#ifndef POKEMON_H
#define POKEMON_H
#include "GameObject.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "PokemonGym.h"
#include "PokemonCenter.h"
#include "BattleArena.h"
#include "Rival.h"
#include <string>

enum PokemonStates
{
    STOPPED = 0,
    MOVING = 1,
    EXHAUSTED = 2,
    IN_GYM = 3,
    IN_CENTER = 4,
    MOVING_TO_GYM = 5,
    MOVING_TO_CENTER = 6,
    TRAINING_IN_GYM = 7,
    RECOVERING_STAMINA = 8,
    IN_ARENA = 9,
    MOVING_TO_ARENA = 10,
    BATTLE = 11,
    FAINTED = 12
};

class Pokemon : public GameObject
{
public:
    Pokemon();
    Pokemon(char in_code);
    Pokemon(string name, double speed, double hp, double phys_dmg, double magic_dmg, double def, int id, char in_code, Point2D in_loc);
    ~Pokemon();
    void StartMoving(Point2D dest);
    void StartMovingToCenter(PokemonCenter *center);
    void StartMovingToGym(PokemonGym *gym);
    void StartMovingToArena(BattleArena *arena);
    void StartTraining(unsigned int num_training_units);
    void StartRecoveringStamina(unsigned int num_stamina_points);
    void TakeHit(double physical_damage, double magical_damage, double defense);
    void ReadyBattle(Rival *in_target);
    void Stop();
    void ShowStatus();
    bool Update();
    string GetName();
    bool IsExhausted();
    bool ShouldBeVisible();
    bool IsAlive();
    bool StartBattle();

protected:
    bool UpdateLocation();
    void SetupDestination(Point2D dest);

private:
    double speed;
    Vector2D delta;
    Point2D destination;

protected:
    double pokemon_dollars;
    unsigned int experience_points;
    bool is_in_gym;
    bool is_in_center;
    bool is_in_arena;
    unsigned int stamina;
    unsigned int training_units_to_buy;
    unsigned int stamina_points_to_buy;
    double health;
    double store_health;
    double physical_damage;
    double magical_damage;
    double defense;
    Rival *target;
    PokemonCenter *current_center;
    PokemonGym *current_gym;
    BattleArena *current_arena;
    string name;
};
double GetRandomAmountOfPokemonDollars();
#endif
