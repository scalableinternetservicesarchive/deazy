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
:m_StudentWorld(sWorld),GraphObject(imageID,startX,startY, startDirection,depth) /*,m_alive(true),m_infected(false)*/
{}
//check if the actor is alive
//bool Actors:: isAlive() const
//{
//    return m_alive;
//}
//make living status of the actor dead
//void Actors::killTheActor()
//{
//    m_alive=false;
//}
//change the infection status
//void Actors:: gotInfected()
//{
//    m_infected=true;
//}
////check for infection
//bool Actors::isInfected() const
//{
//    return m_infected;
//}
StudentWorld* Actors:: getWorld() const
{
    return m_StudentWorld;
}
Actors::~Actors()
{}
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
:Actors(IID_PLAYER, startX , startY, right , 0 , sWorld )/*, m_infectionCount(0)*/
{
    
}
Penelope::~Penelope()
{}
bool Penelope::blockActors()
{
    return true;
}
//Penelope doSomething function
void Penelope:: doSomething()
{
    //if Penelope is not alive, don't do anything
//    if(!isAlive())
//        return;
//    //The doSomething() method must check to see if Penelope is infected
//    if(!isInfected())
//    {
//        //increament the infection rate by one during each tick
//        m_infectionCount++;
//        if(m_infectionCount==500)
//        {
//            //She must immediately set her status to dead
//            killTheActor();
//            //------- NOT SURE TO BE HERE !!!!!!!!!!!!!!!!!!!!!!!
//           // getWorld()->decLives();
//            //The game must play a SOUND_PLAYER_DIE sound effect
//            getWorld()->playSound(SOUND_PLAYER_DIE);
//            //The doSomething() method must return immediately, doing nothing more during this tick
//            return;
//        }
//    }
    int ch;
    //if the user pressed any keys during the tick
    if (getWorld()->getKey(ch))
    {
        cout << "Dir:" << getDirection()<< endl;
        cout << "x:" << this->getX()<< endl;
        cout << "y:" << this->getY()<< endl;
        //to determine the destination based on the user d
        switch (ch)
        {
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
                if(getWorld()->isBlocked((this->getX()-16)/16, (this->getY())/16))
                {
                    //then update Penelope’s location to the specified location with the GraphObject class’s moveTo() method.
                    this->moveTo(this->getX()-4, this->getY());
                }
                
                break;
            case KEY_PRESS_RIGHT:
                //... move Penelope to the right ...;
                setDirection(right);
                
                /*
                 If the movement to (dest_x, dest_y) would not cause Penelope’s
                 bounding box to intersect with the bounding box of any wall,
                 citizen or zombie objects
                 */
                cout <<this->getX();
                if(getWorld()->isBlocked((this->getX()+16)/16, (this->getY())/16))
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
                if(getWorld()->isBlocked((this->getX())/16, (this->getY()+16)/16 ))
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
                if(getWorld()->isBlocked((this->getX())/16,( this->getY()-16)/16))
                {
                    //then update Penelope’s location to the specified location with the GraphObject class’s moveTo() method.
                    this->moveTo(this->getX(), this->getY()-4);
                }
                break;
//              If the user pressed the tab key and if Penelope has any landmines in her
//              inventory, Penelope will introduce a new landmine object at her current
//              (x,y) location into the game and her landmine count will decrease by 1.
//            case KEY_PRESS_TAB:
//                break;
//                If the user pressed the enter key and if Penelope has any vaccines in her
//                inventory, Penelope will set her infected status to false and reduce her
//                vaccine count by 1. (She wasted that vaccine if she was not infected.)
//            case KEY_PRESS_ENTER:
//                break;
//                If the player pressed the space key and Penelope has at least one
//                flamethrower charge, then Penelope will attempt to fire three flames into
//                the three slots directly in front of her:
//            case KEY_PRESS_SPACE:
//                break;
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


//==============================================End of Penelope Methods ===========================================


// ============================================= Wall Methods =====================================================

//1. A wall object must have an image ID of IID_WALL.
//2. The object must start at the location on the level as specified in the current level’s
//data file. The object’s starting location in the level must be equal to
//(SPRITE_WIDTH * level_x, SPRITE_HEIGHT * level_y); its starting level_x
//and level_y can be obtained using our provided Level class. Hint: The
//StudentWorld object can pass in this (x,y) location when constructing the object.
//3. A wall object has a direction of right.
//4. A wall object has a depth of 0.
//Walls constructor
Walls::Walls(int startX, int startY, StudentWorld *sWorld)
:Actors(IID_WALL,  startX ,  startY, right,0,sWorld)
{}
bool Walls::blockActors()
{
    return true;
}
//Walls doSomething() method
void Walls:: doSomething()
{
//  A wall must be given an opportunity to do something during every tick (in its
//  doSomething() method). When given an opportunity to do something during a tick, the
//  wall must do nothing. After all, it's just a wall!
    return;
}
Walls::~Walls()
{}


//Block the actors


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
bool Exit::blockActors()
{
    return false;
}

//===================================End of the Exit Method ================================

//// Randomly picks a direction
//GraphObject::Direction Actor::randomDir()
//{
//    int choice = randInt(0, 3);
//    Direction dirChoice = none;
//    switch (choice)
//    {
//        case 0:
//            dirChoice = up;
//            break;
//        case 1:
//            dirChoice = right;
//            break;
//        case 2:
//            dirChoice = down;
//            break;
//        case 3:
//            dirChoice = left;
//            break;
//    }
//    return dirChoice;
//}





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
