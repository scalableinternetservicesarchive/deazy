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
#include <sstream>  // defines the type std::ostringstream
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw
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
{
    m_landmines=0;
    m_flamethrower_charges=0;
    m_vaccines=0;
    m_infectionCount=0;
    m_score=0;
}
//init() method that would be called by the framework to initialize all the objects load the level(s)
int StudentWorld::init()
{
    //get the level file to load
    Level lev(assetPath());
    //get the level based what level penelope is on
    //GWSTATUS_PLAYER_WON
    string levelFile = "level0"+ to_string(getLevel())+".txt";
    Level::LoadResult result = lev.loadLevel(levelFile);
    if (result == Level::load_fail_file_not_found)
        return GWSTATUS_PLAYER_WON;
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
//                         m_level.push_back(nullptr);
                        continue;
                       
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
//    The status line must be formatted like this (the spec and sample executables are inconsistent):
//Score: 004500  Level: 27  Lives: 3  Vaccines: 2  Flames: 16  Mines: 1  Infected: 0
    
    //iterate through all objects
    for (vector<Actors*>::iterator it = m_level.begin(); it != m_level.end(); it++)
    {
        // tell all the objects to do Something during the tick to do something (e.g. move)
        (*it)->doSomething();
        //if the Penelope is dead, return from move() with GWSTATUS_PLAYER_DIED
        if(penelopePtr->isAlive()==false)
        {
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
        
        //if Penelope overlaps with Exit, return the level is finished
//        if(citizne alive && citizen overlap exit)
//            if((*it)->doesOverlap(penelopePtr))
//                return GWSTATUS_FINISHED_LEVEL;
        if((*it)->doesOverlap(penelopePtr))
        {
            playSound(SOUND_LEVEL_FINISHED);
            return GWSTATUS_FINISHED_LEVEL;
        }
    }
   //Remove newly-dead actors after each tick
   for (vector<Actors*>::iterator iter = m_level.begin(); iter != m_level.end();)
   {
        //if the current actor is dead, remove that actor from the level
        if (!(*iter)->isAlive())
        {
            delete *iter;
            iter=m_level.erase(iter);
        }
        else
            iter++;
    }
    //display the string stream n top
    setGameStatText(stingStreamTextDisplay());
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
        m_level.erase(it);
        it=m_level.begin();
    }
    m_landmines=0;
    m_flamethrower_charges=0;
    m_vaccines=0;
    m_infectionCount=0;
    m_score=0;
}
//Destructor
StudentWorld:: ~StudentWorld()
{
    //call cleanUp() to destrot all the objects
    this->cleanUp();
}
int StudentWorld:: flamethrowerCharges()
{
    return m_flamethrower_charges;
}
void StudentWorld:: incrementFlamethrowerCharges(int amount)
{
    m_flamethrower_charges+=amount;
}
void StudentWorld:: decrementFlamethrowerCharges()
{
    m_flamethrower_charges--;
}
int StudentWorld:: landminesCounter()
{
    return m_landmines;
}
void StudentWorld::incrementLandmines(int amt)
{
    m_landmines+=amt;
}
void StudentWorld:: decrementLandmines()
{
    m_landmines--;
}
int StudentWorld:: vaccineCounter()
{
    return m_vaccines;
}
void StudentWorld:: incrementVaccine(int amt)
{
    m_vaccines+=amt;
}
void StudentWorld:: decrementVaccine()
{
    m_vaccines--;
}
//Determining blocking movement for wall, citizens, Penelope, and zombies
bool StudentWorld:: isBlocked(  double dest_x, double dest_y, Actors *actorPtr)
{
    //iterate through all the objects
    for (vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++ )
    {
        //if the current object is the same as the passed actor OR it is nullptr then  skip
        if( (*iter)==actorPtr )
            continue;
        //if it is an objet that has the blockActors methods( walls, zombies, citizens, Penelope), return false as they block the current object
        else if((*iter)->blockActors(dest_x, dest_y))
            return false;
    }
    //otherwise return true
    return true;
}
//check if the passed object is a citizen
void StudentWorld:: addNewZombie(double startX, double startY)
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
double StudentWorld:: distanceToPenelope(double citizenX, double citizenY)
{
    return sqrt(pow(citizenX - penelopePtr->getX(), 2) + pow(citizenY - penelopePtr->getY(), 2));
}
//return the distance between the citizen and nearest zombie
double StudentWorld:: distanceToNearestZombie(double citizenX, double citizenY)
{
    //By default min dist is 240, the largest possible distance on the level
    double minDist=240;
    for(vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++)
    {
//        if((*iter)==nullptr) continue;
        if((*iter)->isZombie())
        {
            double zombieX= (*iter)->getX();
            double zombieY=(*iter)->getY();
            //calculate the distance between the citizen and the current zombie
            double tempMinDist= sqrt(pow(zombieX - citizenX, 2) + pow(zombieY - citizenY, 2));
            //if tempMinDist is smaller than minDist
            if(tempMinDist<minDist)
                //store the temp value in minDist
                minDist=tempMinDist;
            else
                continue;
        }
    }
    return minDist;
}
//detemine Euclidean Distance From Penelope
bool StudentWorld:: euclideanDistanceFromPenelope(double citizenX, double citizenY)
{
    double deltaX= citizenX - penelopePtr->getX();
    double deltaY= citizenY - penelopePtr->getY();
    double result= pow(deltaX,2) + pow(deltaY, 2);
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
//        if((*iter)==nullptr) continue;
        //if found one zombie retern true
        if((*iter)->levelHasZombie())
            return true;
    }
    //otherwise, return false as it could not find any
    return false;
}
//check if the passed point which is for a citizen has either the sam y or x, row or col.
 bool StudentWorld:: isCitizenOnTheSameRowOrColumnWithPenelope(double citizenX, double citizenY)
{
    //if the either is the same, return true
    if(citizenX== penelopePtr->getX() || citizenY== penelopePtr->getY())
        return true;
    //otherwise false
    return false;
}
//return a direction that a citizen should face based on Penelope location, called if penelope and citizen are on the same row or col
Direction StudentWorld:: findWhatDirectionCitizenShouldFaceToFollowPenelope(double citizenX, double citizenY)
{
    //if both on the same column
    if(citizenX== penelopePtr->getX())
    {
        //if penelope on right of the citzen
        if(citizenY < penelopePtr->getY())
            return Actors::up;
        return Actors:: down;
    }
    //on the same row
    else
    {
        //if penelope on top the citizen
        if(citizenX < penelopePtr->getX())
            return Actors:: right;
        return Actors:: left;
    }
}
//randmoly pick a direction for a citizen if he is not on the same row or col
Direction StudentWorld:: determineOneHorizontalOneVerticalDirectionRandomly(double citizenX, double citizenY, int randomDirection)
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
bool StudentWorld:: euclideanDistanceFromCitizenToZombie(double citizenX, double citizenY)
{
    //iterate through all the actors
    for(vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++)
    {
        //if nullptr continue
//        if((*iter)==nullptr) continue;
        //if the current actor is zombie
         if((*iter)->isZombie())
        {
            double deltaX= citizenX - (*iter)->getX();
            double deltaY= citizenY - (*iter)->getY();
            double result= pow(deltaX,2) + pow(deltaY, 2);
            //if less than 80 pixels, return true
            if(result<= pow(80, 2))
                return true;

        }
    }
    //if there is no zombie with that specification close to a citizen, return false
    return false;
}
//check if the passed object overlap with penelope
bool StudentWorld:: doesOverlapWithPenelope(double point_x, double point_y)
{
    for(vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++)
    {
        //if nullptr continue
//        if((*iter)==nullptr) continue;
        //if the current actor is penelope or citizen
         if((*iter)==penelopePtr)
        {
            double deltaX= point_x - (*iter)->getX();
            double deltaY= point_y - (*iter)->getY();
            double result = pow(deltaX, 2) + pow(deltaY, 2);
            if(result<= pow(10, 2))
                return true;
        }
    }
    return false;
}
////check if the any person or zombie overlaps with a pit
//bool StudentWorld:: doesOverlapWithPit(int pit_x, int pit_y,Actors* actor)
//{
//    for(vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++)
//    {
//        //if nullptr continue
//        if((*iter)==nullptr) continue;
//        //=================== CODE HERE ====================================
//    }
//    return false;
//}
////check if the citizen overlap with exit
bool StudentWorld:: doesExitOverlapWithCitizen(double exit_x, double exit_y)
{
    //iterate through all the actors
    for(vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++)
    {
        if((*iter)->isCitizen())
        {
            double deltaX= exit_x - (*iter)->getX();
            double deltaY= exit_y - (*iter)->getY();
            double result = pow(deltaX, 2) + pow(deltaY, 2);
            if(result<= pow(10, 2))
                return true;
        }
    }
    return false;
}
//check if there is a person in front of the current zombie
bool StudentWorld:: isPersonInFrontOfZommbie(double zombieFacing_x, double zombieFacing_y)
{
    for(vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++)
    {
        //if nullptr continue
//        if((*iter)==nullptr) continue;
        //calculate the center of the current person and zombie passed in
        double zombieFacingX_center= zombieFacing_x+ SPRITE_WIDTH/2;
        double zombieFacingY_center= zombieFacing_y + SPRITE_HEIGHT/2;
        //if the current object is
        if((*iter)->isCitizen() || (*iter)==penelopePtr)
        {
            double personX_center= (*iter)->getX() +SPRITE_WIDTH/2;
            double personY_center= (*iter)->getY()+SPRITE_HEIGHT/2;
            // then use the Udulican formula, instead the distance between the centers should be less than 16
            double deltaX= pow((zombieFacingX_center - personX_center),2);
            double deltaY= pow((zombieFacingY_center - personY_center),2);
            if(deltaX + deltaY < pow(16,2))
                return true;
            continue;
        }
    }
    return false;
}
//check if there is person in 10 pixels of vomit coordinate
bool StudentWorld:: isPersonWhoseEuclideanDistanceFromVomitCoordinates(double vomitCoordinate_x, double vomitCoordinate_y)
{
    for(vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++)
    {
        //if nullptr continue
//        if((*iter)==nullptr) continue;
        //if the object is a person
        if((*iter)->isCitizen() || (*iter)==penelopePtr)
        {
            // then use the Edulican formula
            int deltaX= pow((vomitCoordinate_x - (*iter)->getX()),2);
            int deltaY= pow((vomitCoordinate_y - (*iter)->getY()),2);
            if(deltaX + deltaY <= pow(10,2)) return true;
        }
    }
    return false;
}
// Introduce a vomit at this point
void StudentWorld:: introduceVomitAtThisPoint(double introVomit_x, double introVomit_y)
{
    m_level.push_back(new Vomit(introVomit_x, introVomit_y, this));
}
//return a random direction
// Randomly picks a direction
Direction StudentWorld::randomDir()
{
    int choice = randInt(0, 3);
    Direction dirChoice;
    switch (choice)
    {
        case 0:
            dirChoice = Actors:: up;
            break;
        case 1:
            dirChoice = Actors::right;
            break;
        case 2:
            dirChoice = Actors::down;
            break;
        case 3:
            dirChoice = Actors::left;
            break;
    }
    return dirChoice;
}
//add a vaccine goodie at the location passed
void StudentWorld:: addVaccineGoodieHere(double here_x,double here_y)
{
    m_level.push_back(new VaccineGoodies(here_x,here_y, this));
}

//This function returns the person object that is closest
Actors* StudentWorld:: findClosestPersonToSmartZombie(double smartZombie_x,double smartZombie_y)
{
    double minDist= 240;
    Actors *nearestActor;
    for(vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++)
    {
        //if nullptr continue
//        if((*iter)==nullptr) continue;
        if((*iter) -> isCitizen() || (*iter)==penelopePtr)
        {
            double personX= (*iter)->getX();
            double personY=(*iter)->getY();
            //calculate the distance between the citizen and the current zombie
            double deltaX= pow((smartZombie_x - personX),2);
            double deltaY= pow((smartZombie_x - personY),2);
            //if tempMinDist is smaller than minDist
            if(deltaX + deltaY < minDist)
            {
                //store the temp value in minDist
                minDist=deltaX + deltaY;
                nearestActor = *iter;
            }
        }
    }
    return nearestActor;
}
// find the distance from smart zombie to the person
double StudentWorld :: findTheDistanceFromSmartZombieToPerson(double smartZombie_x,double smartZombie_y, Actors* thePersonPtr)
{
   return sqrt( pow(smartZombie_x - thePersonPtr->getX(), 2) + pow(smartZombie_y- thePersonPtr->getY(), 2)) ;
}
//return true if smartZombie is one the same row or col with the person
bool StudentWorld :: smartZombieSameRowOrColWithThePerson(double smartZombie_x,double smartZombie_y, Actors* thePersonPtr)
{
    if(smartZombie_x == thePersonPtr->getX() || smartZombie_y == thePersonPtr->getY() )
        return true;
    return false;
}

Direction StudentWorld:: pickDirectionToGetCloserToPerson(double smartZombie_x,double smartZombie_y, Actors* thePersonPtr)
{
    if(smartZombie_x< thePersonPtr->getX())
        return Actors::right;
    else if(smartZombie_x > thePersonPtr->getX())
        return Actors:: left;
    else if(smartZombie_y< thePersonPtr->getY())
        return Actors::up;
    else
        return Actors:: down;
}
//randmoly pick a direction for a citizen if he is not on the same row or col
Direction StudentWorld:: pickRandomDirForSmartZombieToFollowPerson(double smartZombie_x,double smartZombie_y,int randomDirection, Actors* thePersonPtr )
{
    //if the random integer is 0, pick horizontal direction
    if(randomDirection==0)
    {
        if( smartZombie_x < thePersonPtr->getX())
            return Actors:: right;
        else
            return Actors:: left;
    }
    //otherwise pick a vertical direction
    else
    {
        if( smartZombie_x < thePersonPtr->getY())
            return Actors:: up;
        else
            return Actors:: down;
    }
}

bool StudentWorld:: doesOverlapsWithcitizenPenelope(Actors * actor)
{
    for(vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++)
    {
        //if the current actor is penelope or citizen
        if((*iter)->isCitizen() || (*iter)==penelopePtr)
        {
            double deltaX= actor->getX() - (*iter)->getX();
            double deltaY= actor->getY() - (*iter)->getY();
            double result = pow(deltaX, 2) + pow(deltaY, 2);
            if(result<= pow(10, 2))
                return true;
        }
    }
    return false;
}
//adding a flame object at the desired location
void StudentWorld:: introduceFlameObject(double here_x, double here_y, Direction dir)
{
    m_level.push_back(new Flames(here_x, here_y, dir,this));
}
//introducing a new pits at this loation
void StudentWorld:: introducePitObject(double here_x, double here_y)
{
    m_level.push_back(new Pits(here_x, here_y,this));
}
////vomit will infect a person if overlaps
void StudentWorld:: vomitOverlapsWithcitizenPenelopeToInfect(Actors *actor)
{
    for(vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++)
    {
        //if the current actor is penelope or citizen
        if((*iter)->isCitizen() || (*iter)==penelopePtr)
        {
                (*iter)->vomitInfectable(actor->getX(), actor->getY());
        }
    }
    return;
}


void StudentWorld:: flameDamagesWhenOverlapsWithTheseObjecr(Actors *actorPtr)
{
    for(vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++)//iterate through all the objects
    {
    //if the current actor is penelope or citizen
        (*iter)->flameDamagable(actorPtr->getX(), actorPtr->getY());
    }
}
void StudentWorld:: introduceLandmineHere(double here_x, double here_y)
{
    m_level.push_back(new Landmines(here_x, here_y, this));
}

string StudentWorld:: stingStreamTextDisplay()
{
    //    The status line must be formatted like this (the spec and sample executables are inconsistent):
    //Score: 004500  Level: 27  Lives: 3  Vaccines: 2  Flames: 16  Mines: 1  Infected: 0
    ostringstream oss;
    oss<< "Score: ";
    oss.fill('0');
    oss << setw(6)<< left<< score();
    oss<<"  Level: ";
    oss.fill(' ');
    oss << setw(4)<<left << getLevel();
    oss<<"Lives: "<<setw(3)<< left<<  getLives();
    oss<<"Vaccine: "<< setw(3) << left<< vaccineCounter();
    oss<< "Flames: "<< setw(4) << left<< flamethrowerCharges();
    oss<< "Mines: "<< setw(3) <<left<< landminesCounter() ;
    oss<< "Infection: "<< setw(4) << left<< infectionCounter();
    return oss.str();
}

double StudentWorld:: score()
{
    return m_score;
}
void StudentWorld:: changeScore(double amt)
{
    if(amt>=0)
        m_score+=amt;
    else
        m_score-=amt;
}
bool StudentWorld:: isBlockedFromFlame( double here_x, double here_y, Actors *actorPtr )
{
    //iterate through all the objects
    for (vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++ )
    {
        //if the current object is the same as the passed actor OR it is nullptr then  skip
        if( (*iter)==actorPtr )
            continue;
        //if it is an objet that has the blockActors methods( walls, zombies, citizens, Penelope), return false as they block the current object
        else if((*iter)->flameBlockable(here_x, here_y))
            return false;
    }
    //otherwise return true
    return true;
}

int StudentWorld::  infectionCounter()
{
    return m_infectionCount;
}
void StudentWorld:: incrementInfection()
{
    m_infectionCount++;
}
void StudentWorld:: intitailStatusInfection(int amt)
{
    m_infectionCount=amt;
}

bool StudentWorld:: noCitizenOnLevel()
{
    for (vector<Actors*>::iterator iter = m_level.begin() ; iter !=m_level.end() ; iter++ )
    {
        //if there is at least one citizen on the level, return false
        if( (*iter)->isCitizen())
            return false;
    }
    //otherwise return true
    return true;
}
