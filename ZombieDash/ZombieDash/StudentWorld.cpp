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
#include <list>
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



Penelope* penelope();
int StudentWorld::init()
{
    //    Initialize the data structures used to keep track of your game’s world.
    //    2. Allocate and insert a Penelope object into the game world as specified in the
    //    current level’s data file.
    //    3. Allocate and insert various wall, pit, goodie, zombie, and exit objects into the
    //    game world as specified in the current level’s data file.
    
    
    //Hint: You will likely want to use our Level class to load the current level specification in
    //    your StudentWorld class’s init() method. The assetPath() and getLevel() methods
    //    that your StudentWorld class inherits from GameWorld might also be useful, along with
    //    the Stringstreams writeup on the class web site!
    Penelope *penelopePtr;
    //get the level file to load
    Level lev(assetPath());
    //string levelFile = assetPath() + "/level0" + char(getLevel())+ ".txt";
    string levelFile = "level01.txt";
    
    Level::LoadResult result = lev.loadLevel(levelFile);
    if (result == Level::load_fail_file_not_found)
        return GWSTATUS_LEVEL_ERROR;
    else if (result == Level::load_fail_bad_format)
        return GWSTATUS_LEVEL_ERROR;
    else if (result == Level::load_success)
    {
        //put the actors and walls in on the field using 2D list STL
        for(int i=0 ; i< 16; i++)//row
        {
            for(int j=0; j<16 ; j++)//col
            {
                //get the current char from the level0*.txt and store in ge
                Level::MazeEntry ge = lev.getContentsOf(i,j);
                switch (ge)
                {
                    //if ge is Penelope
                    case Level::player:
//                        create a new Penelope and put her in penelope pointer STL
                        penelopePtr=new Penelope(SPRITE_WIDTH*i,SPRITE_HEIGHT*j,this);
                        m_level[i][j].push_back(penelopePtr);
                        break;
                    case Level::wall:
                        //create a new wall on the level
                        m_level[i][j].push_back(new Walls(SPRITE_WIDTH*i,SPRITE_HEIGHT *j,this));
                        break;
//                    case Level::vaccine_goodie:
//                        break;
//                    case Level::dumb_zombie:
//                        break;
//                    case Level::smart_zombie:
//                        break;
//                    case Level::landmine_goodie:
//                        break;
                    case Level::exit:
                        m_level[i][j].push_back(new Exit(SPRITE_WIDTH * i,SPRITE_HEIGHT *j,this));
                        break;
//                    case Level::citizen:
//                        break;
//                    case Level:: gas_can_goodie:
//                        break;
//                    case Level:: pit:
//                        break;
                    case Level::empty:
                         m_level[i][j].push_back(nullptr);
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
    for(int i=0 ; i< 16; i++)
    {
        for(int j=0; j<16; j++)
        {
            for (list<Actors*>::iterator it = m_level[i][j].begin(); it != m_level[i][j].end(); it++)
            {
               //if the current object is nullptr, ignore and continue, aka do nothing
                if(*it==nullptr) continue;
                 // tell Penelope to do something (e.g. move)
                (*it)->doSomething();
                //if the Penelope is dead, return from move() with GWSTATUS_PLAYER_DIED
//                if((*it)->isAlive()==false)
//                    return GWSTATUS_PLAYER_DIED;
//                if(it->exit())
//                    return GWSTATUS_FINISHED_LEVEL;
            }
        }
    }
    
//    for(int i=0 ; i< 16; i++)
//    {
//        for(int j=0; j<16 ; j++)
//        {
//            for (list<Actors*>::iterator it = m_level[i][j].begin(); it != m_level[i][j].end(); it++)
//            {
//                // tell Penelope to do something (e.g. move)
//                (*it)->doSomething();
//                //if the Penelope is dead, return from move() with GWSTATUS_PLAYER_DIED
//                //                if((*it)->isAlive()==false)
//                //                    return GWSTATUS_PLAYER_DIED;
//                //                if(it->exit())
//                //                    return GWSTATUS_FINISHED_LEVEL;
//            }
//        }
//    }
    // Remove newly-dead actors after each tick
//    for(int i=0 ; i < VIEW_HEIGHT ; i++)
//    {
//        for(int j=0; j < VIEW_WIDTH ; j++)
//        {
//            for (list<Actors*>::iterator iter = m_level[i][j].begin(); iter != m_level[i][j].end();)
//            {
//                //if the current actor is dead, remove that actor from the level and
//                if ((*iter)->isAlive() == false)
//                {
//                    iter=m_level[i][j].erase(iter);
//                }
//                else
//                    iter++;
//
//            }
//        }
//    }
    
    //displayText();
    
    
    
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
    for (int i = 0; i < VIEW_WIDTH; i++)
    {
        
        for (int j = 0; j < VIEW_HEIGHT; j++)
        {
            for (list<Actors*>::iterator it = m_level[i][j].begin(); it != m_level[i][j].end(); it++)
            {
                delete *it;
            }
        }
    }
    //    The StudentWorld destructor will be called by our game framework when the game is
    //    over. If the game ends prematurely because the player pressed the q key, cleanUp() will
    //    NOT have been called by our framework, so your destructor should call it to make sure
    //    the game shuts down cleanly. In normal gameplay, Penelope may lose her last life or
    //    finish the last level, resulting in cleanUp() being called as for any level ending; a little
    //    later, the StudentWorld destructor is called, which would call cleanUp() again. Make
    //    sure that two consecutive calls to cleanUp() won't do anything undefined. For
    //    example, if cleanUp() deletes an object and leaves a dangling pointer, it could be
    //        disastrous if the second call to cleanUp() tries use that pointer in a delete expression.
}
//Destructor
StudentWorld:: ~StudentWorld()
{
    //call cleanUp()
    this->cleanUp();
}


//Determining blocking movement
bool StudentWorld:: isBlocked( int dest_x, int dest_y)
{
    
    //current object
    for (list<Actors*>::iterator iter = m_level[dest_x][dest_y].begin() ; iter !=m_level[dest_x][dest_y].end() ; iter++ )
        if ((*iter) != nullptr && (*iter)->blockActors())
            return false;
    return true;
//    if(m_level[dest_x][dest_y].front()->blockActors() && m_level[dest_x][dest_y].front() !=nullptr)
//        return false;
   // return true;
    //    double currentObjectLowerLeftX= getX();
    //    double currentObjectLowerLeftY= getY();
    //    double otherObjectX=otherObject.getX();
    //    double otherObjectY=otherObject.getY();
    //
    //    //calculate (Δx)2 + (Δy)2
    //    double result= pow( (currentObjectY-otherObjectY),2 ) + pow((currentObjectX-otherObjectX),2);
    //    //if the result is <=100, return true
    //    if(result<=100)
    //        return true;
    //otherwise false

}



//void StudentWorld:: displayText()
//{
//
//    string a[4] = {"", "", "", ""};
//    a[leader] = "*";
//    ostringstream text;
//    int ticks = 2000 - m_ticks;
//    text << "Ticks:" << setw(5) << ticks << " - " << compilerForEntrant[0]->getColonyName() << a[0] << ": ";
//    text << text.fill('0') << setw(2) << m_antNum[0];
//    if (fileNames.size() > 1)
//        text << "  " << compilerForEntrant[1]->getColonyName() << a[1] << ": " << text.fill('0') << setw(2) << m_antNum[1];
//    if (fileNames.size() > 2)
//        text << "  " << compilerForEntrant[2]->getColonyName() << a[2] << ": " << text.fill('0') << setw(2) << m_antNum[2];
//    if (fileNames.size() > 3)
//        text << "  " << compilerForEntrant[3]->getColonyName() << a[3] << ": " << text.fill('0') << setw(2) <<  m_antNum[3];
//    string s = text.str();
//    setGameStatText(s);
//}
