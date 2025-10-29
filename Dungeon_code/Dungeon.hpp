#ifndef DUNGEON_HPP_INCLUDED
#define DUNGEON_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "Player.hpp"
#include "Monster.hpp"
#include "NPC.hpp"
#include "Room.hpp"

using namespace std;

class Dungeon{
private:
    Player player;
    vector<Room> rooms;
    Room* exitRoom;
    
    /* Create a new player, and give him/her basic status */
    void createPlayer();

    /* Create a map, include different rooms */
    void createMap();
    void makeRoomBesidePair(int,int,char);
    
    /* player's moveing action */
    void handleMovement();

    /* game initial setting */
    /* Including create player, create map etc  */
    void startGame();

    /* player's action including 
    showing the action list that player can do at that room
    and dealing with player's input  */
    void chooseAction(vector<Object*>);
    
    /* Check whether the game should end or not */
    /* Including player victory, or he/she dead */
    bool checkGameLogic();

    void printSmileFace();
public:
    Dungeon();

    /* the whole game process */
    void runDungeon();
};


#endif // DUNGEON_HPP_INCLUDED
