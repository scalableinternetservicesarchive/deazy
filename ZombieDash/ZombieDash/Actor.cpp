//  Actor.cpp
//  Project 3
//
//  Created by ali mirabzadeh on 2/13/19.
//  Copyright © 2019 AMZ Development. All rights reserved.

#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>
#include "Level.h"
/*
 IDs to be used for each Actor:
 IID_PLAYER (for Penelope)
 IID_ZOMBIE (for both smart and dumb zombies)
 IID_CITIZEN
 IID_FLAME
 IID_VOMIT
 IID_PIT
 IID_LANDMINE (for a deployed landmine)
 IID_VACCINE_GOODIE
 IID_GAS_CAN_GOODIE
 IID_LANDMINE_GOODIE
 IID_EXIT
 IID_WALL
*/

//  =================================== Actors Methods =================================
//Actors Constructor
Actors :: Actors(int imageID, int startX, int startY, int startDirection, int depth, StudentWorld *sWorld)
:m_StudentWorld(sWorld),GraphObject(imageID,startX,startY, startDirection,depth)
{}
//set the life status of an object. true as in alive, false as in dead
void Actors:: setAlive(bool lifeStatus)
{
    m_alive=lifeStatus;
}
//return life status of an object
bool Actors:: isAlive() const
{
    return m_alive;
}
//check if the actor is infected or not
bool Actors:: isInfected() const
{
    return m_infected;
}
//change the infection status
void Actors:: setInfection(bool infectionStatus)
{
    m_infected= infectionStatus;
}
StudentWorld* Actors:: getWorld() const
{
    return m_StudentWorld;
}
Actors::~Actors()
{}

bool Actors::blockActors(int x, int y)
{
    return false;
}
bool Actors::doesOverlap(Actors* otherObject)
{
    return false;
}
// Randomly picks a direction
Direction Actors::randomDir()
{
    int choice = randInt(0, 3);
    Direction dirChoice;
    switch (choice)
    {
        case 0:
            dirChoice = up;
            break;
        case 1:
            dirChoice = right;
            break;
        case 2:
            dirChoice = down;
            break;
        case 3:
            dirChoice = left;
            break;
    }
    return dirChoice;
}
//bool Actors:: blockActors()const
//{
//    return false;
//}

//bool Actors:: isMoved()
//{
//    return m_isMoved;
//}
//void Actors:: setMove(bool moveValue)
//{
//    m_isMoved= moveValue;
//}

////determine the bounding box
//double boundingBox(double objectX, double objectY)
//{
//    return (x+SPRITE_WIDTH−1, y+SPRITE_HEIGHT−1)
//}
//================================End of Actor's Methods ================================

// =============================== Penelope Methods ==================================
/*
 When it is first created:
 1. A Penelope object must have an image ID of IID_PLAYER.
 2. The object must start at the location on the level as specified in the current level’s
 data file. The object’s starting location in the level must be equal to
 (SPRITE_WIDTH * level_x, SPRITE_HEIGHT * level_y); its starting level_x
 and level_y can be obtained using our provided Level class. Hint: The
 StudentWorld object can pass in this (x,y) location when constructing the object.
 3. A Penelope object starts out alive.
 4. A Penelope object has a direction of right.
 5. A Penelope object has a depth of 0.
 6. A Penelope object has no landmines, flamethrower charges, or vaccines.
 7. A Penelope object has an infection status of false.
 8. A Penelope object has an infection count of 0.
 */
//Penelope Constructor
Penelope::Penelope(int startX, int startY, StudentWorld * sWorld)
:Actors(IID_PLAYER, startX , startY, right , 0 , sWorld ), m_infectionCount(0)
{
    //when constructing set life status of Penelope to be true as alive
    setAlive(true);
    //set Penelope infection in the beginning false, as not infected
    setInfection(false);
}
Penelope::~Penelope()
{}
bool Penelope::blockActors(int x, int y)
{
    return false;
}
//Penelope doSomething function
void Penelope:: doSomething()
{
    //if Penelope is not alive, don't do anything
    if(!isAlive())
        return;
   //The doSomething() method must check to see if Penelope is infected
    if(isInfected())
    {
        //increament the infection rate by one during each tick
        m_infectionCount++;
        if(m_infectionCount==500)
        {
            //She must immediately set her status to dead
            setAlive(true);
            //------- NOT SURE TO BE HERE !!!!!!!!!!!!!!!!!!!!!!!
            getWorld()->decLives();
            //The game must play a SOUND_PLAYER_DIE sound effect
            getWorld()->playSound(SOUND_PLAYER_DIE);
            //The doSomething() method must return immediately, doing nothing more during this tick
            return;
        }
    }
    int ch;
    //if the user pressed any keys during the tick
    if (getWorld()->getKey(ch))
    {
        //to determine the destination based on the user d
        switch (ch)
        {
            //
            case KEY_PRESS_LEFT:
                //Set Penelope’s direction to the specified movement direction.
                setDirection(left);
                //Determine Penelope’s destination location (dest_x, dest_y)
                /*
                 If the movement to (dest_x, dest_y) would not cause Penelope’s
                 bounding box to intersect with the bounding box of any wall,
                 citizen or zombie objects, then update Penelope’s location to the
                 specified location with the GraphObject class’s moveTo() method.
                 */
                if(getWorld()->isBlocked( this->getX()-4, this->getY(),this))
                {
                    //then update Penelope’s location to the specified location with the GraphObject class’s moveTo() method.
                    this->moveTo(this->getX()-4, this->getY());
                }
                
                break;
            case KEY_PRESS_RIGHT:
                //... move Penelope to the right ...;
                //set the direction to the right
                setDirection(right);
                /*
                 If the movement to (dest_x, dest_y) would not cause Penelope’s
                 bounding box to intersect with the bounding box of any wall,
                 citizen or zombie objects
                 */
                if(getWorld()->isBlocked((this->getX()+4), this->getY(),this))
                {
                    //then update Penelope’s location to the specified location with the GraphObject class’s moveTo() method.
                    this->moveTo(this->getX()+4, this->getY());
                }
                break;
            case KEY_PRESS_UP:
                //move up
                setDirection(up);
                /*
                 If the movement to (dest_x, dest_y) would not cause Penelope’s
                 bounding box to intersect with the bounding box of any wall,
                 citizen or zombie objects
                 */
                if(getWorld()->isBlocked( this->getX(),(this->getY()+4) ,this ))
                {
                    //then update Penelope’s location to the specified location with the GraphObject class’s moveTo() method.
                    this->moveTo(this->getX(), this->getY()+4);
                }
                break;
            case KEY_PRESS_DOWN:
                //move down
                setDirection(down);
                /*
                 If the movement to (dest_x, dest_y) would not cause Penelope’s
                 bounding box to intersect with the bounding box3 of any wall,
                 citizen or zombie objects.
                 */
               if(getWorld()->isBlocked(this->getX(),this->getY()-4, this))
                {
                    //then update Penelope’s location to the specified location with the GraphObject class’s moveTo() method.
                    this->moveTo(this->getX(), this->getY()-4);
                }
                break;
//              If the user pressed the tab key and if Penelope has any landmines in her
//              inventory
            case KEY_PRESS_TAB:
                if(m_landmines>0)
                {
                    //Penelope will introduce a new landmine object at her current (x,y) location into the game
                
                    //new Landmines(this->getX(), this->getY(), this)
                    //landmine count will decrease by 1
                    m_landmines--;
                }
                break;
//                If the user pressed the enter key and if Penelope has any vaccines in her
//                inventory
            case KEY_PRESS_ENTER:
                if(m_vaccines>0)
                {
                    //Penelope will set her infected status to false and reduce her vaccine count by 1
                    setInfection(false);
                    // reduce vaccine count by 1. (She wasted that vaccine if she was not infected.)
                    m_vaccines--;
                }
                break;
//                If the player pressed the space key and Penelope has at least one
//                flamethrower charge, then Penelope will attempt to fire three flames into
//                the three slots directly in front of her:
            case KEY_PRESS_SPACE:
                if(m_flamethrower_charges>0)
                {
                    //then Penelope will attempt to fire three flames into the three slots directly in front of her:
                    m_flamethrower_charges--;
                }
                break;
            }
        }
//    What Penelope Must Do In Other Circumstances
    
//    • Penelope can be infected by vomit. When vomit overlaps with Penelope, her
//    infection status becomes true.
//    • Penelope can be damaged. If a flame object overlaps with Penelope it will kill her.
//    When killed:
//    o She must immediately has her status set to dead,
//    o The game must play a SOUND_PLAYER_DIE sound effect
//    o (The StudentWorld object should detect her death and the current level
//       ends)
//    • Penelope blocks other objects from moving nearby/onto her. Penelope’s bounding
//    box must never intersect with that of any citizen, zombie, or wall.
}


////return number of Landmines that Penelope has
//int Penelope:: numOfLandmines()
//{
//    return m_landmines;
//}
//// return the number of Flamethrower_charges that Penelope has
//int Penelope:: numOfFlamethrower_charges()
//{
//    return m_flamethrower_charges;
//}
////return number of vaccines that Penelope has
//int Penelope:: numOfVaccines()
//{
//    return m_vaccines;
//}
//==============================================End of Penelope Methods ===========================================

// ============================================= Wall Methods =====================================================

//Walls constructor
Walls::Walls(int startX, int startY, StudentWorld *sWorld)
:Actors(IID_WALL,  startX ,  startY, right,0,sWorld)
{}
//blocking movement method for a wall
bool Walls::blockActors(int point_x, int point_y)
{
    //calculate the center of the current wall and the point passed in
    int pointX_center= point_x+ SPRITE_WIDTH/2;
    int pointY_center= point_y + SPRITE_HEIGHT/2;
    int wallX_center= this->getX() +SPRITE_WIDTH/2;
    int wallY_center= this->getY() +SPRITE_HEIGHT/2;
    
    // then use the Udulican formula, instead the distance between the centers should be less than 16
    int deltaX= pow((pointX_center - wallX_center),2);
    int deltaY= pow((pointY_center - wallY_center),2);
    
    //if that's cse then wall blocks the passed object
    if(deltaX + deltaY < pow(16,2)) return true;
    //otherwise it does not
    return false;
}
//Walls doSomething() method
void Walls:: doSomething()
{
    //A wall does nothing during a tick
    return;
}
Walls::~Walls()
{}

//What a Wall Must Do In Other Circumstances
//• A wall cannot be damaged by a flame.
//• A wall cannot be infected by vomit.
//• A wall blocks the movement of citizens, zombies, and Penelope (its bounding box must never intersect with any actor’s bounding box

//• A wall blocks flames (i.e., a flame fired by Penelope or emitted by a landmine cannot overlap6 or be created past a wall).

// ================================== End of Wall Methods ===============================================

//===================================  Exit Method ==========================================
//Constructor
Exit::Exit(int startX, int startY, StudentWorld *sWorld)
:Actors(IID_EXIT, startX , startY, right,1,sWorld)
{}
void Exit::doSomething()
{
    return;
}
Exit::~Exit()
{}
bool Exit::doesOverlap(Actors * otherObject)
{
    int exitX= this->getX();
    int exitY= this->getY();
    int otherObjectX= otherObject->getX();
    int otherObjectY= otherObject->getY();
    
    int deltaX= pow((exitX - otherObjectX),2);
    int deltaY= pow((exitY - otherObjectY),2);
    
    if(deltaY + deltaX <= 100)
        return true;
    return false;
}

//===================================End of the Exit Method ================================







//Determining Blocking of Movement
//In Zombie Dash, citizens, zombies, and Penelope can move anywhere on the level, with
//the following exceptions:
//• They must not move onto any wall.
//• They must not move onto any citizen, zombie, or Penelope.
//When we say “P must not move onto Q” we mean the following: Moving P must not
//result in P’s bounding box intersecting AT ALL with Q’s bounding box. If an actor has
//its lower left corner at location (x,y), then the actor’s bounding box is the rectangle with
//lower left corner (x,y) and upper right corner
//(x+SPRITE_WIDTH−1, y+SPRITE_HEIGHT−1)
//bool blockingOfMovement()
//{
//
//}

// ================================= Dumb Zombies Methods ================================================
DumbZombies::  DumbZombies(int startX, int startY, StudentWorld* sWorld)
:Actors(IID_ZOMBIE, startX , startY, right,0,sWorld)
{}
void DumbZombies:: doSomething()
{
    
    //Randomly pick a direction and move 1 pixel in that direction
    Direction randNum= randInt(0, 3);
    switch(randNum)
    {
        case 0:
            setDirection(up);
            this->moveTo(this->getX(),this->getY()+1 );
            break;
        case 1:
            setDirection(right);
            this->moveTo(this->getX() +1,this->getY() );
            break;
        case 2:
            setDirection(down);
            this->moveTo(this->getX(),this->getY()-1 );
            break;
        case 3:
            setDirection(left);
            this->moveTo(this->getX()-1,this->getY() );
            break;
    }
}
DumbZombies:: ~DumbZombies()
{
    
}
//=============================================== end of dumb zombies methods ==================================

//================================================ Smart Zombies ======================================

SmartZombies:: SmartZombies(int startX, int startY, StudentWorld* sWorld)
:Actors(IID_EXIT, startX , startY, right,0,sWorld)
{
    //Smart Zombie start alive
    setAlive(true);
}

void SmartZombies:: doSomething()
{
//    1. The smart zombie must check to see if it is currently alive. If not, then its
//        doSomething() method must return immediately – none of the following steps
//        should be performed
//    if(!isAlive())
//        return;
//    2. The smart zombie will become paralyzed every other tick trying to figure out
//    what to do. The 2nd, 4th, 6th, etc., calls to doSomething() for a smart zombie are the
//        “paralysis” ticks for which doSomething() must return immediately – none of the
//            following steps should be performed
    
    Direction randNum= randInt(0, 3);
    switch(randNum)
    {
        case 0:
            setDirection(up);
            this->moveTo(this->getX(),this->getY()+1 );
            break;
        case 1:
            setDirection(right);
            this->moveTo(this->getX() +1,this->getY() );
            break;
        case 2:
            setDirection(down);
            this->moveTo(this->getX(),this->getY()-1 );
            break;
        case 3:
            setDirection(left);
            this->moveTo(this->getX()-1,this->getY() );
            break;
    }
}

SmartZombies:: ~SmartZombies()
{
    
}
//=============================================== end of Smart zombies methods ==================================

//================================================ Landmines======================================
Landmines:: Landmines (int startX, int startY, StudentWorld* sWorld)
:Actors(IID_LANDMINE, startX , startY, right,1,sWorld)
{}
void Landmines:: doSomething()
{
    return;
}
Landmines::  ~Landmines ()
{
    
}
//=============================================== end of Landmines methods ==================================


//================================================ Pits ======================================
Pits:: Pits(int startX, int startY, StudentWorld* sWorld)
:Actors(IID_PIT, startX , startY, right,0,sWorld)
{}
void Pits:: doSomething()
{
    return;
}
Pits:: ~Pits()
{}
//=============================================== end of Pits methods ==================================

//================================================ Flames ======================================
Flames:: Flames(int startX, int startY, StudentWorld* sWorld)
: Actors(IID_FLAME, startX , startY, right,0,sWorld)
{}
void Flames:: doSomething()
{
    return;
}
Flames:: ~Flames()
{}
//=============================================== end of Flames methods ==================================


//================================================ Vomit ======================================
Vomit::Vomit(int startX, int startY, StudentWorld* sWorld)
:Actors(IID_VOMIT, startX , startY, right,0,sWorld)
{}
void Vomit:: doSomething()
{
    return;
}
Vomit:: ~Vomit()
{}
//=============================================== end of Vomit methods ==================================

//================================================ VaccineGoodies ======================================

VaccineGoodies:: VaccineGoodies(int startX, int startY, StudentWorld* sWorld)
:Actors(IID_VACCINE_GOODIE, startX , startY, right,1,sWorld)
{}
void VaccineGoodies:: doSomething()
{
    return;
}
VaccineGoodies:: ~VaccineGoodies()
{}
//=============================================== end of VaccineGoodies methods ==================================

//================================================ GasCanGoodies ======================================

GasCanGoodies:: GasCanGoodies(int startX, int startY, StudentWorld* sWorld)
:Actors(IID_GAS_CAN_GOODIE, startX , startY, right,1,sWorld)
{}
void GasCanGoodies:: doSomething()
{
    return;
}
GasCanGoodies:: ~GasCanGoodies()
{}
//=============================================== end of GasCanGoodies methods ==================================

//================================================ LandminesGoodies ======================================

LandminesGoodies::LandminesGoodies(int startX, int startY, StudentWorld* sWorld)
:Actors( IID_LANDMINE_GOODIE, startX , startY, right,1,sWorld  )
{}

void LandminesGoodies:: doSomething()
{
    return;
}
LandminesGoodies:: ~LandminesGoodies()
{
    
}
//=============================================== end of LandminesGoodies methods ==================================

//================================================ Citizen ======================================
Citizen:: Citizen(int startX, int startY, StudentWorld* sWorld)
:Actors(IID_CITIZEN, startX , startY, right,0,sWorld )
{}
void Citizen:: doSomething()
{
    return;
}
Citizen:: ~Citizen()
{
    
}
//=============================================== end of Citizen methods ==================================
