#include "Pokemon.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>

// TODO: Pick sane default starting values
Pokemon::Pokemon() : GameObject('P')
{
    stamina = 20;
    pokemon_dollars = 0.0;
    current_center = NULL;
    current_gym = NULL;
    current_arena = NULL;
    stamina_points_to_buy = 0;
    training_units_to_buy = 0;
    speed = 1;
    health = 1;
    this->name = "Pokemon";
    is_in_gym = false;
    is_in_center = false;
    experience_points = 0;
    this->speed = 5.0;
    this->health = 20.0;
    this->store_health = health;
    this->physical_damage = 5.0;
    this->magical_damage = 4.0;
    this->defense = 15;
    cout << "Pokemon default constructed." << endl;
}

Pokemon::Pokemon(string name, double speed, double hp, double phys_dmg, double magic_dmg, double def, int in_id, char in_code, Point2D in_loc) : GameObject(in_loc, in_id, 'P')
{
    stamina = 20;
    pokemon_dollars = 0.0;
    current_center = NULL;
    current_gym = NULL;
    current_arena = NULL;
    stamina_points_to_buy = 0;
    training_units_to_buy = 0;
    this->name = name;
    this->speed = speed;
    this->health = hp;
    this->store_health = health;
    this->physical_damage = phys_dmg;
    this->magical_damage = magic_dmg;
    this->defense = def;
    is_in_gym = false;
    is_in_center = false;
    experience_points = 0;
    cout << "Pokemon constructed." << endl;
}

Pokemon::Pokemon(char in_code) : GameObject(in_code)
{
    stamina = 20;
    pokemon_dollars = 0.0;
    current_center = NULL;
    current_gym = NULL;
    current_arena = NULL;
    stamina_points_to_buy = 0;
    training_units_to_buy = 0;
    this->name = name;
    this->speed = speed;
    this->health = health;
    this->store_health = health;
    this->physical_damage = physical_damage;
    this->magical_damage = magical_damage;
    is_in_gym = false;
    is_in_center = false;
    experience_points = 0;
    cout << "Pokemon constructed." << endl;
}

Pokemon::~Pokemon()
{
    cout << "Pokemon destructed." << endl;
}

// PA4 code goes here....
bool Pokemon::IsAlive()
{
    if (state != FAINTED)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Pokemon::IsExhausted()
{
    return stamina == 0;
}

// returns true if the simulation should be stopped
bool Pokemon::Update()
{
    bool arrived = false;
    unsigned int stamina_received = 0;
    unsigned int stamina_cost = 0;
    double dollar_cost = 0;
    unsigned int num_training_units = 0;
    unsigned int experience_gain = 0;
    switch (state)
    {
    case STOPPED:
        return false;
    case MOVING:
        if (is_in_center)
        {
            current_center->RemoveOnePokemon();
            is_in_center = false;
        }
        else if (is_in_gym)
        {
            current_gym->RemoveOnePokemon();
            is_in_gym = false;
        }
        if (stamina == 0)
        {
            cout << name << " is out of stamina and can't move." << endl;
            state = EXHAUSTED;
            return true;
        }
        else
        {
            arrived = UpdateLocation();
            if (arrived)
            {
                state = STOPPED;
                return true;
            }
            else
            {
                pokemon_dollars += GetRandomAmountOfPokemonDollars();
                stamina -= 1;
                return false;
            }
        }
    case MOVING_TO_GYM:
        if (is_in_center)
        {
            current_center->RemoveOnePokemon();
            is_in_center = false;
        }
        else if (is_in_gym)
        {
            current_gym->RemoveOnePokemon();
            is_in_gym = false;
        }
        if (stamina == 0)
        {
            cout << name << " is out of stamina and can't move." << endl;
            state = EXHAUSTED;
            return true;
        }
        else
        {
            arrived = UpdateLocation();
            if (arrived)
            {
                state = IN_GYM;
                is_in_gym = true;
                current_gym->AddOnePokemon();
                return true;
            }
            else
            {
                pokemon_dollars += GetRandomAmountOfPokemonDollars();
                stamina -= 1;
                return false;
            }
        }
    case MOVING_TO_CENTER:
        if (is_in_center)
        {
            current_center->RemoveOnePokemon();
            is_in_center = false;
        }
        else if (is_in_gym)
        {
            current_gym->RemoveOnePokemon();
            is_in_gym = false;
        }
        if (stamina == 0)
        {
            cout << name << " is out of stamina and can't move." << endl;
            state = EXHAUSTED;
            return true;
        }
        else
        {
            arrived = UpdateLocation();
            if (arrived)
            {
                state = IN_CENTER;
                is_in_center = true;
                current_center->AddOnePokemon();
                return true;
            }
            else
            {
                pokemon_dollars += GetRandomAmountOfPokemonDollars();
                stamina -= 1;
                return false;
            }
        }
    case MOVING_TO_ARENA:
        if (is_in_center)
        {
            current_center->RemoveOnePokemon();
            is_in_arena = false;
        }
        else if (is_in_gym)
        {
            current_gym->RemoveOnePokemon();
            is_in_gym = false;
        }
        if (stamina == 0)
        {
            cout << name << " is out of stamina and can't move." << endl;
            state = EXHAUSTED;
            return true;
        }
        else
        {
            arrived = UpdateLocation();
            if (arrived)
            {
                state = IN_ARENA;
                is_in_arena = true;
                current_gym->AddOnePokemon();
                return true;
            }
            else
            {
                pokemon_dollars += GetRandomAmountOfPokemonDollars();
                stamina -= 1;
                return false;
            }
        }
    case RECOVERING_STAMINA:
        dollar_cost = current_center->GetDollarCost(stamina_points_to_buy);
        pokemon_dollars -= dollar_cost;
        stamina += current_center->DistributeStamina(stamina_points_to_buy);
        cout << "** " << name << " recovered " << stamina_points_to_buy << " stamina point(s)! **" << endl;
        stamina_points_to_buy = 0;
        state = IN_CENTER;
        return true;
    case TRAINING_IN_GYM:
        stamina_cost = current_gym->GetStaminaCost(training_units_to_buy);
        dollar_cost = current_gym->GetDollarCost(training_units_to_buy);
        experience_gain = current_gym->TrainPokemon(training_units_to_buy);
        stamina -= stamina_cost;
        pokemon_dollars -= dollar_cost;
        experience_points += experience_gain;
        cout << "** " << name << " completed " << training_units_to_buy << " training unit(s)! **" << endl;
        cout << "** " << name << " gained " << experience_gain << " experience points! **" << endl;
        training_units_to_buy = 0;
        state = IN_GYM;
        return true;
    case BATTLE:
        ReadyBattle(target);
        stamina_cost = current_arena->GetStaminaCost();
        dollar_cost = current_arena->GetDollarCost();
        stamina_cost -= stamina_cost;
        pokemon_dollars -= dollar_cost;
        if (StartBattle())
        {
            this->health = 20;
            this->state = IN_ARENA;
            target->IsAlive();
        }
        else
        {
            this->state = FAINTED;
            target->IsAlive();
        }
        

    case EXHAUSTED:
    case IN_GYM:
    case IN_CENTER:
    case FAINTED:
    default:
        return false;
    }
}

void Pokemon::StartMovingToCenter(PokemonCenter *center)
{
    if (!IsExhausted())
    {
        if (location == center->GetLocation())
        {
            cout << display_code << GetId() << ": I am already at the Pokemon Center!" << endl;
        }
        else
        {
            if (is_in_center)
            {
                current_center->RemoveOnePokemon(); // handles corner case
                is_in_center = false;
            }
            else if (is_in_gym)
            {
                current_gym->RemoveOnePokemon();
                is_in_gym = false;
            }
            state = MOVING_TO_CENTER;
            current_center = center;
            SetupDestination(center->GetLocation());
            cout << display_code << GetId() << ": On my way to center " << center->GetId() << endl;
        }
    }
    else
        cout << display_code << GetId() << ": I am exhausted so I can't move to recover stamina..." << endl;
}

void Pokemon::StartMovingToGym(PokemonGym *gym)
{
    if (!IsExhausted())
    {
        if (location == gym->GetLocation())
        {
            cout << display_code << GetId() << ": I am already at the Pokemon Gym!" << endl;
        }
        else
        {
            if (is_in_gym)
            {
                current_gym->RemoveOnePokemon(); // handles corner case
                is_in_gym = false;
            }
            else if (is_in_center)
            {
                current_center->RemoveOnePokemon();
                is_in_center = false;
            }
            state = MOVING_TO_GYM;
            current_gym = gym;
            SetupDestination(gym->GetLocation());
            cout << display_code << GetId() << ": On my way to gym " << gym->GetId() << endl;
        }
    }
    else
        cout << display_code << GetId() << ": I am exhausted so I shouldn't be going to the gym.." << endl;
}

void Pokemon::StartTraining(unsigned int num_training_units)
{
    unsigned int training_units_in_gym = 0;
    if (!IsExhausted())
    {
        if (state == IN_GYM || state == TRAINING_IN_GYM)
        {
            if (current_gym->IsAbleToTrain(num_training_units,
                                           pokemon_dollars, stamina))
            {
                if (!current_gym->IsBeaten())
                {
                    training_units_in_gym = current_gym->GetNumTrainingUnitsRemaining();
                    training_units_to_buy = min(num_training_units, training_units_in_gym);
                    state = TRAINING_IN_GYM;
                    cout << display_code << GetId() << ": Started " << training_units_to_buy
                         << " training unit(s) at Pokemon Gym " << current_gym->GetId() << endl;
                }
                else
                    cout << display_code << GetId() << ": Cannot train! This Pokemon Gym is already beaten!"
                         << current_gym->GetId() << endl;
            }
            else
                cout << display_code << GetId() << ": Not enough stamina and/or money for training" << endl;
        }
        else
            cout << display_code << GetId() << ": I can only train in a Pokemon Gym!" << endl;
    }
    else
        cout << display_code << GetId() << ": I am exhausted so no more training for me.." << endl;
}

void Pokemon::StartRecoveringStamina(unsigned int num_stamina_points)
{
    unsigned int stamina_count_in_center = 0;
    if (state == IN_CENTER || state == RECOVERING_STAMINA)
    {
        if (IsExhausted())
            cout << display_code << GetId() << ": I barely made it to the Pokemon center!" << endl;
        if (current_center->CanAffordStaminaPoints(num_stamina_points, pokemon_dollars))
        {
            if (current_center->HasStaminaPoints())
            {
                stamina_count_in_center = current_center->GetNumStaminaPointsRemaining();
                state = RECOVERING_STAMINA;
                stamina_points_to_buy = min(num_stamina_points, stamina_count_in_center);
                cout << display_code << GetId() << ": Started recovering " << stamina_points_to_buy
                     << " stamina point(s) at Pokemon Center " << current_center->GetId() << endl;
            }
            else
                cout << display_code << GetId()
                     << ": Cannot recover! No stamina points available in this Pokemon Center "
                     << current_center->GetId() << endl;
        }
        else
            cout << display_code << GetId() << ": Not enough money to recover stamina." << endl;
    }
    else
        cout << display_code << GetId() << ": I can only recover stamina at a Pokemon Center!" << endl;
}

void Pokemon::StartMoving(Point2D dest)
{
    if (!IsExhausted())
    {
        if (dest == this->GetLocation())
        {
            cout << display_code << GetId() << ": I'm already there. see?" << endl;
        }
        else
        {
            state = MOVING;
            SetupDestination(dest);
            cout << display_code << GetId() << ": On my way." << endl;
        }
    }
    else
    {
        cout << display_code << GetId() << ": I am exhausted. I may move but you just cannot see me. " << endl;
    }
}

void Pokemon::ReadyBattle(Rival *in_target)
{
    if (state == IN_ARENA)
    {
        if (current_arena->IsAbleToFight(pokemon_dollars, stamina))
        {
            if (!current_arena->IsBeaten())
            {
                if (in_target->IsAlive())
                {
                    state = BATTLE;
                    target = in_target;
                }
                else
                {
                    state = IN_ARENA;
                }
            }
            else
            {
                state = IN_ARENA;
            }
        }
        else
        {
            state = IN_ARENA;
        }
    }
    else
    {
        state = IN_ARENA;
    }
}

bool Pokemon::StartBattle()
{
    while (health > 0.0 || target->get_health() > 0.0)
    {
        TakeHit(target->get_phys_dmg(), target->get_magic_dmg(), defense);
        target->TakeHit(physical_damage, magical_damage, target->get_defense());
    }
    if (health <= 0)
    {
        return false; // Lost to rival
    }
    else
    {
        return true; // Beat the rival
    }
}

void Pokemon::SetupDestination(Point2D dest)
{
    destination = dest;
    delta = (destination - location) * (speed / GetDistanceBetween(destination, location));
}

void Pokemon::Stop()
{
    state = STOPPED;
    cout << display_code << GetId() << ": Stopping.." << endl;
}

bool Pokemon::UpdateLocation()
{
    //check if within one step
    if (fabs((destination - location).x) <= fabs(delta.x) &&
        fabs((destination - location).y) <= fabs(delta.y))
    {
        location = destination;
        cout << display_code << GetId() << ": I’m there!" << endl;
        return true;
    }
    else
    {
        location = location + delta;
        cout << display_code << GetId() << ": step..." << endl;
        return false;
    }
}

string Pokemon::GetName()
{
    return name;
}

double GetRandomAmountOfPokemonDollars()
{
    double f_min = 0.0;
    double f_max = 2.0;
    double f = (double)rand() / RAND_MAX;
    return f_min + f * (f_max - f_min);
}

void Pokemon::TakeHit(double physical_damage, double magical_damage, double defense)
{
    int attack_type = rand() % 2;
    if (attack_type == 0) // 0 is physical damage
    {
        double damage = (100.0 - defense) / (100 * physical_damage);
        health = health - damage;
    }
    else if (attack_type == 1) // 1 is magical damage
    {
        double damage = (100.0 - defense) / (100 * magical_damage);
        health = health - damage;
    }
}

void Pokemon::ShowStatus()
{
    cout << name << " status: ";
    GameObject::ShowStatus();
    switch (state)
    {
    case STOPPED:
        cout << " stopped" << endl;
        break;
    case MOVING:
        cout << " moving at a speed of " << speed
             << " to " << destination << " at each step of " << delta << endl;
        break;
    case MOVING_TO_CENTER:
        cout << " heading to Pokemon Center " << current_center->GetId()
             << " at a speed of " << speed << " at each step of " << delta << endl;
        break;
    case MOVING_TO_GYM:
        cout << " heading to Pokemon Gym " << current_gym->GetId()
             << " at a speed of " << speed << " at each step of " << delta << endl;
        break;
    case IN_GYM:
        cout << " inside Pokemon Gym " << current_gym->GetId() << endl;
        break;
    case IN_CENTER:
        cout << " inside Pokemon Center " << current_center->GetId() << endl;
        break;
    case TRAINING_IN_GYM:
        cout << " training in Pokemon Gym " << current_gym->GetId() << endl;
    case RECOVERING_STAMINA:
        cout << " recovering stamina in Pokemon Center " << current_gym->GetId() << endl;
        break;
    case EXHAUSTED:
        cout << endl;
    default:
        break;
    }
    //  Print stats here
    cout << "\tStamina: " << stamina << endl;
    cout << "\tPokemon Dollars: " << pokemon_dollars << endl;
    cout << "\tExperience Points: " << experience_points << endl;
}

bool Pokemon::ShouldBeVisible()
{
    return !IsExhausted();
}
