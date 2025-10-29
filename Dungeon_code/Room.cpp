#include "Room.hpp"
#define HUNGER_COST_NORMAL -5
#define HUNGER_COST_DESERT -10
#define HUNGER_COST_FOREST -20  //highest hunger
#define HUNGER_COST_SWAMP -7
#define THIRST_COST_NORMAL -10
#define THIRST_COST_DESERT -25  //highest thirst
#define THIRST_COST_FOREST -5
#define THIRST_COST_SWAMP -13
#define PROBABILITY_PRECENT_OF_STUMBLE_AND_REPLENISH 10
#define POINTS_PLACE_REPLENISH 200
#define PROBABILITY_PRECENT_OF_SANDSTORM 30

Room::Room(){
    
}
Room::Room(string roomType, bool isExit, int index, bool monsterExist, vector<Object*> objects):
roomType(roomType), isExit(isExit), index(index), monsterExist(monsterExist), objects(objects),
hungerCost(HUNGER_COST_NORMAL), thirstCost(THIRST_COST_NORMAL),
upRoom(nullptr), downRoom(nullptr), leftRoom(nullptr), rightRoom(nullptr){
    if(roomType == "desert"){
        hungerCost = HUNGER_COST_DESERT;
        thirstCost = THIRST_COST_DESERT;
    }
    else if(roomType == "forest"){
        hungerCost = HUNGER_COST_FOREST;
        thirstCost = THIRST_COST_FOREST;
    }
    else if(roomType == "swamp"){
        hungerCost = HUNGER_COST_SWAMP;
        thirstCost = THIRST_COST_SWAMP;
    }
}

bool Room::popObject(Object* object){
    int size = static_cast<int>(objects.size());
    bool success = false;
    for(int i=0;i<size;i++){
        if(objects.at(i) == object){
            objects.erase(objects.begin()+i);
            success = true;
            break;
        }
    }
    return success;
} /*pop out the specific object, used when the interaction is done*/

int Room::pointsStumbleReplenish(){
    if(roomType != "desert" && roomType != "forest" && roomType != "swamp"){
        return 0;
    }
    
    srand(static_cast<unsigned>(time(0)));
    if(rand() % 101 <= PROBABILITY_PRECENT_OF_STUMBLE_AND_REPLENISH){
        cout << "You occasionally stumble upon a";
        if(roomType == "desert"){
            cout << "n oasis." << endl << endl;
        }
        else if(roomType == "forest"){
            cout << " lake." << endl << endl;
        }
        else if(roomType == "swamp"){
            cout << " lotus leaf." << endl << endl;
        }
        cout << "Thirst points replenishes " << POINTS_PLACE_REPLENISH << " points!" << endl << endl;
        return POINTS_PLACE_REPLENISH;
    }else{
        return 0;
    }
}

bool Room::sandstorm(){
    static int sandstormTime = 0;
    static bool inSandstorm = false;
    if(roomType != "desert"){
        if(inSandstorm){
            inSandstorm = false;
            hungerCost/= 1.5;
            thirstCost/= 1.5;
        }
        sandstormTime = 0;
        return false;
    }
    if(sandstormTime > 0){
        sandstormTime--;
    }
    if(sandstormTime == 0){
        if(inSandstorm){
            inSandstorm = false;
            hungerCost/= 1.5;
            thirstCost/= 1.5;
        }

        srand(static_cast<unsigned>(time(0)));
        int chance = rand() % 100;
        if(chance < PROBABILITY_PRECENT_OF_SANDSTORM){
            cout << "There is a sandstorm!!! You're getting hungrier and thirstier." << endl << endl;
            sandstormTime = 3;
            hungerCost*= 1.5;
            thirstCost*= 1.5;
            return true;
        }
        else{
            return false;
        }
    }
    return false;
}

/* Set & Get function*/
void Room::setUpRoom(Room* upRoom){
    this->upRoom = upRoom;
}
void Room::setDownRoom(Room* downRoom){
    this->downRoom = downRoom;
}
void Room::setLeftRoom(Room* leftRoom){
    this->leftRoom = leftRoom;
}
void Room::setRightRoom(Room* rightRoom){
    this->rightRoom = rightRoom;
}
void Room::setIsExit(bool isExit){
    this->isExit = isExit;
}
void Room::setIndex(int index){
    this->index = index;
}
void Room::setMonsterExist(bool monsterExist){
    this->monsterExist = monsterExist;
}
void Room::setObjects(vector<Object*> objects){
    this->objects = objects;
}
bool Room::getIsExit(){
    return isExit;
}
int Room::getIndex(){
    return index;
}
bool Room::getMonsterExist(){
    return monsterExist;
}
int Room::getHungerCost(){
    return hungerCost;
}
int Room::getThirstCost(){
    return thirstCost;
}
string Room::getRoomType(){
    return roomType;
}
vector<Object*> Room::getObjects(){
    return objects;
}
Room* Room::getUpRoom(){
    return upRoom;
}
Room* Room::getDownRoom(){
    return downRoom;
}
Room* Room::getLeftRoom(){
    return leftRoom;
}
Room* Room::getRightRoom(){
    return rightRoom;
}
