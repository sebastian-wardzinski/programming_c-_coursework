#include <galaxy-explorer/AsteroidList.hpp>

//AsteroidListItem constructor that takes no arguments
AsteroidListItem::AsteroidListItem() {
    this->next = nullptr;
    this->data = nullptr;
}

//AsteroidListItem constructor that takes an asteroid object
AsteroidListItem::AsteroidListItem(Asteroid a) {
    this->next = nullptr;
    Asteroid* ast = new Asteroid(a.getID(), a.getMass(), a.getHealth(), a.getCurrentHitbox(), a.getVelocity());
    this->data = ast;
}

//AsteroidListItem destructor
AsteroidListItem::~AsteroidListItem() {
    delete data;
    data = NULL;
    next = NULL;
}

//AstreroidList constructor, creates an empty list
AsteroidList::AsteroidList(){
    head.setNext(NULL);
}

//AsteroidList copy constructor
AsteroidList::AsteroidList(const AsteroidList& src)
{
    const AsteroidListItem* ptr = src.head.getNext();
    AsteroidListItem* nptr = NULL;
    AsteroidListItem* temp = NULL;
    
    while(ptr!=NULL){
        nptr = new AsteroidListItem(ptr->getData());
        if(temp == NULL) head.setNext(nptr);
        else temp->setNext(nptr);
        
        temp = nptr;
        ptr = ptr->getNext();
    } 
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the destructor (because you should put all your constructors together).
}

//AsteroidList destructor 
AsteroidList::~AsteroidList() {
    AsteroidListItem* tptr = head.getNext();
    
    while(tptr!=NULL){
        head.setNext(tptr->getNext());  
        delete tptr;
        tptr = head.getNext();
    }
    delete tptr;
    tptr=NULL;
    head.setNext(NULL);
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the copy constructor (because you should put all your constructors together).
}

//Add an asteroid to the front of the list
void AsteroidList::pushFront(Asteroid e) {
    AsteroidListItem* nptr = new AsteroidListItem(e);
    nptr->setNext(head.getNext());
    head.setNext(nptr);
}

//Return the first node of the AsteroidList
Asteroid& AsteroidList::front() {
    AsteroidListItem* fnode;
    fnode = head.getNext();
    
    return fnode->getData();
}

//Return the first node of the constant AsteroidList
const Asteroid& AsteroidList::front() const {
    const AsteroidListItem* fnode;
    fnode = head.getNext();
    
    return fnode->getData();
}

//Checks if the list is empty
bool AsteroidList::isEmpty() const {
    if(head.getNext() == NULL) return (1);
    else return (0);
}

//Returns the number of items in the list
int AsteroidList::size() const {
    int count = 0;
    const AsteroidListItem *tptr = &head;
    while(tptr->getNext() !=NULL){
        count++;
        tptr = tptr->getNext();
    }
    
    return (count);
}

//Returns the address of the pointer that points to the first asteroid
AsteroidListItem* AsteroidList::beforeBegin() {
    return &head;
}

//Same as above but for a constant list
const AsteroidListItem* AsteroidList::beforeBegin() const {
    return &head;
}

//Returns the address of the first asteroid in the list
AsteroidListItem* AsteroidList::begin() {
    return head.getNext();
}

//Same as above but for a constant list
const AsteroidListItem* AsteroidList::begin() const {
    return head.getNext();
}

//Returns the address of the last asteroid in the last
AsteroidListItem* AsteroidList::beforeEnd() {
    AsteroidListItem *tptr = &head;
    
    while (tptr->getNext() != NULL)
        tptr = tptr->getNext();
    
    return tptr;
}

//Same as above but for a constant list
const AsteroidListItem* AsteroidList::beforeEnd() const {
    const AsteroidListItem *tptr = &head;
    
    while (tptr->getNext() != NULL)
        tptr = tptr->getNext();
    
    return tptr;
}

//Where the last asteroid points to (NULL)
AsteroidListItem* AsteroidList::end() {
	return NULL;
}

//Where the last asteroid points to (NULL)
const AsteroidListItem* AsteroidList::end() const {
	return NULL;
}

//Inserts a given asteroid immediately after the list item 'prev'
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    AsteroidListItem* nptr = new AsteroidListItem(e);
    
    nptr->setNext(prev->getNext());
    prev->setNext(nptr);
   
    return nptr;
}

//Inserts a given AsteroidList after the list item 'prev'
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
    AsteroidListItem* tptr = prev;
    
    AsteroidListItem* nextItem = tptr->getNext();
    const AsteroidListItem* optr = others.head.getNext();
    
    while(optr != NULL){
        prev = this->insertAfter(prev, optr->getData());
        optr = optr->getNext();
    }
    tptr = nextItem;
}

//Deletes the AsteroidListItem immediately after the item 'prev'
AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    AsteroidListItem* tptr = prev->getNext();
    
    prev->setNext(tptr->getNext());
    tptr->setNext(NULL);
    delete tptr;
    tptr = NULL;
    
    return prev->getNext();
}

//Clears all the AsteroidListItems in the linked list, but preserves the head
void AsteroidList::clear() {
    AsteroidListItem* tptr = head.getNext();
    
    while(tptr!=NULL){
        head.setNext(tptr->getNext());  
        delete tptr;
        tptr = head.getNext();
    }
    delete tptr;
    tptr=NULL;
    head.setNext(NULL);

}

//Assignment operator for AsteroidLists
AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
    if(this == &src) return (*this);
    
    this->clear();
    AsteroidList* ptr = new AsteroidList(src);
    head.setNext(ptr->head.getNext());
    
    return(*this);
    
}
