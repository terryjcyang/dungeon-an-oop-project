#ifndef NPC_HPP_INCLUDED
#define NPC_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "GameCharacter.hpp"
#include "Player.hpp"
#include "Item.hpp"

using namespace std;

class Item;

class NPC: public GameCharacter
{
private:
    string script;
public:
    NPC();
    NPC(string,string,vector<Item*>);

    /* Virtual function that you need to complete   */
    /* In NPC, this function should deal with the   */
    /* transaction in easy implementation           */
    bool triggerEvent(Object*);

    void listNpcItems();
    
    /* Set & Get function*/
    void setScript(string);
    string getScript();

};


#endif // NPC_HPP_INCLUDED
