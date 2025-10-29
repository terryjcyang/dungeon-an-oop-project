#ifndef ROOM_HPP_INCLUDED
#define ROOM_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cassert>
#include "Object.hpp"

using namespace std;

class Room
{
private:
    Room *upRoom, *downRoom, *leftRoom, *rightRoom;
    bool isExit;
    int index;
    bool monsterExist;
    int hungerCost, thirstCost;
    //such as a desert, forest, or swamp
    string roomType;
    vector<Object*> objects;
public:
    Room();
    Room(string,bool,int,bool,vector<Object*>);
    bool popObject(Object*); /*pop out the specific object, used when the interaction is done*/

    int pointsStumbleReplenish();
    bool sandstorm();
    
    /* Set & Get function*/
    void setUpRoom(Room*);
    void setDownRoom(Room*);
    void setLeftRoom(Room*);
    void setRightRoom(Room*);
    void setIsExit(bool);
    void setIndex(int);
    void setMonsterExist(bool);
    void setObjects(vector<Object*>);
    bool getIsExit();
    int getIndex();
    bool getMonsterExist();
    int getHungerCost();
    int getThirstCost();
    string getRoomType();
    vector<Object*> getObjects();
    Room* getUpRoom();
    Room* getDownRoom();
    Room* getLeftRoom();
    Room* getRightRoom();
};

#endif // ROOM_HPP_INCLUDED
