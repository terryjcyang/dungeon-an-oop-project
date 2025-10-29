#include "Player.hpp"
#define HUNGER_MAX 300
#define THIRST_MAX 350
#define HUNGER_0_HEALTH_DEDUCT -10
#define THIRST_0_HEALTH_DEDUCT -15

Player::Player(){
    
}
Player::Player(string name, int maxHealth, int attack, int defense): 
GameCharacter(name, "Player", maxHealth, attack, defense),
hunger(HUNGER_MAX), thirst(THIRST_MAX), poison(0), poisonTime(0),
currentRoom(nullptr), previousRoom(nullptr){

}

void Player::increaseStates(int healthAdd, int attackAdd, int defenseAdd, int hungerAdd, int thirstAdd, int poisonAdd){
    setCurrentHealth(getCurrentHealth()+healthAdd);
    if(getCurrentHealth() > getMaxHealth())
        setCurrentHealth(getMaxHealth());
    setAttack(getAttack()+attackAdd);
    setDefense(getDefense()+defenseAdd);
    hunger += hungerAdd;
    if(hunger > HUNGER_MAX)
        hunger = HUNGER_MAX;
    thirst += thirstAdd;
    if(thirst > THIRST_MAX)
        thirst = THIRST_MAX;
    poison += poisonAdd;
}

void Player::changeRoom(Room* room){
    previousRoom = currentRoom;
    currentRoom = room;
}

/* In Player, show the status of player.    */
bool Player::triggerEvent(Object* object){  //why accept a pointer
    cout << "Status:" << endl
    << "[" << getName() << "]" << endl
    << "> Health: " << getCurrentHealth() << "/" << getMaxHealth() << endl
    << "> Attack: " << getAttack() << endl
    << "> Defense: " << getDefense() << endl
    << "> Hunger: " << hunger << "/" << HUNGER_MAX << "(get damage if <= 0)" << endl
    << "> Thirst: " << thirst << "/" << THIRST_MAX << "(get damage if <= 0)" << endl
    << "> Poison: " << poison << "(get damage if > 0)" << endl << endl;
    //> (All you want to add...)
    
    return true;
}

bool Player::openBackpack(){    //also, use items
    cout << "> Inside your backpack: " << endl << endl;
    listItems();
    cout << endl;
    
    if(items.size() == 0){
        return false;
    }
    cout << "Do you want to eat food or equip weapon?" << endl
    << "(enter choice, or press 0 if no need)" << endl;
    int choice;
    cin >> choice;
    if(choice == 0 || items.at(choice - 1)->getTag() == "money"){
        cout << "You did not select any thing." << endl << endl;
        return false;
    }
    int healthEnhance = items.at(choice - 1)->getHealth();
    int attackEnhance = items.at(choice - 1)->getAttack();
    int defenseEnhance = items.at(choice - 1)->getDefense();
    int hungerEnhance = items.at(choice - 1)->getHunger();
    int thirstEnhance = items.at(choice - 1)->getThirst();
    int poisonCure = items.at(choice - 1)->getPoison();
    increaseStates(healthEnhance, attackEnhance, defenseEnhance, hungerEnhance, thirstEnhance, poisonCure);
    if(healthEnhance != 0 || attackEnhance != 0 || defenseEnhance != 0){
        cout << "You get health / attack / defense points enhancement: " << healthEnhance << "/" << attackEnhance << "/" << defenseEnhance << " respectively." << endl << endl;
    }
    else{
        cout << "You get hunger / thirst complement and poison cure: " << hungerEnhance << "/" << thirstEnhance << "/" << poisonCure <<  " respectively." << endl << endl;
    }
    items.erase(items.begin() + choice - 1);
    return true;
}

void Player::hungerThirstConsumption(){
    //whenever after an action(since time passing)
    if(getCurrentHealth() == 0){
        return;
    }
    cout << "** After this run: ";
    //environment poison(swamp)
    static bool isSwamp = false;
    if(currentRoom->getRoomType() == "swamp" && isSwamp == false){
        isSwamp = true;
        poison += -20;
        poisonTime = 3;
        cout << endl << "You are poisoned since you're crossing a swamp." << endl;
     }
    else if(currentRoom->getRoomType() != "swamp"){
        isSwamp = false;
    }
    
    int replenish = currentRoom->pointsStumbleReplenish();
    increaseStates(0, 0, 0, currentRoom->getHungerCost(), currentRoom->getThirstCost() + replenish, 0);
    
    if(hunger == 0){
        int newHealth = getCurrentHealth() + HUNGER_0_HEALTH_DEDUCT;
        if(newHealth < 0)
            newHealth = 0;
        setCurrentHealth(newHealth);
        cout << "Hunger point is 0. Getting \"" << HUNGER_0_HEALTH_DEDUCT << "\" points health deduction. Please refill it soon." << endl;
    }
    if(thirst == 0){
        int newHealth = getCurrentHealth() + THIRST_0_HEALTH_DEDUCT;
        if(newHealth < 0)
            newHealth = 0;
        setCurrentHealth(newHealth);
        cout << "Thirst point is 0. Getting \"" << THIRST_0_HEALTH_DEDUCT << "\" points health deduction. Also, you have 30% of chance miss attack to the monster. Please refill it soon." << endl;
    }
    if(poison < 0){
        int newHealth = getCurrentHealth() + poison;
        if(newHealth < 0)
            newHealth = 0;
        setCurrentHealth(newHealth);
        cout << "You have been poisoned. Getting \"" << -poison << "\" points health deduction. BTW, milk can cure you." << endl;
    }
    cout << endl;
    
    if(hunger < 0)
        hunger = 0;
    if(thirst < 0)
        thirst = 0;
    if(poisonTime > 0)
        poisonTime--;
    if(poisonTime <= 0){
        poison = 0;
        poisonTime = 0;
    }
    
    cout << "You hunger/thirst points: " << hunger << "/" << thirst << endl << endl;
        
}

/* Set & Get function*/
void Player::setCurrentRoom(Room* currentRoom){
    this->currentRoom = currentRoom;
}
void Player::setPreviousRoom(Room* previousRoom){
    this->previousRoom = previousRoom;
}
void Player::setHunger(int hunger){
    this->hunger = hunger;
}
void Player::setThirst(int thirst){
    this->thirst = thirst;
}
void Player::setPoison(int poison){
    this->poison = poison;
}
void Player::setPoisonTime(int poisonTime){
    this->poisonTime = poisonTime;
}
Room* Player::getCurrentRoom(){
    return currentRoom;
}
Room* Player::getPreviousRoom(){
    return previousRoom;
}
int Player::getHunger(){
    return hunger;
}
int Player::getThirst(){
    return thirst;
}
int Player::getPoison(){
    return poison;
}
int Player::getPoisonTime(){
    return poisonTime;
}
