#include "Monster.hpp"

Monster::Monster(){
    
}
Monster::Monster(string name, int maxHealth, int attack, int defense, int poison, int poisonTime, vector<Item*> items = vector<Item*>(), string tag = "Monster"):
GameCharacter(name, tag, maxHealth, attack, defense, items),
poison(poison), poisonTime(poisonTime){
    
}
Monster::Monster(string name, int maxHealth, int attack, int defense, int poison, int poisonTime, vector<Item*> items = vector<Item*>()):
GameCharacter(name, "Monster", maxHealth, attack, defense, items),
poison(poison), poisonTime(poisonTime){
    
}
Monster::Monster(string name, int maxHealth, int attack, int defense, int poison, int poisonTime):
GameCharacter(name, "Monster", maxHealth, attack, defense),
poison(poison), poisonTime(poisonTime){
    
}

/* In Monster, the fight system. */
bool Monster::triggerEvent(Object* object){
    Player* player = dynamic_cast<Player*>(object);
    if (player == nullptr) {
        return false;
    }
    
    int choice;
    do{
        cout << "What to do, " << player->getName() << " the brave?" << endl << endl;
        cout << "1. fight[press 1]" << this->getName() << "(Your attack is " << player->getAttack() << ".)" << endl;
        if(player->getCurrentRoom()->getIndex() != 0){
            cout << "2. retreat[press 2] (go back to previous room)" << endl;
        }
        cout << endl;
        cin >> choice;
        if(choice == 1){
            int attackHitChance = 100;
            
            //player attacks
            if(player->getThirst() == 0){
                srand(static_cast<unsigned>(time(0)));
                attackHitChance = rand() % 100;
            }
            if(attackHitChance > 29){
                int damage = player->getAttack() - this->getDefense();
                this->setDefense(this->getDefense()*0.9);
                if(damage < 0)
                    damage = 0;
                this->setCurrentHealth(this->getCurrentHealth() - damage);
                int monsterHealth = this->getCurrentHealth();
                if(monsterHealth < 0)
                    monsterHealth = 0;
                cout << "Monster " << this->getName() << " gets " << damage << " damage. (Monster's defense is " << this->getDefense() << ".) "
                << "Monster's health is now " << monsterHealth << "." << endl << endl;
                //check if monster died
                if(this->getCurrentHealth() <= 0){
                    cout << "Player's victory!" << endl;
                    //monster's meat or sth
                    while(items.size() > 0){
                        cout << "Look! The monster has " << items.at(0)->getName() << " on it. Let's take it." << endl;
                        player->addItem(items.at(0));
                        items.erase(items.begin());
                    }
                    cout << endl;
                    player->getCurrentRoom()->setMonsterExist(false);
                    player->getCurrentRoom()->popObject(this);
                    break;
                }
            }
            else{
                cout << "Your hit missed since you are too thirst." << endl << endl;
            }
            
            //monster attacks
            int damage = this->getAttack() - player->getDefense();
            player->setDefense(player->getDefense()*0.7);
            if(damage < 0)
                damage = 0;
            player->setCurrentHealth(player->getCurrentHealth() - damage);
            int playerHealth = player->getCurrentHealth();
            if(playerHealth < 0)
                playerHealth = 0;
            cout << "Player " << player->getName() << " gets " << damage << " damage. (Player's defense is " << player->getDefense() << ".) "
            << "Player's health is now " << playerHealth << "." << endl << endl;
            if(poison < 0){
                if(static_cast<float>(player->getCurrentHealth()) / player->getMaxHealth() < 0.7){
                    player->setPoison(player->getPoison() + poison);
                    player->setPoisonTime(poisonTime);
                    cout << "You are poisoned by " << getName() << "'s hit." << endl << endl;
                }
            }
            
            //check if player died
            if(player->getCurrentHealth() <= 0){
                player->setCurrentHealth(0);
                break;
            }
        }
        else if(choice == 2){
            player->changeRoom(player->getPreviousRoom());
            cout << "You retreat." << endl << endl;
        }
        else{
            cout << "====ERROR=====+++" << endl << endl;
        }
    }while(choice == 1);
    
    return true;
}

void Monster::getFromAnimal(Object* object){
    Player* player = dynamic_cast<Player*>(object);
    cout << "Wao! There comes a " << getName() << "." << "Let me see what I can get." << endl;
    if(items.size() == 0){
        cout << "Oh, nothing~" << endl << endl;
    }
    else{
        cout << "Oh, I got " << items.at(0)->getName() << "." << endl << endl
        << "Item " << items.at(0)->getName() << " is in your backpack." << endl << endl;
        player->addItem(items.at(0));
        items.erase(items.begin());
    }
}

/* Set & Get function*/
void Monster::setPoison(int poison){
    this->poison = poison;
}
void Monster::setPoisonTime(int poisonTime){
    this->poisonTime = poisonTime;
}
int Monster::getPoison(){
    return poison;
}
int Monster::getPoisonTime(){
    return poisonTime;
}
