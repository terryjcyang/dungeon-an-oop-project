#include "Item.hpp"
#include "Player.hpp"

Item::Item(){
    
}
Item::Item(string name, string tag, int health, int attack, int defense, int hunger = 0, int thirst = 0, int poison = 0):
Object(name, tag), health(health), attack(attack), defense(defense),
hunger(hunger), thirst(thirst), poison(poison){

}

/* In Item, pick up action.
 You should add status to the player. */
bool Item::triggerEvent(Object* object){
    Player* player = dynamic_cast<Player*>(object);
    if(player == nullptr)
        return false;

        while(getTag() == "chest" && inside.size() != 0){
            cout << "Look what is inside the chest!" << endl << "It's a " << inside.at(0)->getName() << "." << endl;
            inside.at(0)->printItem();
            cout << " is in your backpack." << endl << endl;
            player->addItem(inside.at(0));
            this->inside.erase(inside.begin());
        }
        if(getTag() != "chest"){
            player->addItem(this);
            this->printItem();
            cout << " is in your backpack." << endl << endl;
        }
        player->getCurrentRoom()->popObject(this);
        return true;
}

void Item::printItem(){
    cout << getName();
    if(getTag() == "money"){
        return;
    }
    cout << "(";
    if(health != 0){
        cout << "Health enhancement:" << health;
    }
    if(attack != 0){
        cout << "Attack enhancement:" << attack << " ";
    }
    if(defense != 0){
        cout << "Defense enhancement:" << defense << " ";
    }
    if(hunger != 0){
        cout << "Hunger complement:" << hunger << " ";
    }
    if(thirst != 0){
        cout << "Thirst complement:" << thirst << " ";
    }
    if(poison != 0){
        cout << "Poison cure:" << poison << " ";
    }
    cout << ")";
}

///* Set & Get function*/
int Item::getHealth(){
    return health;
}
int Item::getAttack(){
    return attack;
}
int Item::getDefense(){
    return defense;
}
int Item::getHunger(){
    return hunger;
}
int Item::getThirst(){
    return thirst;
}
int Item::getPoison(){
    return poison;
}
vector<Item*> Item::getInside(){
    return inside;
}
void Item::setHealth(int health){
    this->health = health;
}
void Item::setAttack(int attack){
    this->attack = attack;
}
void Item::setDefense(int defense){
    this->defense = defense;
}
void Item::setHunger(int hunger){
    this->hunger = hunger;
}
void Item::setThirst(int thirst){
    this->thirst = thirst;
}
void Item::setPoison(int poison){
    this->poison = poison;
}
void Item::setInside(vector<Item*> inside){
    this->inside = inside;
}
