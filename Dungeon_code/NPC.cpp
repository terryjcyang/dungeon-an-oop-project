#include "NPC.hpp"

NPC::NPC(){
    
}
NPC::NPC(string name, string script, vector<Item*> items):
GameCharacter(name, "NPC", -1, -1, -1, items), script(script){
    
}

void NPC::listNpcItems(){
    cout << ">" << getName() << "'s commodity:" << endl << endl;
    listItems();
} /*print all the Item in this NPC*/

/* In NPC, transaction in easy implementation */
bool NPC::triggerEvent(Object* object){
    Player* player = dynamic_cast<Player*>(object);
    cout << getScript() << endl << endl;
    listNpcItems();
    if(items.size() == 0){
        cout << "Sorry, someone just bought my last commodity away." << endl << "...." << endl << "Wait! Was that you??!  I regret. Give me extra five golden coins. OR I WILL CALL THE KNIGHTS!!" << endl << "Wait, wait...." << endl << endl << player->getName() << ": Hoo, fortunately I run fast." << endl << endl;
        return false;
    }
    
    cout << "What would you like to buy? (0: buy nothing)" << endl << endl;
    int choice;
    cin >> choice;
    if(choice == 0 || choice > items.size()){
        cout << "Sure. See you later." << endl << endl;
        return false;
    }
    else{
        cout << "Oh, that one. That is GREAT. Give me one golden coin, then you can have it." << endl << endl;
        vector<Item*> inventory = player->getItems();
        int numberOfInventory = static_cast<int>(inventory.size());
        int indexOfCoin = -1;
        for(int i=0;i<numberOfInventory;i++){
            if(inventory.at(i)->getTag() == "money"){
                indexOfCoin = i;
                break;
            }
        }
        if(indexOfCoin == -1){
            cout << "...You don't have a GOLDEN COIN!! Sorry, see you next time." << endl << endl;
            return false;
        }
        
        player->addItem(items.at(choice-1));
        cout << player->getName() << ": Here you go." << endl
        << getName() << ": Ok, here's your " << items.at(choice-1)->getName() << "." << endl << endl;
        items.erase(items.begin() + choice-1);
        return true;
    }
}

/* Set & Get function*/
void NPC::setScript(string script){
    this->script = script;
}

string NPC::getScript(){
    return script;
}
