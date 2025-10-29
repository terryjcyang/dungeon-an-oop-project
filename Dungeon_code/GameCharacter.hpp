#ifndef GAMECHARACTER_HPP_INCLUDED
#define GAMECHARACTER_HPP_INCLUDED

#include <iostream>
#include <string>
#include <cassert>
#include "Object.hpp"
#include "Item.hpp"

using namespace std;

class Item;

class GameCharacter: public Object
{
private:
    int maxHealth;
    int currentHealth;
    int attack;
    int defense;
protected:
    vector<Item*> items;
public:
    GameCharacter();
    GameCharacter(string,string,int,int,int,vector<Item*>);
    GameCharacter(string,string,int,int,int);
    bool checkIsDead();
    int takeDamage(int);
    
    void listItems();
    void addItem(Item*);
    
    /* Set & Get function*/
    void setMaxHealth(int);
    void setCurrentHealth(int);
    void setAttack(int);
    void setDefense(int);
    void setItems(vector<Item*>);
    int getMaxHealth();
    int getCurrentHealth();
    int getAttack();
    int getDefense();
    vector<Item*> getItems();
};
#endif // GAMECHARACTER_HPP_INCLUDED
