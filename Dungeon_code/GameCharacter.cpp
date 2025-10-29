#include "GameCharacter.hpp"

GameCharacter::GameCharacter(){
    
}
GameCharacter::GameCharacter(string name, string tag, int maxHealth, int attack, int defense, vector<Item*> items):
Object(name, tag), maxHealth(maxHealth), currentHealth(maxHealth), attack(attack), defense(defense), items(items){

}
GameCharacter::GameCharacter(string name, string tag, int maxHealth, int attack, int defense):
Object(name, tag), maxHealth(maxHealth), currentHealth(maxHealth), attack(attack), defense(defense){

}

bool GameCharacter::checkIsDead(){
    return currentHealth <= 0;
}
int GameCharacter::takeDamage(int damage){
    currentHealth -= damage;
    return currentHealth;
}

void GameCharacter::listItems(){
    int vectorSize = static_cast<int>(items.size());
    if(vectorSize == 0)
        cout << "<<Nothing>>" << endl;
    for(int i=0;i<vectorSize;i++){
        cout << i+1 << ".";
        items.at(i)->printItem();
        cout << endl;
    }
    cout << endl;
}

void GameCharacter::addItem(Item* item){
    items.push_back(item);
}


/* Set & Get function*/
void GameCharacter::setMaxHealth(int maxHealth){
    this->maxHealth = maxHealth;
}
void GameCharacter::setCurrentHealth(int currentHealth){
    this->currentHealth = currentHealth;
}
void GameCharacter::setAttack(int attack){
    this->attack = attack;
}
void GameCharacter::setDefense(int defense){
    this->defense = defense;
}
void GameCharacter::setItems(vector<Item*> items){
    this->items = items;
}
int GameCharacter::getMaxHealth(){
    return maxHealth;
}
int GameCharacter::getCurrentHealth(){
    return currentHealth;
}
int GameCharacter::getAttack(){
    return attack;
}
int GameCharacter::getDefense(){
    return defense;
}
vector<Item*> GameCharacter::getItems(){
    return items;
}
