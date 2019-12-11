#include <iostream>
#include "Rival.h"

Rival::Rival() : GameObject('R')
{
    this->health = 20;
    this->defense = 15;
    this->physical_damage = 5;
    this->magical_damage = 4;
}

Rival::Rival(string name, double speed, double hp, double phys_dmg, double magic_dmg, double def, int in_id, Point2D in_loc) : GameObject(in_loc, in_id, 'R')
{
    this->health = hp;
    this->defense = def;
    this->physical_damage = phys_dmg;
    this->magical_damage = magic_dmg;
    this->name = name;
    this->speed = speed;
    this->health = hp;
    this->physical_damage = phys_dmg;
    this->magical_damage = magic_dmg;
}

Rival::~Rival()
{
    cout << "Rival destructed" << endl;
}

void Rival::TakeHit(double physical_damage, double magical_damage, double defense)
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

double Rival::get_phys_dmg()
{
    return physical_damage;
}

double Rival::get_magic_dmg()
{
    return magical_damage;
}

double Rival::get_defense()
{
    return defense;
}

double Rival::get_health()
{
    return health;
}

bool Rival::IsAlive()
{
    if (health > 0)
    {
        state = ALIVE_RIVAL;
        return true;
    }
    else
    {
        state = FAINTED_RIVAL;
        return false;
    }
}

bool Rival::Update()
{
    if (health <= 0)
    {
        state = FAINTED_RIVAL;
        return false;
    }
    else
    {
        state = ALIVE_RIVAL;
        return true;
    }
}

void Rival::ShowStatus()
{
    cout << name << " status: ";
    GameObject::ShowStatus();
    switch (state)
    {
    case ALIVE_RIVAL:
        cout << " is alive" << endl;
        break;

    case FAINTED_RIVAL:
        cout << " is fainted " << endl;
        break;

    default:
        break;
    }
    cout << "\tHealth: " << health << endl;
    cout << "\tPhysical Damage: " << physical_damage << endl;
    cout << "\tMagical Damage: " << magical_damage << endl;
    cout << "\tDefense: " << defense << endl;
}

bool Rival::ShouldBeVisible()
{
    return IsAlive();
}
