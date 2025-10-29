#ifndef ENEMY_HPP_INCLUDED
#define ENEMY_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cassert>
#include "GameCharacter.hpp"
#include "Player.hpp"

using namespace std;

class Monster: public GameCharacter
{
private:
    int poison, poisonTime;
public:
    Monster();
    Monster(string,int,int,int,int,int,vector<Item*>,string);
    Monster(string,int,int,int,int,int,vector<Item*>);
    Monster(string,int,int,int,int,int);

    /* Virtual function that you need to complete   */
    /* In Monster, this function should deal with   */
    /* the combat system.                           */
    bool triggerEvent(Object*);
    
    void getFromAnimal(Object*);
    
    /* Set & Get function*/
    void setPoison(int);
    void setPoisonTime(int);
    int getPoison();
    int getPoisonTime();
};


#endif // ENEMY_HPP_INCLUDED
