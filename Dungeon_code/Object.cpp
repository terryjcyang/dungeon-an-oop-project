#include "Object.hpp"

Object::Object(){
    
}
Object::Object(string name, string tag): 
name(name), tag(tag){

}

/* Set & Get function*/
void Object::setName(string name){
    this->name = name;
}
void Object::setTag(string tag){
    this->tag = tag;
}
string Object::getName(){
    return this->name;
}
string Object::getTag(){
    return this->tag;
}
