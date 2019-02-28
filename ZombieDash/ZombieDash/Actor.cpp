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



//Vomit is not blocked by an exit.




//  =================================== Actors Methods =================================
//Actors Constructor
Actors :: Actors(int imageID, double startX, double startY, int startDirection, int depth, StudentWorld *sWorld)
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

bool Actors::blockActors(double x, double y)
{
    return false;
}
bool Actors::doesOverlap(Actors* otherObject)
{
    return false;
}
bool Actors::isCitizen()
{
    return false;
}
bool Actors:: flameBlockable(double x, double y)
{
    return false;
}
bool Actors:: isPerson()
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
bool Actors:: isZombie()
{
    return false;
}
bool Actors:: levelHasZombie()
{
    return false;
}
void Actors:: flameDamagable(double x, double y)
{
    return;
}
void Actors:: vomitInfectable(double x, double y)
{
    return;
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
Penelope::Penelope(double startX, double startY, StudentWorld * sWorld)
:Actors(IID_PLAYER, startX , startY, right , 0 , sWorld ), m_infectionCount(0)
{
    //when constructing set life status of Penelope to be true as alive
    this->setAlive(true);
    //set Penelope infection in the beginning false, as not infected
    setInfection(false);
}
Penelope::~Penelope()
{}
void Penelope:: flameDamagable(double point_x, double point_y)
{
   
    // then use the Udulican formula, instead the distance between the centers should be less than 16
    double deltaX= pow((point_x - this->getX()),2);
    double deltaY= pow((point_y - this->getY()),2);
    
    //if that's cse then wall blocks the passed object
    if(deltaX + deltaY <= pow(10,2))
    {
        //She must immediately set her status to dead
        this->setAlive(false);
        //The game must play a SOUND_PLAYER_DIE sound effect
        getWorld()->playSound(SOUND_PLAYER_DIE);
    }
    //otherwise it does not
   
}
void Penelope:: vomitInfectable(double x, double y)
{
    double deltaX= x - this->getX();
    double deltaY= y - this->getY();
    double result = pow(deltaX, 2) + pow(deltaY, 2);
    if(result<= pow(10, 2))
        this->setInfection(true);
}
bool Penelope:: isPerson()
{
    return true;
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
        getWorld()->incrementInfection();
        if(getWorld()->infectionCounter()==500)
        {
            //She must immediately set her status to dead
            this->setAlive(false);
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
                if(getWorld()->landminesCounter()>0)
                {
                    //Penelope will introduce a new landmine object at her current (x,y) location into the game
                    getWorld()->introduceLandmineHere(this->getX(), this->getY());
                    //landmine count will decrease by 1
                    getWorld()->decrementLandmines();
                }
                break;
//                If the user pressed the enter key and if Penelope has any vaccines in her
//                inventory
            case KEY_PRESS_ENTER:
                if(getWorld()-> vaccineCounter()>0)
                {
                    //Penelope will set her infected status to false and reduce her vaccine count by 1
                    this->setInfection(false);
                    // reduce vaccine count by 1. (She wasted that vaccine if she was not infected.)
                    getWorld()->decrementVaccine();
                    getWorld()->intitailStatusInfection(0);
                }
                break;
//                If the player pressed the space key and Penelope has at least one
//                flamethrower charge, then Penelope will attempt to fire three flames into
//                the three slots directly in front of her:
            case KEY_PRESS_SPACE:
                if(getWorld()->flamethrowerCharges()>0)
                {
                    //then Penelope will attempt to fire three flames into the three slots directly in front of her:
                    getWorld()->decrementFlamethrowerCharges();
                    //Penelope must play the SOUND_PLAYER_FIRE
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                    //Penelope will add up to three new flame objects to the game. If Penelope is at (px, py) this is where the new flame objects will go: For i = 0, 1, and 2,
                    int fireDest_x, fireDest_y;
                    for (int i=1; i <4 ; i++)
                    {
                        //If Penelope is facing up: posi = (px, py + i *SPRITE_HEIGHT)
                        if(this->getDirection()==up)
                        {
                            //Compute the position posi where the next flame will go.
                            fireDest_x=this->getX();
                            fireDest_y= this->getY() + (i*SPRITE_HEIGHT);
                            //If a flame at posi would overlap1 with a wall or exit object, then immediately stop the loop.
                            if(getWorld()->isBlockedFromFlame(fireDest_x, fireDest_y, this))
                            {
                                //Otherwise add a new flame object2 at posi with a starting direction that is the same as the direction Penelope is facing.
                                getWorld()->introduceFlameObject(fireDest_x, fireDest_y, up);
                            }
                            else
                                //ii. If a flame at posi would overlap1 with a wall or exit object, then immediately stop the loop.
                                break;
                        }
                        //If Penelope is facing down: posi = (px, py − i *SPRITE_HEIGHT)
                        else if(this->getDirection()==down)
                        {
                            //Compute the position posi where the next flame will go.
                            fireDest_x=this->getX();
                            fireDest_y= this->getY() - (i*SPRITE_HEIGHT);
                            //If a flame at posi would overlap1 with a wall or exit object, then immediately stop the loop.
                            if(getWorld()->isBlockedFromFlame(fireDest_x, fireDest_y, this))
                            {
                                //Otherwise add a new flame object2 at posi with a starting direction that is the same as the direction Penelope is facing.
                                getWorld()->introduceFlameObject(fireDest_x, fireDest_y, down);
                            }
                            else
                                //ii. If a flame at posi would overlap1 with a wall or exit object, then immediately stop the loop.
                                break;
                        }
                        //If Penelope is facing right: posi = (px + i *SPRITE_WIDTH, py)
                        else if(this->getDirection()==right)
                        {
                            //Compute the position posi where the next flame will go.
                            fireDest_x=this->getX()+ (i*SPRITE_WIDTH);
                            fireDest_y= this->getY() ;
                            //If a flame at posi would overlap1 with a wall or exit object, then immediately stop the loop.
                            if(getWorld()->isBlockedFromFlame(fireDest_x, fireDest_y, this))
                            {
                                //Otherwise add a new flame object2 at posi with a starting direction that is the same as the direction Penelope is facing.
                                getWorld()->introduceFlameObject(fireDest_x, fireDest_y, down);
                            }
                            else
                                //ii. If a flame at posi would overlap1 with a wall or exit object, then immediately stop the loop.
                                break;
                        }
                        //If Penelope is facing left: posi = (px − i *SPRITE_WIDTH, py)
                        else
                        {
                            //Compute the position posi where the next flame will go.
                            fireDest_x=this->getX()-( i*SPRITE_WIDTH);
                            
                            fireDest_y= this->getY() ;
                            //If a flame at posi would overlap1 with a wall or exit object, then immediately stop the loop.
                            if(getWorld()->isBlockedFromFlame(fireDest_x, fireDest_y, this))
                            {
                                //Otherwise add a new flame object2 at posi with a starting direction that is the same as the direction Penelope is facing.
                                getWorld()->introduceFlameObject(fireDest_x, fireDest_y, down);
                            }
                            else
                                //ii. If a flame at posi would overlap1 with a wall or exit object, then immediately stop the loop.
                                break;
                        }
                        
                    }
                    
                        
                }
                break;
            }
        }
}
//    • Penelope blocks other objects from moving nearby/onto her. Penelope’s bounding
//    box must never intersect with that of any citizen, zombie, or wall.
bool Penelope::blockActors(double point_x, double point_y)
{
    //calculate the center of the current wall and the point passed in
    int pointX_center= point_x+ SPRITE_WIDTH/2;
    int pointY_center= point_y + SPRITE_HEIGHT/2;
    int penelopeX_center= this->getX() +SPRITE_WIDTH/2;
    int penelopeY_center= this->getY() +SPRITE_HEIGHT/2;
    
    // then use the Udulican formula, instead the distance between the centers should be less than 16
    int deltaX= pow((pointX_center - penelopeX_center),2);
    int deltaY= pow((pointY_center - penelopeY_center),2);
    
    //if that's cse then wall blocks the passed object
    if(deltaX + deltaY < pow(16,2)) return true;
    //otherwise it does not
    return false;
}
//==============================================End of Penelope Methods ===========================================

// ============================================= Wall Methods =====================================================

//Walls constructor
Walls::Walls(double startX, double startY, StudentWorld *sWorld)
:Actors(IID_WALL,  startX ,  startY, right,0,sWorld)
{
    this->setAlive(true);
}
//blocking movement method for a wall
bool Walls::blockActors(double point_x, double point_y)
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
bool Walls:: flameBlockable(double point_x, double point_y)
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


//What a Wall Must Do In Other Circumstances
//• A wall cannot be damaged by a flame.
//• A wall cannot be infected by vomit.
//• A wall blocks the movement of citizens, zombies, and Penelope (its bounding box must never intersect with any actor’s bounding box

//• A wall blocks flames (i.e., a flame fired by Penelope or emitted by a landmine cannot overlap6 or be created past a wall).

// ================================== End of Wall Methods ===============================================

//===================================  Exit Method ==========================================
//Constructor
Exit::Exit(double startX, double startY, StudentWorld *sWorld)
:Actors(IID_EXIT, startX , startY, right,1,sWorld)
{
    this->setAlive(true);
}
void Exit::doSomething()
{
    //1. The exit must determine if it overlaps with a citizen (not Penelope!). If so, then the exit must:
    if(getWorld()->doesExitOverlapWithCitizen(this->getX(), this->getY()))
    {
        //a. Inform the StudentWorld object that the user is to receive 500 points.
        getWorld()->increaseScore(500);
        // b. Set the citizen object’s state to dead (so that it will be removed from the game by the StudentWorld object at the end of the current tick) – note, this must not kill the citizen in a way that deducts points from the player as if the citizen died due to a zombie infection, a flame, or a pit.
        
        //  c. Play a sound effect to indicate that the citizen was saved by using the exit: SOUND_CITIZEN_SAVED.
        getWorld()->playSound(SOUND_CITIZEN_SAVED);
    }
    //2. The exit must determine if it overlaps with Penelope. If so and all citizens have either exited the level or died, then:
//    if(getWorld()->doesOverlapWithPenelope(this->getX(), this->getY()) && getWorld()->noCitizenOnLevel())
//    {
//       // a. Inform the StudentWorld object that Penelope has finished the current level
//        
//    }
  
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
    
    if( deltaY + deltaX <= 100)
        return true;
    return false;
}
bool Exit:: flameBlockable(double point_x, double point_y)
{
    //calculate the center of the current wall and the point passed in
    int pointX_center= point_x+ SPRITE_WIDTH/2;
    int pointY_center= point_x + SPRITE_HEIGHT/2;
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
//===================================End of the Exit Method ================================

// ================================= Dumb Zombies Methods ================================================
DumbZombies::  DumbZombies(double startX, double startY, StudentWorld* sWorld)
:Actors(IID_ZOMBIE, startX , startY, right,0,sWorld), m_paralyzedCounter(true), m_movementPlan(0)
{
    this->setAlive(true);
}
void DumbZombies:: flameDamagable(double point_x, double point_y)
{
    // then use the Udulican formula, instead the distance between the centers should be less than 16
    double deltaX= pow((point_x - this->getX()),2);
    double deltaY= pow((point_y - this->getY()),2);
    
    //if that's cse then wall blocks the passed object
    if(deltaX + deltaY <= pow(10,2))
    {
        //Set its own state to dead
        this->setAlive(false);
        //o Play a sound effect to indicate that the dumb zombie died: SOUND_ZOMBIE_DIE.
        getWorld()->playSound(SOUND_ZOMBIE_DIE);
        //Increase the player’s score by 1000 points.
        getWorld()->increaseScore(1000);
        
        //1 in 10 dumb zombies are mindlessly carrying a vaccine goodie that they'll drop when they die. If this dumb zombie has a vaccine goodie, it will
        // introduce a new vaccine goodie at its (x,y) coordinate by adding it to the StudentWorld object.
        if(1==randInt(1, 10))
        {
            //When a dumb zombie drops a vaccine goodie, it does not simply drop it at its own (x,y) coordinates, but tries to fling it away instead: It chooses a random direction, computes the coordinates SPRITE_WIDTH units away if the direction is left or right or SPRITE_HEIGHT units away if it is up or down, and if no other object in the game would overlap with an object created at those coordinates, introduces a new vaccine goodie at those coordinates; otherwise, it does not introduce a vaccine object.
            switch (randomDir())
            {
                case up:
                    if(getWorld()->isBlocked(this->getX(), this->getY()+SPRITE_HEIGHT, this))
                        getWorld()->addVaccineGoodieHere(this->getX(), this->getY()+SPRITE_HEIGHT);
                    break;
                case down:
                    if(getWorld()->isBlocked(this->getX(), this->getY()-SPRITE_HEIGHT, this))
                        getWorld()->addVaccineGoodieHere(this->getX(), this->getY()-SPRITE_HEIGHT);
                    break;
                case left:
                    if(getWorld()->isBlocked(this->getX() - SPRITE_WIDTH, this->getY(), this))
                        getWorld()->addVaccineGoodieHere(this->getX()- SPRITE_WIDTH, this->getY());
                    break;
                case right:
                    if(getWorld()->isBlocked(this->getX()+ SPRITE_WIDTH, this->getY(), this))
                        getWorld()->addVaccineGoodieHere(this->getX()+ SPRITE_WIDTH, this->getY());
                    break;
            }
            
        }
        
    }
   
}
void DumbZombies:: doSomething()
{
    
    //    1. The dumb zombie must check to see if it is currently alive. If not, then its doSomething() method must return immediately – none of the following steps  should be performed
    if(!isAlive())
        return;
//    2. The dumb zombie will become paralyzed every other tick trying to figure out what to do. The 2nd, 4th, 6th, etc., calls to doSomething() for a dumb zombie are the  “paralysis” ticks for which doSomething() must return immediately – none of the following steps should be performed.
    m_paralyzedCounter = !m_paralyzedCounter;
    if(m_paralyzedCounter)
        return;
//   3. The dumb zombie must check to see if a person (either Penelope or one of the citizens on the level) is in front of it in the direction it is facing:
    Direction zombieDir= this-> getDirection();
    //switch case to function depending on the direction the dumbzombie is facing
    switch (zombieDir)
    {
        //if the zombie is facing up
        case up:
        
            //The dumb zombie must check to see if a person (either Penelope or one of the citizens on the level) is in front of it in the direction it is facing:
            if(getWorld()->isPersonInFrontOfZommbie(this->getX(), this->getY()+SPRITE_HEIGHT))
            {
                //If there is a person whose Euclidean distance from the vomit coordinates is less than or equal to 10 pixels,
               if( getWorld()->isPersonWhoseEuclideanDistanceFromVomitCoordinates(this->getX(), this->getY()+SPRITE_HEIGHT))
               {
                   //then there is a 1 in 3 chance that the dumb zombie will vomit. If the zombie choses to vomit, it will
                   if(1==randInt(1, 3))
                   {
                       //i. Introduce a vomit object into the game at the vomit coordinates.
                       getWorld()->introduceVomitAtThisPoint(this->getX(), this->getY()+SPRITE_HEIGHT);
                       //Play the sound SOUND_ZOMBIE_VOMIT.
                       getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
                       //Immediately return and do nothing more this tick.
                       return;
                   }
               }
            }
            break;
        case down:
             if(getWorld()->isPersonInFrontOfZommbie(this->getX(), this->getY()-SPRITE_HEIGHT))
             {
                 //If there is a person whose Euclidean distance from the vomit coordinates is less than or equal to 10 pixels,
                 if( getWorld()->isPersonWhoseEuclideanDistanceFromVomitCoordinates(this->getX(), this->getY()-SPRITE_HEIGHT))
                 {
                     //then there is a 1 in 3 chance that the dumb zombie will vomit. If the zombie choses to vomit, it will
                     if(1==randInt(1, 3))
                     {
                         //i. Introduce a vomit object into the game at the vomit coordinates.
                         getWorld()->introduceVomitAtThisPoint(this->getX(), this->getY()-SPRITE_HEIGHT);
                         //Play the sound SOUND_ZOMBIE_VOMIT.
                         getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
                         //Immediately return and do nothing more this tick.
                         return;
                     }
                 }
             }
            break;
        case right:
             if(getWorld()->isPersonInFrontOfZommbie(this->getX()+SPRITE_WIDTH, this->getY()))
             {
                 //If there is a person whose Euclidean distance from the vomit coordinates is less than or equal to 10 pixels,
                 if( getWorld()->isPersonWhoseEuclideanDistanceFromVomitCoordinates(this->getX()+SPRITE_HEIGHT, this->getY()))
                 {
                     //then there is a 1 in 3 chance that the dumb zombie will vomit. If the zombie choses to vomit, it will
                     if(1==randInt(1, 3))
                     {
                         //i. Introduce a vomit object into the game at the vomit coordinates.
                         getWorld()->introduceVomitAtThisPoint(this->getX()+SPRITE_HEIGHT, this->getY());
                         //Play the sound SOUND_ZOMBIE_VOMIT.
                         getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
                         //Immediately return and do nothing more this tick.
                         return;
                     }
                 }
             }
            break;
        case left:
             if(getWorld()->isPersonInFrontOfZommbie(this->getX()-SPRITE_WIDTH, this->getY()))
             {
                 //If there is a person whose Euclidean distance from the vomit coordinates is less than or equal to 10 pixels,
                 if( getWorld()->isPersonWhoseEuclideanDistanceFromVomitCoordinates(this->getX()-SPRITE_HEIGHT, this->getY()))
                 {
                     //then there is a 1 in 3 chance that the dumb zombie will vomit. If the zombie choses to vomit, it will
                     if(1==randInt(1, 3))
                     {
                         //i. Introduce a vomit object into the game at the vomit coordinates.
                         getWorld()->introduceVomitAtThisPoint(this->getX()-SPRITE_HEIGHT, this->getY());
                         //Play the sound SOUND_ZOMBIE_VOMIT.
                         getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
                         //Immediately return and do nothing more this tick.
                         return;
                     }
                 }
             }
            break;
    }//end of switch
    //The dumb zombie will check to see if it needs a new movement plan because its current movement plan distance has reached zero. If so, the dumb zombie will:
    //Pick a new random movement plan distance in the range 3 through 10 inclusive.
   
    //Set its direction to a random direction (up, down, left, or right).

    if(m_movementPlan==0)
    {
        m_movementPlan= randInt(3, 10);
        this->setDirection(getWorld()->randomDir());
    }
        //5. The dumb zombie will then determine a destination coordinate (dest_x, dest_y) that is 1 pixel in front of it in the direction it is facing.
        switch (this->getDirection())
        {
            //if the zombie is facing up
            // for all the cases check If the movement to (dest_x, dest_y) would not cause the dumb zombie’s bounding box to intersect with the bounding box14 of any wall, person o other zombieobjects, then
            case up:
               if(getWorld()->isBlocked(this->getX(), this->getY()+1, this))
               {
                   this->moveTo(this->getX(), this->getY()+1);
                   m_movementPlan--;
               }
                else
                    m_movementPlan=0;
                break;
            case down:
                if(getWorld()->isBlocked(this->getX(), this->getY()-1, this))
                {
                    this->moveTo(this->getX(), this->getY()-1);
                    m_movementPlan--;
                }
                else
                    m_movementPlan=0;
                break;
            case right:
                if(getWorld()->isBlocked(this->getX()+1, this->getY(), this))
                {
                    this->moveTo(this->getX()+1, this->getY());
                    m_movementPlan--;
                }
                else
                    m_movementPlan=0;
                break;
            case left:
                if(getWorld()->isBlocked(this->getX()-1, this->getY(), this))
                {
                    this->moveTo(this->getX()-1, this->getY());
                    m_movementPlan--;
                }
                
                break;
            
        }//end of switch
//        m_movementPlan=0;
    
   
    
}
DumbZombies:: ~DumbZombies()
{}
bool DumbZombies :: isZombie()
{
    return true;
}
bool DumbZombies :: levelHasZombie()
{
    return true;
}
bool DumbZombies :: blockActors(double point_x, double point_y)
{
    //calculate the center of the current wall and the point passed in
    int pointX_center= point_x+ SPRITE_WIDTH/2;
    int pointY_center= point_y + SPRITE_HEIGHT/2;
    int dumbZombieX_center= this->getX() +SPRITE_WIDTH/2;
    int dumbZombieY_center= this->getY() +SPRITE_HEIGHT/2;
    
    // then use the Udulican formula, instead the distance between the centers should be less than 16
    int deltaX= pow((pointX_center - dumbZombieX_center),2);
    int deltaY= pow((pointY_center - dumbZombieY_center),2);
    
    //if that's cse then wall blocks the passed object
    if(deltaX + deltaY < pow(16,2)) return true;
    //otherwise it does not
    return false;
}
//=============================================== end of dumb zombies methods ==================================

//================================================ Smart Zombies ======================================

SmartZombies:: SmartZombies(double startX, double startY, StudentWorld* sWorld)
:Actors(IID_ZOMBIE, startX , startY, right,0,sWorld), m_paralyzedCounter(true), m_movementPlan(0)
{
    //Smart Zombie start alive
    this->setAlive(true);
}

void SmartZombies:: flameDamagable(double point_x, double point_y)
{
   
    // then use the Udulican formula, instead the distance between the centers should be less than 16
    double deltaX= pow((point_x - this->getX()),2);
    double deltaY= pow((point_y - this->getY()),2);
    
    //if that's cse then wall blocks the passed object
    if(deltaX + deltaY <= pow(10,2))
    {
        //Set its own state to dead
        this->setAlive(false);
        //o Play a sound effect to indicate that the smart zombie died: SOUND_ZOMBIE_DIE.
        getWorld()->playSound(SOUND_ZOMBIE_DIE);
        //Increase the player’s score by 2000 points.
        getWorld()->increaseScore(2000);
    }
}
void SmartZombies:: doSomething()
{
   
//    1. The smart zombie must check to see if it is currently alive. If not, then its
//        doSomething() method must return immediately – none of the following steps
//        should be performed
    if(!isAlive())
        return;
//    2. The smart zombie will become paralyzed every other tick trying to figure out
//    what to do. The 2nd, 4th, 6th, etc., calls to doSomething() for a smart zombie are the
//        “paralysis” ticks for which doSomething() must return immediately – none of the
//            following steps should be performed
    m_paralyzedCounter = !m_paralyzedCounter;
    if(m_paralyzedCounter)
        return;
    //  3. The dumb zombie must check to see if a person (either Penelope or one of the citizens on the level) is in front of it in the direction it is facing:
    //switch case to function depending on the direction the dumbzombie is facing
    switch (this-> getDirection())
    {
            //if the zombie is facing up
        case up:
            //The dumb zombie must check to see if a person (either Penelope or one of the citizens on the level) is in front of it in the direction it is facing:
            if(getWorld()->isPersonInFrontOfZommbie(this->getX(), this->getY() + SPRITE_HEIGHT))
            {
                //If there is a person whose Euclidean distance from the vomit coordinates is less than or equal to 10 pixels,
                if( getWorld()->isPersonWhoseEuclideanDistanceFromVomitCoordinates(this->getX(), this->getY()+SPRITE_HEIGHT))
                {
                    //then there is a 1 in 3 chance that the dumb zombie will vomit. If the zombie choses to vomit, it will
                    if(1==randInt(1, 3))
                    {
                        //i. Introduce a vomit object into the game at the vomit coordinates.
                        getWorld()->introduceVomitAtThisPoint(this->getX(), this->getY()+SPRITE_HEIGHT);
                        //Play the sound SOUND_ZOMBIE_VOMIT.
                        getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
                        //Immediately return and do nothing more this tick.
                        return;
                    }
                }
            }
            break;
        case down:
            if(getWorld()->isPersonInFrontOfZommbie(this->getX(), this->getY() - SPRITE_HEIGHT))
            {
                //If there is a person whose Euclidean distance from the vomit coordinates is less than or equal to 10 pixels,
                if( getWorld()->isPersonWhoseEuclideanDistanceFromVomitCoordinates(this->getX(), this->getY()-SPRITE_HEIGHT))
                {
                    //then there is a 1 in 3 chance that the dumb zombie will vomit. If the zombie choses to vomit, it will
                    if(1==randInt(1, 3))
                    {
                        //i. Introduce a vomit object into the game at the vomit coordinates.
                        getWorld()->introduceVomitAtThisPoint(this->getX(), this->getY()-SPRITE_HEIGHT);
                        //Play the sound SOUND_ZOMBIE_VOMIT.
                        getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
                        //Immediately return and do nothing more this tick.
                        return;
                    }
                }
            }
            break;
        case right:
            if(getWorld()->isPersonInFrontOfZommbie(this->getX() +SPRITE_WIDTH, this->getY()))
            {
                //If there is a person whose Euclidean distance from the vomit coordinates is less than or equal to 10 pixels,
                if( getWorld()->isPersonWhoseEuclideanDistanceFromVomitCoordinates(this->getX()+SPRITE_HEIGHT, this->getY()))
                {
                    //then there is a 1 in 3 chance that the dumb zombie will vomit. If the zombie choses to vomit, it will
                    if(1==randInt(1, 3))
                    {
                        //i. Introduce a vomit object into the game at the vomit coordinates.
                        getWorld()->introduceVomitAtThisPoint(this->getX()+SPRITE_HEIGHT, this->getY());
                        //Play the sound SOUND_ZOMBIE_VOMIT.
                        getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
                        //Immediately return and do nothing more this tick.
                        return;
                    }
                }
            }
            break;
        case left:
            if(getWorld()->isPersonInFrontOfZommbie(this->getX() -SPRITE_WIDTH, this->getY()))
            {
                //If there is a person whose Euclidean distance from the vomit coordinates is less than or equal to 10 pixels,
                if( getWorld()->isPersonWhoseEuclideanDistanceFromVomitCoordinates(this->getX()-SPRITE_HEIGHT, this->getY()))
                {
                    //then there is a 1 in 3 chance that the dumb zombie will vomit. If the zombie choses to vomit, it will
                    if(1==randInt(1, 3))
                    {
                        //i. Introduce a vomit object into the game at the vomit coordinates.
                        getWorld()->introduceVomitAtThisPoint(this->getX()-SPRITE_HEIGHT, this->getY());
                        //Play the sound SOUND_ZOMBIE_VOMIT.
                        getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
                        //Immediately return and do nothing more this tick.
                        return;
                    }
                }
            }
            break;
    }//end of switch
    //The dumb zombie will check to see if it needs a new movement plan because its current movement plan distance has reached zero. If so, the dumb zombie will:
    //Pick a new random movement plan distance in the range 3 through 10 inclusive.
    if(m_movementPlan==0)
    {
        m_movementPlan= randInt(3, 10);
        //    b. Select the person (Penelope or a citizen) closest to the smart zombie, i.e., the one whose Euclidean distance from the zombie is the smallest. If more than one person is the same smallest distance away, select one of them.
        Actors* nearestPerson= getWorld()-> findClosestPersonToSmartZombie(this->getX(), this->getY());
        // i. If the distance to the selected nearest person is more than 80 pixels away, the direction is chosen from up, down, left, and right.
        if( getWorld()-> findTheDistanceFromSmartZombieToPerson(this->getX(), this->getY(), nearestPerson) > 80)
            //Set its direction to a random direction:
            this->setDirection(getWorld()->randomDir());
        //Otherwise, the nearest person is less than or equal to 80 pixels away, the direction is chosen to be one that would cause the zombie to get closer to the person
        else
        {
            //If the zombie is on the same row or column as the person, choose the (only) direction that gets the zombie closer
            if(getWorld()-> smartZombieSameRowOrColWithThePerson(this->getX(), this->getY(), nearestPerson))
            {
                this->setDirection(getWorld()-> pickDirectionToGetCloserToPerson(this->getX(), this->getY(), nearestPerson));
            }
            else
            {
                // 2. Otherwise, choose randomly between the two directions (one horizontal and one vertical) that get the zombie closer.
                int randomInt = randInt(0, 1);
                //if randmoly get zero, pick horizontal direction
                if(randomInt==0)
                {
                    ///==================NOT RIGHT ================ FIX THIS ===============
                    Direction dir= getWorld()->pickRandomDirForSmartZombieToFollowPerson(this->getX(),this->getY(),0, nearestPerson );
                    switch (dir)
                    {
                        case right:
                            this->setDirection(right);
//                            dest_x=this->getX()+1;
//                            dest_y=this->getY();
                            break;
                        case left:
                            this->setDirection(left);
//                            dest_x=this->getX()-1;
//                            dest_y=this->getY();
                            break;
                    }
                }
                    //if blocked, pick a vertical direction
                else
                {
                    Direction dir= getWorld()->pickRandomDirForSmartZombieToFollowPerson(this->getX(),this->getY(),1, nearestPerson );
                    switch (dir)
                    {
                        case up:
                            this->setDirection(up);
//                            dest_x=this->getX();
//                            dest_y=this->getY()+1;
                            break;
                        case down:
                            this->setDirection(down);
//                            dest_x=this->getX();
//                            dest_y=this->getY()-1;
                            break;
                    }
                }
            }
        }
    }
    
    switch (this->getDirection())
    {
        case up:
            //if not blocked in that direction
            if(getWorld()->isBlocked(this->getX(), this->getY()+1, this))
            {
                // 2. Move 2 pixels in that direction using the GraphObject class's moveTo() method.
                this->moveTo(this->getX(), this->getY()+1);
                //c. Decrease the movement plan distance by
                m_movementPlan--;
            }
            else
                m_movementPlan=0;
            break;
        case down:
            //if not blocked in that direction
            if(getWorld()->isBlocked(this->getX(), this->getY()-1, this))
            {
                // 2. Move 2 pixels in that direction using the GraphObject class's moveTo() method.
                this->moveTo(this->getX(), this->getY()-1);
                //c. Decrease the movement plan distance by
                m_movementPlan--;
            }
            else
                m_movementPlan=0;
            break;
        case right:
            //if not blocked in that direction
            if(getWorld()->isBlocked(this->getX()+1, this->getY(), this))
            {
                // 2. Move 2 pixels in that direction using the GraphObject class's moveTo() method.
                this->moveTo(this->getX()+1, this->getY());
                //c. Decrease the movement plan distance by
                m_movementPlan--;
            }
            else
                m_movementPlan=0;
            break;
        case left:
            //if not blocked in that direction
            if(getWorld()->isBlocked(this->getX()-1, this->getY(), this))
            {
                // 2. Move 2 pixels in that direction using the GraphObject class's moveTo() method.
                this->moveTo(this->getX()-1, this->getY());
                //c. Decrease the movement plan distance by
                m_movementPlan--;
            }
            else
                m_movementPlan=0;
            break;
    }
    
 
//    Otherwise, the smart zombie was blocked from moving by another wall, person or zombie, so set the movement plan distance to 0 (which will cause the smart zombie to pick a new direction to move during the next tick).
    
}

SmartZombies:: ~SmartZombies()
{
    
}
//return true as it is a zombie
bool SmartZombies:: isZombie()
{
    return true;
}
bool SmartZombies:: levelHasZombie()
{
    return true;
}

bool SmartZombies::blockActors(double point_x, double point_y)
{
    //calculate the center of the current wall and the point passed in
    int pointX_center= point_x+ SPRITE_WIDTH/2;
    int pointY_center= point_y + SPRITE_HEIGHT/2;
    int smartZombieX_center= this->getX() +SPRITE_WIDTH/2;
    int smartZombieY_center= this->getY() +SPRITE_HEIGHT/2;
    
    // then use the Udulican formula, instead the distance between the centers should be less than 16
    int deltaX= pow((pointX_center - smartZombieX_center),2);
    int deltaY= pow((pointY_center - smartZombieY_center),2);
    
    //if that's cse then wall blocks the passed object
    if(deltaX + deltaY < pow(16,2)) return true;
    //otherwise it does not
    return false;
}
//=============================================== end of Smart zombies methods ==================================

//================================================ Landmines======================================
Landmines:: Landmines (double startX, double startY, StudentWorld* sWorld)
:Actors(IID_LANDMINE, startX , startY, right,1,sWorld), m_safteyTick(30), m_activeState(false)
{
    this->setAlive(true);
}
void Landmines:: doSomething()
{
    //1. It must check to see if it is currently alive. If not, then doSomething() must return immediately – none of the following steps should be performed.
    if(!isAlive())
        return;
    //If the landmine is not yet active then
    if(m_activeState==false)
    {
        
        //a. It must decrement the number of safety ticks left.
        m_safteyTick--;
        //. If the number of safety ticks is zero, the landmine becomes active.
        if(m_safteyTick==0)
        {
             m_activeState=true;
             //c. The doSomething() method must return immediately, doing nothing more during this tick.
            return;
        }
    }
    //The landmine must determine if it overlaps with a citizen or Penelope. If so, then the landmine must:
    else if(getWorld()-> doesOverlapsWithcitizenPenelope(this))
    {
        //Set its state to dead
        this->setAlive(false);
        //b. Play a sound effect to indicate that the landmine exploded: SOUND_LANDMINE_EXPLODE.
        getWorld()->playSound(SOUND_LANDMINE_EXPLODE);
        // introduce a flame object
        getWorld()->introduceFlameObject(this->getX(), this->getY(),up);
        //d. Introduce flame objects in the eight adjacent slots around the landmine (north, northeast, east, southeast, south, southwest, west, northwest). Each such
//        adjacent spot must exactly SPRITE_WIDTH pixels away horizontally and/or SPRITE_HEIGHT pixels away vertically. (SPRITE_WIDTH and SPRITE_HEIGHT are both 16.) So if the landmine goodie were at position (100, 100), the northwest flame would be added at (84, 116), the east goodie at (116, 100), the southeast goodie at (116, 84), etc.
        //(north
        getWorld()->introduceFlameObject(this->getX(), this->getY() +SPRITE_HEIGHT,up);
        //northEast
        getWorld()->introduceFlameObject(this->getX()+SPRITE_WIDTH, this->getY() +SPRITE_HEIGHT,up);
        //east
        getWorld()->introduceFlameObject(this->getX() +SPRITE_WIDTH, this->getY(),up);
        //south East
        getWorld()->introduceFlameObject(this->getX()+SPRITE_WIDTH, this->getY()-SPRITE_HEIGHT,up);
        //south
        getWorld()->introduceFlameObject(this->getX(), this->getY() -SPRITE_HEIGHT,up);
        //SOUTH WEST
        getWorld()->introduceFlameObject(this->getX()-SPRITE_WIDTH, this->getY()-SPRITE_HEIGHT,up);
        //WEST
        getWorld()->introduceFlameObject(this->getX() -SPRITE_WIDTH, this->getY(),up);
        //north west
        getWorld()->introduceFlameObject(this->getX() -SPRITE_WIDTH, this->getY() +SPRITE_HEIGHT,up);
        //e. Introduce a pit object at the same (x,y) location as the landmine.
        getWorld()->introducePitObject(this->getX(), this->getY());
    }
    
}
Landmines::  ~Landmines ()
{
    
}
void Landmines:: flameDamagable(double point_x, double point_y)
{
    
    // then use the Udulican formula, instead the distance between the centers should be less than 10
    double deltaX= pow((point_x - this->getX()),2);
    double deltaY= pow((point_y - this->getY()),2);
    
    //if that's cse then wall blocks the passed object
    if(deltaX + deltaY <= pow(10,2))
    {
        //Set its state to dead
        this->setAlive(false);
        //Play a sound effect to indicate that the landmine exploded: SOUND_LANDMINE_EXPLODE.
        getWorld()->playSound(SOUND_LANDMINE_EXPLODE);
        // introduce a flame object
        getWorld()->introduceFlameObject(this->getX(), this->getY(),up);
        //d. Introduce flame objects in the eight adjacent slots around the landmine (north, northeast, east, southeast, south, southwest, west, northwest). Each such
        //        adjacent spot must exactly SPRITE_WIDTH pixels away horizontally and/or SPRITE_HEIGHT pixels away vertically. (SPRITE_WIDTH and SPRITE_HEIGHT are both 16.) So if the landmine goodie were at position (100, 100), the northwest flame would be added at (84, 116), the east goodie at (116, 100), the southeast goodie at (116, 84), etc.
        //(north
        getWorld()->introduceFlameObject(this->getX(), this->getY() +SPRITE_HEIGHT,up);
        //northEast
        getWorld()->introduceFlameObject(this->getX()+SPRITE_WIDTH, this->getY() +SPRITE_HEIGHT,up);
        //east
        getWorld()->introduceFlameObject(this->getX() +SPRITE_WIDTH, this->getY(),up);
        //south East
        getWorld()->introduceFlameObject(this->getX()+SPRITE_WIDTH, this->getY()-SPRITE_HEIGHT,up);
        //south
        getWorld()->introduceFlameObject(this->getX(), this->getY() -SPRITE_HEIGHT,up);
        //SOUTH WEST
        getWorld()->introduceFlameObject(this->getX()-SPRITE_WIDTH, this->getY()-SPRITE_HEIGHT,up);
        //WEST
        getWorld()->introduceFlameObject(this->getX() -SPRITE_WIDTH, this->getY(),up);
        //north west
        getWorld()->introduceFlameObject(this->getX() -SPRITE_WIDTH, this->getY() +SPRITE_HEIGHT,up);
        //e. Introduce a pit object at the same (x,y) location as the landmine.
        getWorld()->introducePitObject(this->getX(), this->getY());
    }
}
bool Landmines:: activeState()
{
    return m_activeState;
}
//=============================================== end of Landmines methods ==================================


//================================================ Pits ======================================
Pits:: Pits(double startX, double startY, StudentWorld* sWorld)
:Actors(IID_PIT, startX , startY, right,0,sWorld)
{}
void Pits:: doSomething()
{
//    A pit must be given an opportunity to do something during every tick (in its doSomething() method). When given an opportunity to do something during a tick, the pit will cause any person or zombie that overlaps with it to be destroyed (they fall into the pit). When the person/zombie is destroyed, it must behave just as it were damaged by a flame (e.g., if a dumb zombie falls into a pit, the player gets 1000 points, the game plays a dying noise, etc.; if Penelope falls into a pit the current level will end; a citizen falling into a pit dies, and the player loses 1000 points, etc.).
    
    //check if the pit overlaps with any actor
    return;
}
Pits:: ~Pits()
{}
//=============================================== end of Pits methods ==================================

//================================================ Flames ======================================
Flames:: Flames(double startX, double startY, Direction dir,StudentWorld* sWorld)
: Actors(IID_FLAME, startX , startY, dir ,0,sWorld), m_creationCount(0)
{
    //A flame object starts in an “alive” state.
    this->setAlive(true);
}
void Flames:: doSomething()
{
    m_creationCount++;
    //1. It must check to see if it is currently alive. If not, then doSomething() must return immediately – none of the following steps should be performed.
    if(!isAlive())
        return;
    //After exactly two ticks from its creation
    if(m_creationCount==2)
    {
        //the flame must set its state to dead so it can be destroyed and removed from the level by the StudentWorld object
        this->setAlive(false);
            return;
    }
//    3. Otherwise, the flame will damage all damageable objects that overlap8 with the flame. The following objects are all damageable and must react to being damaged in the appropriate way: Penelope, citizens, all types of goodies, landmines, and all types of zombies.
    getWorld()->flameDamagesWhenOverlapsWithTheseObjecr(this);
}
Flames:: ~Flames()
{}
//=============================================== end of Flames methods ==================================


//================================================ Vomit ======================================
Vomit::Vomit(double startX, double startY, StudentWorld* sWorld)
:Actors(IID_VOMIT, startX , startY, right,0,sWorld), m_creationCount(0)
{
    this->setAlive(true);
}
void Vomit:: doSomething()
{
    m_creationCount++;
    // It must check to see if it is currently alive. If not, then doSomething() must return immediately – none of the following steps should be performed.
    if(!isAlive())
        return;
    //After exactly two ticks from its creation
    if(m_creationCount==2)
    {
        //the flame must set its state to dead so it can be destroyed and removed from the level by the StudentWorld object
        this->setAlive(false);
        return;
    }
   // Otherwise, the vomit will infect any infectable object that overlaps with the vomit. The following objects are infectable and must react to being infected in the appropriate way: Penelope and citizens.
    getWorld()->vomitOverlapsWithcitizenPenelopeToInfect(this);
    
}
Vomit:: ~Vomit()
{}
//Vomit is not blocked by an exit.

//=============================================== end of Vomit methods ==================================

//================================================ VaccineGoodies ======================================

VaccineGoodies:: VaccineGoodies(double startX, double startY, StudentWorld* sWorld)
:Actors(IID_VACCINE_GOODIE, startX , startY, right,1,sWorld)
{
    this->setAlive(true);
}
void VaccineGoodies:: doSomething()
{
    // It must check to see if it is currently alive. If not, then doSomething() must return immediately – none of the following steps should be performed.
    if(!isAlive())
        return;
    // The vaccine goodie must determine if it overlaps with Penelope. If so, then the vaccine goodie must
    if(getWorld()->doesOverlapWithPenelope( this-> getX() , this->getY()))
    {
       // a. Inform the StudentWorld object that the user is to receive 50 points.
        getWorld()->increaseScore(50);
        //b. Set its state to dead (so that it will be removed from the game by the StudentWorld object at the end of the current tick).
        this->setAlive(false);
        //c. Play a sound effect to indicate that Penelope picked up the goodie: SOUND_GOT_GOODIE.
        getWorld()->playSound(SOUND_GOT_GOODIE);
        //d. Inform the StudentWorld object that Penelope is to receive one dose of vaccine.
        getWorld()->incrementVaccine(1);
    }
    
}
VaccineGoodies:: ~VaccineGoodies()
{}
 void VaccineGoodies:: flameDamagable(double point_x, double point_y)
{
    // then use the Udulican formula, instead the distance between the centers should be less than 16
    double deltaX= pow((point_x - this->getX()),2);
    double deltaY= pow((point_y - this->getY()),2);
    //if that's cse then wall blocks the passed object
    if(deltaX + deltaY <= pow(10,2))
        this->setAlive(false);
}
//=============================================== end of VaccineGoodies methods ==================================

//================================================ GasCanGoodies ======================================

GasCanGoodies:: GasCanGoodies(double startX, double startY, StudentWorld* sWorld)
:Actors(IID_GAS_CAN_GOODIE, startX , startY, right,1,sWorld)
{
    this->setAlive(true);
}
void GasCanGoodies:: doSomething()
{
   // 1. It must check to see if it is currently alive. If not, then doSomething() must return immediately – none of the following steps should be performed.
    if(!isAlive())
        return;
   // 2. The gas can goodie must determine if it overlaps with Penelope. If so, then the gas can goodie must:
    if(getWorld()->doesOverlapWithPenelope(this->getX(), this->getY()))
    {
        //a. Inform the StudentWorld object that the user is to receive 50 points.
        getWorld()->increaseScore(50);
        //b. Set its state to dead (so that it will be removed from the game by the StudentWorld object at the end of the current tick).
        this->setAlive(false);
        //c. Play a sound effect to indicate that Penelope picked up the goodie: SOUND_GOT_GOODIE.
        getWorld()->playSound(SOUND_GOT_GOODIE);
        //d. Inform the StudentWorld object that Penelope is to receive 5 charges for her flamethrower.
        getWorld()->incrementFlamethrowerCharges(5);
    }
}
GasCanGoodies:: ~GasCanGoodies()
{}
void GasCanGoodies:: flameDamagable(double point_x, double point_y)
{
    // then use the Udulican formula, instead the distance between the centers should be less than 16
    double deltaX= pow((point_x - this->getX()),2);
    double deltaY= pow((point_y - this->getY()),2);
    //if that's cse then wall blocks the passed object
    if(deltaX + deltaY <= pow(10,2))
        this-> setAlive(false);
}
//=============================================== end of GasCanGoodies methods ==================================

//================================================ LandminesGoodies ======================================

LandminesGoodies::LandminesGoodies(double startX, double startY, StudentWorld* sWorld)
:Actors( IID_LANDMINE_GOODIE, startX , startY, right,1,sWorld  )
{
    this->setAlive(true);
}

void LandminesGoodies:: doSomething()
{
    // 1. It must check to see if it is currently alive. If not, then doSomething() must return immediately – none of the following steps should be performed.
    if(!isAlive())
        return;
    // 2. The gas can goodie must determine if it overlaps with Penelope. If so, then the gas can goodie must:
    if(getWorld()->doesOverlapWithPenelope(this->getX(), this->getY()))
    {
        //a. Inform the StudentWorld object that the user is to receive 50 points.
        getWorld()->increaseScore(50);
        //b. Set its state to dead (so that it will be removed from the game by the StudentWorld object at the end of the current tick).
        this->setAlive(false);
        //c. Play a sound effect to indicate that Penelope picked up the goodie: SOUND_GOT_GOODIE.
        getWorld()->playSound(SOUND_GOT_GOODIE);
       // d. Inform Inform the StudentWorld object that Penelope is to receive 2 landmines.
        getWorld()->incrementLandmines(2);
    }
    
}
LandminesGoodies:: ~LandminesGoodies()
{}
void LandminesGoodies:: flameDamagable(double point_x, double point_y)
{
    // then use the Udulican formula, instead the distance between the centers should be less than 16
    double deltaX= pow((point_x - this->getX()),2);
    double deltaY= pow((point_y - this->getY()),2);
    //if that's cse then wall blocks the passed object
    if(deltaX + deltaY <= pow(10,2))
        this->setAlive(false);
}
//=============================================== end of LandminesGoodies methods ==================================

//================================================ Citizen ======================================
Citizen:: Citizen(double startX, double startY, StudentWorld* sWorld)
:Actors(IID_CITIZEN, startX , startY, right,0,sWorld ), m_infectionCount(0), m_paralyzedCounter(true)
{
    //when construct a citzen, he is not infected
    this->setInfection(false);
    //citizen starts alive
    this->setAlive(true);
}
void Citizen:: flameDamagable( double point_x, double point_y)
{
    // then use the Udulican formula, instead the distance between the centers should be less than 16
    double deltaX= pow((point_x - this->getX()),2);
    double deltaY= pow((point_y - this->getY()),2);
    //if that's cse then wall blocks the passed object
    if(deltaX + deltaY <= pow(10,2))
    {
       //Set its own state to dead
        this->setAlive(false);
        //o Play a sound effect to indicate that the citizen died: SOUND_CITIZEN_DIE.
        getWorld()->playSound(SOUND_CITIZEN_DIE);
        //Decrease the player’s score by 1000 points.
        getWorld()->increaseScore(-1000);
    }
}
void Citizen:: doSomething()
{
    
//    The citizen must check to see if it is currently alive. If not, then its doSomething()
//        method must return immediately – none of the following steps should be
//        performed.
    if(!isAlive())
        return;
    if(isInfected())
    {
        m_infectionCount++;
        if(m_infectionCount==500)
        {
            //Set its state to dead (so that it will be removed from the game by the StudentWorld object at the end of the current tick).
            this->setAlive(false);
            //Play a SOUND_ZOMBIE_BORN sound effect
            getWorld()->playSound(SOUND_ZOMBIE_BORN);
            //Decrease the player’s score by 1000 for failing to save this citizen (the player’s score could go negative!)
            
            getWorld()->increaseScore(-1000);
            //Introduce a new zombie object into the same (x,y) coordinate as the former citizen by adding it to the StudentWorld object:
            getWorld()->addNewZombie(this->getX(), this->getY());
            //Immediately return (since the citizen is now dead!)
            return;
        }
    }
    //            Otherwise, the citizen will become paralyzed every other tick trying to figure out
    //            what to do. The 2nd, 4th, 6th, etc., calls to doSomething() for a citizen are the
    //                “paralysis” ticks for which doSomething() must return immediately – none of the
    //                    following steps should be performed.
    m_paralyzedCounter=!m_paralyzedCounter;
    if(m_paralyzedCounter)
        return;

    //The citizen must determine its distance to Penelope: dist_p
    double dist_p= getWorld()->distanceToPenelope(this->getX(), this->getY());
    //The citizen must determine its distance to the nearest zombie: dist_z
    double dist_z= getWorld()->distanceToNearestZombie(this->getX(), this->getY());
    double dest_x,dest_y;
//    If dist_p < dist_z or no zombies exist in the level (so dist_z is irrelevant), and the
//    citizen's Euclidean distance from Penelope is less than or equal to 80 pixels (so
//    the citizen wants to follow Penelope):
    if((dist_p < dist_z ||  !getWorld()->zombieExist() ) && getWorld()->euclideanDistanceFromPenelope(this->getX(), this->getY()))
    {
        //If the citizen is on the same row or column as Penelope:
        if(getWorld()->isCitizenOnTheSameRowOrColumnWithPenelope(this->getX(), this->getY()))
        {
            //find out what direction citizen should face
            Direction dir= getWorld()->findWhatDirectionCitizenShouldFaceToFollowPenelope(this->getX(), this->getY());
            
            //set the dest of citizen based on where it is facing to
            if(dir==up)
            {
                //citizen can move up
                dest_x=this->getX();
                dest_y=this->getY()+2;
            }
            if(dir==down)
            {
                dest_x=this->getX();
                dest_y=this->getY()-2;
            }
            if(dir==right)
            {
                dest_x=this->getX()+2;
                dest_y=this->getY();
            }
            if(dir==left)
            {
                dest_x=this->getX()-2;
                dest_y=this->getY();
            }
//         If the citizen can move 2 pixels in the direction toward Penelope  without being blocked16 (by another citizen, Penelope, a zombie, or a wall), the citizen will
            if(getWorld()->isBlocked(dest_x, dest_y, this))
            {
               // 1. Set its direction to be facing toward Penelope.
                setDirection(dir);
                // 2. Move 2 pixels in that direction using the GraphObject class's moveTo() method.
                this->moveTo(dest_x, dest_y);
               // 3. Immediately return and do nothing more during the current tick.
                return;
            }
        }
        //If the citizen is not on the same row or column as Penelope, determine the one horizontal and the one vertical direction that would get the citizen closer to Penelope. Then
        else
        {
            int randomInt = randInt(0, 1);
            //if randmoly get zero, pick horizontal direction
            if(randomInt==0)
            {
                Direction dir= getWorld()->determineOneHorizontalOneVerticalDirectionRandomly(this->getX(), this->getY(), 0);
                switch (dir)
                {
                    case right:
                        dest_x=this->getX()+2;
                        dest_y=this->getY();
                        break;
                    case left:
                        dest_x=this->getX()-2;
                        dest_y=this->getY();
                        break;
                }
                //if not blocked in that direction
                if(getWorld()->isBlocked(dest_x, dest_y, this))
                {
                    // 1. Set its direction to be facing toward Penelope.
                    setDirection(dir);
                    // 2. Move 2 pixels in that direction using the GraphObject class's moveTo() method.
                    this->moveTo(dest_x, dest_y);
                    // 3. Immediately return and do nothing more during the current tick.
                    return;
                }
                //if blocked, pick a vertical direction
                else
                {
                    Direction dir= getWorld()->determineOneHorizontalOneVerticalDirectionRandomly(this->getX(), this->getY(), 1);
                    switch (dir)
                    {
                        case up:
                            dest_x=this->getX();
                            dest_y=this->getY()+2;
                            break;
                        case down:
                            dest_x=this->getX();
                            dest_y=this->getY()-2;
                            break;
                    }
                    //if not blocked in that direction
                    if(getWorld()->isBlocked(dest_x, dest_y, this))
                    {
                        // 1. Set its direction to be facing toward Penelope.
                        setDirection(dir);
                        // 2. Move 2 pixels in that direction using the GraphObject class's moveTo() method.
                        this->moveTo(dest_x, dest_y);
                        // 3. Immediately return and do nothing more during the current tick.
                        return;
                    }
                }
            }
            //if randomly got 1, pick the vertical direction
            else
            {
                Direction dir= getWorld()->determineOneHorizontalOneVerticalDirectionRandomly(this->getX(), this->getY(), 1);
                switch (dir)
                {
                    case up:
                        dest_x=this->getX();
                        dest_y=this->getY()+2;
                        break;
                    case down:
                        dest_x=this->getX();
                        dest_y=this->getY()-2;
                        break;
                }
                //if not blocked in that direction
                if(getWorld()->isBlocked(dest_x, dest_y, this))
                {
                    // 1. Set its direction to be facing toward Penelope.
                    setDirection(dir);
                    // 2. Move 2 pixels in that direction using the GraphObject class's moveTo() method.
                    this->moveTo(dest_x, dest_y);
                    // 3. Immediately return and do nothing more during the current tick.
                    return;
                }
                //if blocked in that diretion
                else
                {
                    Direction dir= getWorld()->determineOneHorizontalOneVerticalDirectionRandomly(this->getX(), this->getY(), 0);
                    switch (dir)
                    {
                        case right:
                            dest_x=this->getX()+2;
                            dest_y=this->getY();
                            break;
                        case left:
                            dest_x=this->getX()-2;
                            dest_y=this->getY();
                            break;
                    }
                        //if not blocked in that direction
                    if(getWorld()->isBlocked(dest_x, dest_y, this))
                    {
                        // 1. Set its direction to be facing toward Penelope.
                        setDirection(dir);
                        // 2. Move 2 pixels in that direction using the GraphObject class's moveTo() method.
                        this->moveTo(dest_x, dest_y);
                        // 3. Immediately return and do nothing more during the current tick.
                        return;
                    }
                }
            }
        }
    }
   // If there is a zombie whose Euclidean distance from the citizen is less than or equal to 80 pixels, the citizen wants to run away, so:
    else if( getWorld() -> euclideanDistanceFromCitizenToZombie(this->getX(), this->getY()))
    {
       // a. For each of the four directions up, down, left and right, the citizen must:
//        for(Direction dir=0; dir<4; dir++)
//        {
            //checking for up
//            if(dir==0)
//            {
                if(getWorld()->isBlocked(this->getX(), this->getY()+2, this))
                {
                    //if moving to the new location make it away from the new
                    if(getWorld()->distanceToNearestZombie(this->getX(), this->getY()) < getWorld()->distanceToNearestZombie(this->getX(), this->getY()+2))
                    {
                        //Set the citizen’s direction to the direction that will take it furthest away from the nearest zombie
                        setDirection(up);
                        //Move 2 pixels in that direction using the GraphObject class's moveTo() method
                        this->moveTo(this->getX(), this->getY()+2);
                        //Immediately return and do nothing more during the current tick.
                        return;
                    }
                }
//                else
//                    // If the citizen is blocked from moving there, it ignores this direction.
//                    continue;
//            }
            //checking for down
//            if(dir ==1)
//            {
                else if(getWorld()->isBlocked(this->getX(), this->getY()-2, this))
                {
                    //if moving to the new location make it away from the new
                    if(getWorld()->distanceToNearestZombie(this->getX(), this->getY()) < getWorld()->distanceToNearestZombie(this->getX(), this->getY()-2))
                    {
                        //Set the citizen’s direction to the direction that will take it furthest away from the nearest zombie
                        setDirection(down);
                        //Move 2 pixels in that direction using the GraphObject class's moveTo() method
                        this->moveTo(this->getX(), this->getY()-2);
                        //Immediately return and do nothing more during the current tick.
                        return;
                    }
                }
//                else
//                    // If the citizen is blocked from moving there, it ignores this direction.
//                    continue;
//            }
            //checking for right
//            if(dir ==2)
//            {
                if(getWorld()->isBlocked(this->getX()+2, this->getY(), this))
                {
                    ///if moving to the new location make it away from the new
                    if(getWorld()->distanceToNearestZombie(this->getX(), this->getY())< getWorld()->distanceToNearestZombie(this->getX()+2, this->getY()))
                    {
                        //Set the citizen’s direction to the direction that will take it furthest away from the nearest zombie
                        setDirection(right);
                        //Move 2 pixels in that direction using the GraphObject class's moveTo() method
                        this->moveTo(this->getX()+2, this->getY());
                        //Immediately return and do nothing more during the current tick.
                        return;
                    }
                }
//                else
//                    // If the citizen is blocked from moving there, it ignores this direction.
//                    continue;
//            }
            //checking for left
//            if(dir ==3)
//            {
                if(getWorld()->isBlocked(this->getX()-2, this->getY(), this))
                {
                    ///if moving to the new location make it away from the new
                    if(getWorld()->distanceToNearestZombie(this->getX(), this->getY())< getWorld()->distanceToNearestZombie(this->getX()-2, this->getY()))
                    {
                        //Set the citizen’s direction to the direction that will take it furthest away from the nearest zombie
                        setDirection(left);
                        //Move 2 pixels in that direction using the GraphObject class's moveTo() method
                        this->moveTo(this->getX()-2, this->getY());
                        //Immediately return and do nothing more during the current tick.
                        return;
                    }
                }
//                else
//                    // If the citizen is blocked from moving there, it ignores this direction.
//                    continue;
//            }
//            If none of the movement options would allow the citizen to get further away from the nearest zombie (e.g., right now it’s 20 pixels away from the nearest zombie, but if it were to move in any of the four directions it would get even closer to some zombie), then doSomething() immediately returns
           
        }
//    }
     return;
}

//What a Citizen Must Do In Other Circumstances
//• A citizen can be damaged by flames. If a flame overlaps17 with a citizen, it will
//kill the citizen. The citizen must:
//o Set its own state to dead (so that it will be removed from the game by the
//                             StudentWorld object at the end of the current tick).
//o Play a sound effect to indicate that the citizen died:
//SOUND_CITIZEN_DIE.
//o Decrease the player’s score by 1000 points.
//• A citizen can be infected by vomit. When vomit overlaps with a citizen, the
//citizen's infection status becomes true.
//• A citizen blocks other objects from moving nearby/onto it. A citizen's bounding
//box must never intersect with that of any other citizen, Penelope, dumb zombie,
//or smart zombie).
//• A Citizen does not block flames.

//destructor
Citizen:: ~Citizen()
{
    
}
//return true of the object is citizwn
bool Citizen:: isCitizen()
{
    return true;
}
bool Citizen::blockActors(double point_x, double point_y)
{
    //calculate the center of the current wall and the point passed in
    int pointX_center= point_x + SPRITE_WIDTH/2;
    int pointY_center= point_y + SPRITE_HEIGHT/2;
    int citizenX_center= this->getX() + SPRITE_WIDTH/2;
    int citizenY_center= this->getY() + SPRITE_HEIGHT/2;
    
    // then use the Udulican formula, instead the distance between the centers should be less than 16
    int deltaX= pow((pointX_center - citizenX_center),2);
    int deltaY= pow((pointY_center - citizenY_center),2);
    
    //if that's cse then wall blocks the passed object
    if(deltaX + deltaY < pow(16,2)) return true;
    //otherwise it does not
    return false;
}
void Citizen:: vomitInfectable(double x, double y)
{
    double deltaX= x - this->getX();
    double deltaY= y - this->getY();
    double result = pow(deltaX, 2) + pow(deltaY, 2);
    if(result<= pow(10, 2))
    {
        //You must play a SOUND_CITIZEN_INFECTED sound any time a citizen is successfully infected by zombie vomit. Note that this sound is played only when the citizen is first covered in vomit, NOT upon subsequent hit by vomit and NOT when they become a zombie; the sample executables currently don't play this sound. Note also that in general a new sound cuts off an old sound, so you might not hear SOUND_CITIZEN_INFECTED being played if its start is quickly followed by a zombie vomiting.
        getWorld()->playSound(SOUND_CITIZEN_INFECTED);
        this->setInfection(true);
    }
    

}
bool Citizen:: isPerson()
{
    return true;
}
//=============================================== end of Citizen methods ==================================
