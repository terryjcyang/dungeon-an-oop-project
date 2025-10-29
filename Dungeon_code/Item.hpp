#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.hpp"
//#include "Player.hpp"

using namespace std;

class Item: public Object
{
private:
    int health, attack, defense;
    int hunger, thirst, poison;
    vector<Item*> inside;
public:
    Item();
    Item(string,string,int,int,int,int,int,int);

    /* Virtual function that you need to complete    */
    /* In Item, this function should deal with the   */
    /* pick up action. You should add status to the  */
    /* player.                                       */
    bool triggerEvent(Object*);

    void printItem();
    
    /* Set & Get function*/
    int getHealth();
    int getAttack();
    int getDefense();
    int getHunger();
    int getThirst();
    int getPoison();
    vector<Item*> getInside();
    void setHealth(int);
    void setAttack(int);
    void setDefense(int);
    void setHunger(int);
    void setThirst(int);
    void setPoison(int);
    void setInside(vector<Item*>);
};

#endif // ITEM_HPP_INCLUDED
