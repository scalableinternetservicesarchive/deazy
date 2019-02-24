//  StudentWorld.cpp
//  Project 3
//
//  Created by ali mirabzadeh on 2/13/19.
//  Copyright © 2019 AMZ Development. All rights reserved.

#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include "Level.h"
#include <vector>
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
using namespace std;


/*------------------------------ GameWorld.h --------------------------------
//int getLevel() const;
//int getLives() const;
//void decLives();
//void incLives();
//int getScore() const;
//void increaseScore(int howMuch);
//void setGameStatText(string text);
//bool getKey(int& value);
//void playSound(int soundID);
----------------------------POINTS Given -----------------------------------
When Penelope picks up a goodie (a vaccine, gas can, or landmine box): 50 points
• When a citizen makes it safely to the exit: 500 points
• When a dumb zombie is destroyed: 1000 points
• When a a smart zombie is destroyed: 2000 points
• When a citizen becomes a zombie or dies for any reason: −1000 points
*/

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}
StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{}
//init() method that would be called by the framework to initialize all the objects load the level(s)
int StudentWorld::init()
{
    //get the level file to load
    Level lev(assetPath());
    //get the level based what level penelope is on
    //GWSTATUS_PLAYER_WON
    string levelFile = "level0"+ to_string(getLevel()+1)+".txt";
    Level::LoadResult result = lev.loadLevel(levelFile);
    if (result == Level::load_fail_file_not_found)
        return GWSTATUS_LEVEL_ERROR;
    else if (result == Level::load_fail_bad_format)
        return GWSTATUS_LEVEL_ERROR;
    //if succefully load the .txt file
    else if (result == Level::load_success)
    {
        //put the actors and walls in on the field Vector STL
        for(int i=0 ; i< LEVEL_WIDTH; i++)//row
        {
            for(int j=0; j<LEVEL_HEIGHT ; j++)//col
            {
                //get the current char from the level0*.txt and store in ge, from Level.h
                Level::MazeEntry ge = lev.getContentsOf(i,j);
                switch (ge)
                {
                    //based on the object on txt file, construct the object and push it into the vector
                    case Level::player:
                        penelopePtr=new Penelope(SPRITE_WIDTH*i,SPRITE_HEIGHT*j,this);
                        m_level.push_back(penelopePtr);
                        break;
                    case Level::wall:
                        //create a new wall on the level
                        m_level.push_back(new Walls(SPRITE_WIDTH*i,SPRITE_HEIGHT *j,this));
                        break;
                    case Level::vaccine_goodie:
                        m_level.push_back(new VaccineGoodies (SPRITE_WIDTH*i,SPRITE_HEIGHT *j,this));
                        break;
                    case Level::dumb_zombie:
                        m_level.push_back(new DumbZombies(SPRITE_WIDTH*i,SPRITE_HEIGHT *j,this));
                        break;
                    case Level::smart_zombie:
                        m_level.push_back(new SmartZombies(SPRITE_WIDTH*i,SPRITE_HEIGHT *j,this));
                        break;
                    case Level::landmine_goodie:
                        m_level.push_back(new LandminesGoodies(SPRITE_WIDTH*i,SPRITE_HEIGHT *j,this));
                        break;
                    case Level::exit:
                        m_level.push_back(new Exit(SPRITE_WIDTH * i,SPRITE_HEIGHT *j,this));
                        break;
                    case Level::citizen:
                        m_level.push_back(new Citizen(SPRITE_WIDTH*i,SPRITE_HEIGHT *j,this));
                        break;
                    case Level:: gas_can_goodie:
                        m_level.push_back(new GasCanGoodies(SPRITE_WIDTH*i,SPRITE_HEIGHT *j,this));
                        break;
                    case Level:: pit:
                        m_level.push_back(new Pits(SPRITE_WIDTH*i,SPRITE_HEIGHT *j,this));
                        break;
                    case Level::empty:
                         m_level.push_back(nullptr);
                        break;
                }
            }
        }
    }
    //start the game if there was no error
    return GWSTATUS_CONTINUE_GAME;
}
//move() method that will be called by the framework and call each actors to do something, update the level and tells the framework what to do
int StudentWorld::move()
{
    
    
    //iterate through all objects
    for (vector<Actors*>::iterator it = m_level.begin(); it != m_level.end(); it++)
    {
        //if the current object is nullptr, ignore and continue
        if(*it==nullptr) continue;
        // tell all the objects to do Something during the tick to do something (e.g. move)
        (*it)->doSomething();
        
        //if the Penelope is dead, return from move() with GWSTATUS_PLAYER_DIED
        if( penelopePtr->isAlive()==false)
          return GWSTATUS_PLAYER_DIED;
        //if Penelope overlaps with Exit, return the level is finished
//        if(citizne alive && citizen overlap exit)
//            if((*it)->doesOverlap(penelopePtr))
//                return GWSTATUS_FINISHED_LEVEL;
        if((*it)->doesOverlap(penelopePtr))
            return GWSTATUS_FINISHED_LEVEL;
    }
   //Remove newly-dead actors after each tick
//   for (vector<Actors*>::iterator iter = m_level.begin(); iter != m_level.end();)
//    {
//        //if the current actor is dead, remove that actor from the level
//        if ( (*iter)->isAlive() == false)
//        {
//            delete *iter;
//            iter=m_level.erase(iter);
//        }
//        else
//            iter++;
//    }
    //    // Update the game status line
    //    Update Display Text // update the score/lives/level text at screen top
    //    // the player hasn’t completed the current level and hasn’t died, so
    //    // continue playing the current level
    
    
    //    It must ask all of the actors that are currently alive in the game world to do
    //        something (e.g., ask a dumb zombie to move itself, ask a goodie to check if it
    //                   overlaps with Penelope, and if so, grant her something, give Penelope a chance to
    //                   move up, down, left or right, etc.).
    //        a. If an actor does something that causes Penelope to die (e.g., a flame
    //                                                                   overlaps with Penelope, she falls into a pit, she turns into a zombie), then
    //        the move() method should immediately return GWSTATUS_PLAYER_DIED.
    //        b. Otherwise, if the all remaining citizens and Penelope have used the exit
    //            and it’s time to advance to the next level, then the move() method must
    //            return a value of GWSTATUS_FINISHED_LEVEL.
    //    If move() hasn't returned as a result of the above, it must then delete any actors
    //    that have died during this tick (e.g., a dumb zombie that was killed by a flame or a
    //                                     goodie that disappeared because it overlapped with Penelope and was therefore
    //                                     picked up) and remove them from the collection of actors.
    //    3. It must update the status text on the top of the screen with the latest information
    //    (e.g., the user’s current score, the number of landmines Penelope has, the current
    //     level, etc.).
    
      return GWSTATUS_CONTINUE_GAME;
}
//cleanUp() method that would be called by the framework to destroy all the objects
void StudentWorld::cleanUp()
{
    //iterate through all the objects
    for (vector<Actors*>::iterator it = m_level.begin(); it != m_level.end(); it++)
    {
        //delete the current object
        delete *it;
        //then make the it pointer to points the next object while erasing the current one
        it=m_level.erase(it);
    }
}
//Destructor
StudentWorld:: ~StudentWorld()
{
    //call cleanUp() to destrot all the objects
    this->cleanUp();
}

//Determining blocking movement for wall, citizens, Penelope, and zombies
bool StudentWorld:: isBlocked(  int dest_x, int dest_y, Actors *actorPtr)
{
    //iterate through all the objects
    for (vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++ )
    {
        //if the current object is the same as the passed actor OR it is nullptr then  skip
        if( (*iter)==actorPtr || (*iter) == nullptr)
            continue;
        //if it is an objet that has the blockActors methods( walls, zombies, citizens, Penelope), return false as they block the current object
        else if((*iter)->blockActors(dest_x, dest_y))
            return false;
    }
    //otherwise return true
    return true;
}

//void StudentWorld:: displayText()
//{

//}

//check if the passed object is a citizen
void StudentWorld:: addNewZombie(int startX, int startY)
{
    int zombiePercentage= randInt(0, 100);
    for(vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++)
    {
        //if the actor is a citizen
        if((*iter)->isCitizen())
        {
            //There’s a 70% chance a dumb zombie object will be introduced.
            if(zombiePercentage<=70)
                m_level.push_back(new DumbZombies(startX,startY,this));
            else
               //here’s a 30% chance a smart zombie object will be introduced
                m_level.push_back(new SmartZombies(startX,startY,this));
        }
    }
}
//return the distance between the citizen and peneople
int StudentWorld:: distanceToPenelope(int citizenX, int citizenY)
{
    return sqrt(pow(citizenX - penelopePtr->getX(), 2) + pow(citizenY - penelopePtr->getY(), 2));
}
//return the distance between the citizen and nearest zombie
int StudentWorld:: distanceToNearestZombie(int citizenX, int citizenY)
{
    //By default min dist is 240, the largest possible distance on the level
    int minDist=240;
    for(vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++)
    {
        if((*iter)==nullptr) continue;
        if((*iter)->isZombie())
        {
            int zombieX= (*iter)->getX();
            int zombieY=(*iter)->getY();
            //calculate the distance between the citizen and the current zombie
            int tempMinDist= sqrt(pow(zombieX - citizenX, 2) + pow(zombieY - citizenY, 2));
            //if tempMinDist is smaller than minDist
            if(tempMinDist<minDist)
                //store the temp value in minDist
                minDist=tempMinDist;
        }
    }
    return minDist;
}
//detemine Euclidean Distance From Penelope
bool StudentWorld:: euclideanDistanceFromPenelope(int citizenX, int citizenY)
{
    int deltaX= citizenX - penelopePtr->getX();
    int deltaY= citizenY - penelopePtr->getY();
    int result= pow(deltaX,2) + pow(deltaY, 2);
    //if less than 80 pixels, return true
    if(result<= pow(80, 2))
        return true;
    return false;
}
//check if there is at least one zombie on the level
bool StudentWorld:: zombieExist()
{
    //iterate through all the actors
    for(vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++)
    {
        if((*iter)==nullptr) continue;
        //if found one zombie retern true
        if((*iter)->levelHasZombie())
            return true;
    }
    //otherwise, return false as it could not find any
    return false;
}
//check if the passed point which is for a citizen has either the sam y or x, row or col.
 bool StudentWorld:: isCitizenOnTheSameRowOrColumnWithPenelope(int citizenX, int citizenY)
{
    //if the either is the same, return true
    if(citizenX== penelopePtr->getX() || citizenY== penelopePtr->getY())
        return true;
    //otherwise false
    return false;
}
//return a direction that a citizen should face based on Penelope location, called if penelope and citizen are on the same row or col
Direction StudentWorld:: findWhatDirectionCitizenShouldFaceToFollowPenelope(int citizenX, int citizenY)
{
    //if both on the same column
    if(citizenX== penelopePtr->getX())
    {
        //if penelope on right of the citzen
        if(citizenX < penelopePtr->getX())
            return Actors::right;
        return Actors:: left;
    }
    //on the same row
    else
    {
        //if penelope on top the citizen
        if(citizenY < penelopePtr->getY())
            return Actors:: up;
        return Actors:: down;
    }
}
//randmoly pick a direction for a citizen if he is not on the same row or col
Direction StudentWorld:: determineOneHorizontalOneVerticalDirectionRandomly(int citizenX, int citizenY, int randomDirection)
{
    //if the random integer is 0, pick horizontal direction
    if(randomDirection==0)
    {
        if(citizenX < penelopePtr->getX())
            return Actors:: right;
        else
            return Actors:: left;
    }
    //otherwise pick a vertical direction
    else
    {
        if(citizenY < penelopePtr->getY())
            return Actors:: up;
        else
            return Actors:: down;
    }
}
//return true if the Euclidean Distance From Citizen To Zombie is less than 80 pixle
bool StudentWorld:: euclideanDistanceFromCitizenToZombie(int citizenX, int citizenY)
{
    //iterate through all the actors
    for(vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++)
    {
        //if nullptr continue
        if((*iter)==nullptr) continue;
        //if the current actor is zombie
        if((*iter)->isZombie())
        {
            int deltaX= citizenX - (*iter)->getX();
            int deltaY= citizenY - (*iter)->getY();
            int result= pow(deltaX,2) + pow(deltaY, 2);
            //if less than 80 pixels, return true
            if(result<= pow(80, 2))
                return true;
        }
    }
    //if there is no zombie with that specification close to a citizen, return false
    return false;
}
//check if the passed object overlap with penelope
bool StudentWorld:: doesOverlapWithPenelope(int point_x, int point_y)
{
    //calculate the center of the current wall and the point passed in
    int pointX_center= point_x+ SPRITE_WIDTH/2;
    int pointY_center= point_y + SPRITE_HEIGHT/2;
    int penelopeX_center= penelopePtr->getX() +SPRITE_WIDTH/2;
    int penelopeY_center= penelopePtr->getY() +SPRITE_HEIGHT/2;
    
    // then use the Udulican formula, instead the distance between the centers should be less than 16
    int deltaX= pow((pointX_center - penelopeX_center),2);
    int deltaY= pow((pointY_center - penelopeY_center),2);
    
    //if that's cse then wall blocks the passed object
    if(deltaX + deltaY < pow(16,2)) return true;
    //otherwise it does not
    return false;
}
//check if the any person or zombie overlaps with a pit
bool StudentWorld:: doesOverlapWithPit(int pit_x, int pit_y,Actors* actor)
{
    for(vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++)
    {
        //if nullptr continue
        if((*iter)==nullptr) continue;
        //=================== CODE HERE ====================================
    }
    return false;
}
//check if the citizen overlap with exit
bool StudentWorld:: doesExitOverlapWithCitizen(int exit_x, int exit_y)
{
    //iterate through all the actors
    for(vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++)
    {
        //if nullptr continue
        if((*iter)==nullptr) continue;
        if((*iter)->isCitizen())
        {
            
        }
    }
    return false;
}
