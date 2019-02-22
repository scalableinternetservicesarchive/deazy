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

int StudentWorld::move()
{
    //iterate through all Penelope object
    //displayText();
    for (vector<Actors*>::iterator it = m_level.begin(); it != m_level.end(); it++)
    {
        //if the current object is nullptr, ignore and continue, aka do nothing
        if(*it==nullptr) continue;
        // tell all the objects to do Something during the tick to do something (e.g. move)
        (*it)->doSomething();
        //if the Penelope is dead, return from move() with GWSTATUS_PLAYER_DIED
//      if((*it)->isAlive()==false)
//          return GWSTATUS_PLAYER_DIED;
        //if Penelope overlaps with Exit, return the level is finished
        if((*it)->doesOverlap(penelopePtr))
            return GWSTATUS_FINISHED_LEVEL;
    }
    
//Remove newly-dead actors after each tick
//   for (vector<Actors*>::iterator iter = m_level.begin(); iter != m_level.end();)
//    {
//        //if the current actor is dead, remove that actor from the level and
//        if ((*iter)->isAlive() == false)
//            iter=m_level.erase(iter);
//        else
//            iter++;
//    }
    
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
    
    
    //    The move() method must return one of three different values when it returns at the end of
    //    each tick (all are defined in GameConstants.h):
    //    GWSTATUS_PLAYER_DIED
    //    GWSTATUS_CONTINUE_GAME
    //    GWSTATUS_FINISHED_LEVEL
    
    
    //    Here’s pseudocode for how the move() method might be implemented:
    //        int StudentWorld::move()
    //    {
    //        // The term "actors" refers to all zombies, Penelope, goodies,
    //        // pits, flames, vomit, landmines, etc.
    //        // Give each actor a chance to do something, including Penelope
    //        for each of the actors in the game world
    //    {
    //        if (actor[i] is still alive)
    //        {
    //            // tell each actor to do something (e.g. move)
    //            actor[i]->doSomething();
    //            if (Penelope died during this tick)
    //                return GWSTATUS_PLAYER_DIED;
    //            if (Penelope completed the current level)
    //                return GWSTATUS_FINISHED_LEVEL;
    //        }
    //    }
    //    // Remove newly-dead actors after each tick
    //    Remove and delete dead game objects
    //    // Update the game status line
    //    Update Display Text // update the score/lives/level text at screen top
    //    // the player hasn’t completed the current level and hasn’t died, so
    //    // continue playing the current level
      return GWSTATUS_CONTINUE_GAME;
}
//cleanUp() method that would be called by the framework to destroy all the objects
void StudentWorld::cleanUp()
{
    //    When your cleanUp() method is called by our game framework, it means that Penelope
    //    lost a life (e.g., she fell into a pit, turned into a zombie after being infected, or walked
    //                 into a flame she fired herself) or has completed the current level. In this case, every actor
    //    in the entire game (Penelope and every zombie, goodie, projectile, landmine, wall, pit,
    //                        etc.) must be deleted and removed from the StudentWorld’s container of active objects,
    //    resulting in an empty level. If the user has more lives left, our provided code will
    //    subsequently call your init() method to reload and repopulate the level with a new set of
    //    actors, and the level will then continue from scratch.
    //    You must not call the cleanUp() method yourself when Penelope dies. Instead, this
    //    method will be called by our code when init() returns an appropriate status
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
        //if it a an objet that has the blockActors methods( walls, zombies, citizens, Penelope), return false as they block the current object
        else if((*iter)->blockActors(dest_x, dest_y))
            return false;
    }
    //otherwise return true
    return true;
}



//void StudentWorld:: displayText()
//{

//}


