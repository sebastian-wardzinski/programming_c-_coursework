/*
 * This file was developed for the Fall 2018 instance of ECE244 at the University of Toronto.
 * Creator: Matthew J. P. Walker
 */


#include <galaxy-explorer/AsteroidsObserver.hpp>

//When the server sends a new asteroid on the screen
//Inserts the asteroid to the front of the linkedlist
void AsteroidsObserver::onAsteroidInRange(Asteroid asteroid) {
    asteroid_list.pushFront(asteroid);
}

//Updates the position of the asteroid
void AsteroidsObserver::onAsteroidUpdate(Asteroid asteroid) {
    AsteroidListItem* ptr = asteroid_list.begin();
    while(ptr->getData().getID() != asteroid.getID()) ptr = ptr->getNext();
    
    asteroid_list.insertAfter(ptr, asteroid);
    asteroid_list.eraseAfter(ptr);
}

//When the asteroid leaves the bounds of the screen
//Remove the asteroid from the linkedlist
void AsteroidsObserver::onAsteroidOutOfRange(Asteroid asteroid) {
    AsteroidListItem* ptr = asteroid_list.beforeBegin();
    while(ptr->getNext()->getData().getID() != asteroid.getID()) ptr = ptr->getNext();
    
    asteroid_list.eraseAfter(ptr);
}

//When an asteroid gets destroyed by the phasors
//Remove asteroid from the linked list
//Server decides whether to split the asteroid
void AsteroidsObserver::onAsteroidDestroy(Asteroid asteroid) {
    AsteroidListItem* ptr = asteroid_list.beforeBegin(); 
    while(ptr->getNext()->getData().getID() != asteroid.getID()) ptr = ptr->getNext();
    
    asteroid_list.eraseAfter(ptr);
}
