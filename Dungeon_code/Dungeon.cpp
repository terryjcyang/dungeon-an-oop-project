#include "Dungeon.hpp"
#define TOTAL_POINTS_OF_HPPEALTH_ATTACK_DEFENSE 2000

Dungeon::Dungeon():
exitRoom(nullptr){
    
}

/* Create a new player, and give basic status */
void Dungeon::createPlayer(){
    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;
    int health, attack, defense;
    cout << "You have " << TOTAL_POINTS_OF_HPPEALTH_ATTACK_DEFENSE << " points." << endl << "Allot them to your health, attack, and defense wisely.";
    cout << "Enter three numbers(integers) in sequence to allot these point values: ";
    cin >> health >> attack >> defense;
    player = Player(playerName, health, attack, defense);
    cout << "Player " << playerName << " is ready." << endl << endl;
    printSmileFace();
}

/* Create a map, which include several different rooms */
void Dungeon::createMap(){  //hard code: inefficient
    //擁抱改變，遠離Hard Code。
    rooms.reserve(5);
    //Room 0: monster(dead angel), water(fountain),
    vector<Object*> room0Objects = {
        new Monster("Dead Angel", 100, 35, 30, 0, 0),
        new Item("Holy Water", "weapon", 200, 0, 0, 0, 0, 0)
    };
    
    //Room 1(desert): chest(inside: coin), animal(camel: milk),
    vector<Item*> itemsOfCamel = {
        new Item("Milk", "food", 0, 0, 0, 0, 0, 150)
    };
    vector<Object*> room1Objects = {
        new Item("Chest in Fairy Tale", "chest", 0, 0, 0, 0, 0, 0),
        new Monster("Camel", 0, 0, 0, 0, 0, itemsOfCamel, "animal")
    };
    vector<Item*> chestInside = {
        new Item("Sword", "weapon", 0, 150, 70, 0, 0, 0),
        new Item("Golden Coin", "money", 0, 0, 0, 0, 0, 0)
    };
    dynamic_cast<Item*>(room1Objects.at(0))->setInside(chestInside);
    assert(dynamic_cast<Item*>(room1Objects.at(0)) != nullptr);
    
    //Room 2(forest):food(grapefruit), NPC(vendor: bread), monster(huge krait: poison, has meat),
    string scriptOfVendor = "Vendor: Hi! I used to be an adventurer here, but as I become older, I started to sell necessities in this dugeon. Nice to meet you, young brave.";
    vector<Item*> itemsOfVendor = {
        new Item("Bread", "food", 0, 0, 0, 100, 0, 0)
    };
    vector<Item*> itemsOfHugeKrait = {
        new Item("Meat", "food", 0, 0, 0, 300, 0, 0)
    };
    vector<Object*> room2Objects = {
        new Item("Grapefruit", "food", 0, 0, 0, 70, 10, 0),
        new NPC("Vendor", scriptOfVendor, itemsOfVendor),
        new Item("Water", "food", 0, 0, 0, 0, 100, 0),
        new Monster("Huge Krait", 400, 200, 200, 100, 3, itemsOfHugeKrait)
    };
    
    //Room 3(swamp): monster(crocodile), item(medicinal liquid;health up),
    vector<Object*> room3Objects = {
        new Monster("Acient Crocodile", 500, 230, 150, 0, 0),
        new Item("Medicinal Liquid", "weapon", 300, 0, 0, 0, 0, 0)
    };
    
    //Room 4:monster(demon)
    vector<Item*> itemsOfDemon = {
        new Item("The Key of Dungeon", "weapon", 0, 0, 0, 0, 0, 0)
    };
    vector<Object*> room4Objects = {
//        new Monster("Pit Bull", 600, 300, 210, 0, 0),
        new Monster("Demon the King", 450, 310, 210, 0, 0, itemsOfDemon),
    };

    rooms.push_back(Room("Lobby Square", false, 0, true, room0Objects));
    rooms.push_back(Room("desert", false, 1, false, room1Objects));
    rooms.push_back(Room("forest", false, 2, true, room2Objects));
    rooms.push_back(Room("swamp", false, 3, true, room3Objects));
    rooms.push_back(Room("Demon's Castle", true, 4, true, room4Objects));
    exitRoom = &rooms.at(4);
    
    makeRoomBesidePair(0, 1, 'p');
    makeRoomBesidePair(1, 2, 'h');
    makeRoomBesidePair(1, 3, 'p');
    makeRoomBesidePair(4, 3, 'h');
    cout << "Map is ready." << endl;
}
void Dungeon::makeRoomBesidePair(int room1, int room2, char relationship){  //first:left || up room
    if(relationship == 'p'){    //pendicular
        rooms.at(room1).setDownRoom(&rooms.at(room2));
        rooms.at(room2).setUpRoom(&rooms.at(room1));
    }
    else if(relationship == 'h'){  //horizontal
        rooms.at(room2).setLeftRoom(&rooms.at(room1));
        rooms.at(room1).setRightRoom(&rooms.at(room2));
    }
}

/* Deal with player's moving action */
void Dungeon::handleMovement(){
    cout << "Where do you want to go?" << endl << endl;
    vector<Room*> roomArr;
    Room* currentRoom = player.getCurrentRoom();
    
    if(currentRoom->getUpRoom() != nullptr){
        roomArr.push_back(currentRoom->getUpRoom());
        cout << roomArr.size() << ". Go up" << endl << endl;
    }
    if(currentRoom->getDownRoom() != nullptr){
        roomArr.push_back(currentRoom->getDownRoom());
        cout << roomArr.size() << ". Go down" << endl << endl;
    }
    if(currentRoom->getLeftRoom() != nullptr){
        roomArr.push_back(currentRoom->getLeftRoom());
        cout << roomArr.size() << ". Go left" << endl << endl;
    }
    if(currentRoom->getRightRoom() != nullptr){
        roomArr.push_back(currentRoom->getRightRoom());
        cout << roomArr.size() << ". Go right" << endl << endl;
    }
    
    int choice;
    cin >> choice;
    player.changeRoom(roomArr.at(choice-1));
}

/* Deal with all game "initial" setting */
/* Including create player, create map etc  */
void Dungeon::startGame(){
    createMap();
    createPlayer();
    player.setCurrentRoom(&rooms.at(0));
    cout << "GAME IS GOING TO BEGIN. " << endl << "Kill all monsters and survive..." << endl << endl;
}

/* Deal with the player's action     */
/* including showing the action list that player can do at that room   */
/* and dealing with player's input   */
void Dungeon::chooseAction(vector<Object*> objects){
    cout << "-------------------------------" << endl 
    <<  "-------------------------------" << endl
    << "You are in room " << player.getCurrentRoom()->getIndex() << ": " <<  player.getCurrentRoom()->getRoomType() << "." << endl
    << "[Action Menu] What do you want to do ?" << endl << endl;
    vector<string> options = {
        "change room", "status", "backpack"
    };
    if(player.getCurrentRoom()->getIndex() == 0 && player.getCurrentRoom()->getMonsterExist()){
        options.at(0) = "let me think";
        cout << "1.let me think longer" << endl;
    }
    else if(player.getCurrentRoom()->getMonsterExist()){
        options.at(0) = "retreat";
        cout << "1.retreat to previous room" << endl;
    }
    else
        cout << "1.Go to other rooms" << endl;
    cout << "2.Check status" << endl
    << "3.Open backpack" << endl;
    
    int numOfObjects = static_cast<int>(objects.size());
    for(int i=0;i<numOfObjects;i++){
        string objectType = objects.at(i)->getTag();
        string objectName = objects.at(i)->getName();
        cout << i+4 << ".";
        if(objectType == "NPC"){
            options.push_back("npc");
            cout << "Talk to " << objectName << endl;
        }
        else if(objectType == "Monster"){
            options.push_back("monster");
            cout << "Fight with " << objectName << endl;
        }
        else if(objectType == "weapon"){
            options.push_back("weapon");
            cout << "Pick up " << objectName << endl;
        }
        else if(objectType == "food"){
            options.push_back("food");
            cout << "Pick up " << objectName << endl;
        }
        else if(objectType == "money"){
            options.push_back("money");
            cout << "Pick up " << objectName << endl;
        }
        else if(objectType == "chest"){
            options.push_back("chest");
            cout << "Open the chest: " << objectName << endl;
        }
        else if(objectType == "animal"){
            options.push_back("animal");
            cout << "Get close to " << objectName << endl;
        }
        else{
            cout << "=---=---error---=-===" << endl;
        }
    }

    int choice; //input user's choice(digit
    cin >> choice;
    cout << endl;
    if(choice > options.size())
        return;
    
    string choiceWord = options.at(choice - 1);
    if(choiceWord == "change room"){
        handleMovement();
    }
    else if(choiceWord == "status"){
        player.triggerEvent(&player);
    }
    else if(choiceWord == "backpack"){
        player.openBackpack();
    }
    else if(choiceWord == "retreat"){
        player.changeRoom(player.getPreviousRoom());
    }
    else if(choiceWord == "animal"){
        dynamic_cast<Monster*>(objects.at(choice - 4))->getFromAnimal(&player);
    }
    else if(choiceWord == "let me think"){
        
    }
    else{   //including items(food, weapon, chest, coin) and NPC
        objects.at(choice - 4)->triggerEvent(&player);
    }
}

/* Check whether the game should end or not */
/* Including player victory, or he/she dead */
bool Dungeon::checkGameLogic(){
    if(player.checkIsDead() || exitRoom->getMonsterExist() == false){
        return true;
    }else{
        return false;   //means the game is not completed
    }
}

/* Deal with the whole game process */
void Dungeon::runDungeon(){
    startGame();
    
    while(checkGameLogic() == false){
        chooseAction(player.getCurrentRoom()->getObjects());
        player.hungerThirstConsumption();
        player.getCurrentRoom()->sandstorm();
    }
    
    //end game, decide whether win or lose
    if(player.getCurrentHealth() > 0){
        cout << "You win! Congradulation~" << endl << "See you next time!" << endl << endl;
    }else{
        cout << player.getName() << " died." << endl << "Game over." << endl << endl;
    }
}

void Dungeon::printSmileFace(){
    cout
    << "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⣤⣴⣶⠶⠿⠿⠿⠛⠛⠛⠿⠿⠿⠶⣶⣦⣤⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl
    << "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⡾⠟⠛⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠛⠻⢷⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl
    << "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣴⣾⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⣷⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl
    << "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⡾⠟⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⢷⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl
    << "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl
    << "    ⠀⠀⠀⠀⠀⠀⠀⢀⣴⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢿⣦⡀⠀⠀⠀⠀⠀⠀⠀" << endl
    << "    ⠀⠀⠀⠀⠀⠀⣠⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⣿⣿⣿⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⣿⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣄⠀⠀⠀⠀⠀⠀" << endl
    << "    ⠀⠀⠀⠀⠀⣼⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⣧⠀⠀⠀⠀⠀" << endl
    << "    ⠀⠀⠀⢀⣾⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣷⡀⠀⠀⠀" << endl
    << "    ⠀⠀⢀⣾⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣷⡀⠀⠀" << endl
    << "    ⠀⠀⣼⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣧⠀⠀" << endl
    << "    ⠀⣸⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⡿⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣇⠀" << endl
    << "    ⢀⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀⢻⣿⣿⣿⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⡀" << endl
    << "    ⢸⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣿⣿⣿⣿⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡇" << endl
    << "    ⣾⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠛⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣷" << endl
    << "    ⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣷⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣶⣿⣿⣿⠂⠀⠀⠀⠀⠀⠀⠀⠸⣿" << endl
    << "    ⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢛⣿⣿⣿⣿⣷⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿" << endl
    << "    ⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⡏⠙⠛⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠋⠁⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿" << endl
    << "    ⢿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡿" << endl
    << "    ⢸⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⡇" << endl
    << "    ⠈⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⠁" << endl
    << "    ⠀⢹⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⡇⠀" << endl
    << "    ⠀⠀⢻⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⣿⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⣸⡟⠀⠀" << endl
    << "    ⠀⠀⠈⢿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⣿⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⣰⡿⠁⠀⠀" << endl
    << "    ⠀⠀⠀⠈⢿⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⣰⡿⠁⠀⠀⠀" << endl
    << "    ⠀⠀⠀⠀⠀⢻⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⣿⣿⣷⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣶⣿⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⡟⠀⠀⠀⠀⠀" << endl
    << "    ⠀⠀⠀⠀⠀⠀⠙⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⢿⣿⣿⣷⣦⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣶⣿⣿⣿⠟⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⠋⠀⠀⠀⠀⠀⠀" << endl
    << "    ⠀⠀⠀⠀⠀⠀⠀⠈⠻⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠿⣿⣿⣿⣿⣶⣶⣦⣤⣤⣤⣤⣶⣶⣾⣿⣿⣿⡿⠟⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⠟⠁⠀⠀⠀⠀⠀⠀⠀" << endl
    << "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⠛⠻⠿⠿⠿⠿⠿⠿⠿⠿⠛⠛⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl
    << "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⢷⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⡾⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl
    << "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⢷⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣴⡾⠟⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl
    << "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠻⢷⣦⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⣴⡾⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl
    << "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⠛⠻⠿⠶⣶⣶⣶⣦⣤⣴⣶⣶⣶⠶⠿⠟⠛⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl << endl;
}
