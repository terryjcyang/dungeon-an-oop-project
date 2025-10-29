#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "GameCharacter.hpp"
#include "Room.hpp"

using namespace std;

class Item;
class GameCharacter;

class Player: public GameCharacter
{
private:
    Room *currentRoom, *previousRoom;
    int hunger, thirst, poison;
    int poisonTime;
public:
    Player();
    Player(string,int,int,int);
    void increaseStates(int,int,int,int,int,int);
    void changeRoom(Room*);

    /* Virtual function that you need to complete   */
    /* In Player, this function should show the     */
    /* status of player.                            */
    bool triggerEvent(Object*);
    bool openBackpack();
    
    void hungerThirstConsumption();
    
    /* Set & Get function*/
    void setCurrentRoom(Room*);
    void setPreviousRoom(Room*);
    void setHunger(int);
    void setThirst(int);
    void setPoison(int);
    void setPoisonTime(int);
    Room* getCurrentRoom();
    Room* getPreviousRoom();
    int getHunger();
    int getThirst();
    int getPoison();
    int getPoisonTime();
};

#endif // PLAYER_HPP_INCLUDED
