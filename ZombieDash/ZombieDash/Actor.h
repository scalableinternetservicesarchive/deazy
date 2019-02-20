//
//  Actor.h
//  Project 3
//
//  Created by ali mirabzadeh on 2/13/19.
//  Copyright © 2019 AMZ Development. All rights reserved.
//

#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"


//  ----------------- GraphObject ---------------------------------

//GraphObject(int imageID, double startX, double startY, int startDirection = 0, int depth = 0);
//double getX() const; // in pixels (0-255)
//double getY() const; // in pixels (0-255)
//virtual void moveTo(double x, double y); // in pixels (0-255)
//int getDirection() const; // in degrees (0-359)
//void setDirection(Direction d); // {up, down, left, right}
//double getRadius() const; // in pixels (0-255)

//You must not redefine any of these methods in your derived classes since they are not defined as virtual in our base class.
// ------------------------------------------------------------------

class StudentWorld;


class Actors: public GraphObject
{
public:
    //constructor
    Actors(int imageID, int startX, int startY, int startDirection = 0, int depth = 0, StudentWorld *sWorld=nullptr );
    //pure virtual doSomething
    virtual void doSomething()=0;
    //bool is(double, double);
   // virtual base class destructor
    virtual bool blockActors(int, int);
//    virtual int direction();
//    virtual bool isAlive() const;
//    virtual bool isInfected() const;
//    virtual void killTheActor();
//    virtual void gotInfected();
//    virtual bool objectOverlap(Actors &);
//    virtual bool isMoved();
//    virtual void setMove(bool);
    StudentWorld *getWorld() const;
    virtual ~Actors();
    
private:
    //private members
//    bool m_alive;
    StudentWorld *m_StudentWorld;
//    bool m_infected;
//    bool m_isMoved;
    //bool m_block;
};

class Walls: public Actors
{
public:
    Walls(int startX, int startY, StudentWorld *sWorld);
    virtual void doSomething();
    virtual bool blockActors(int, int) ;
     ~Walls();
    
};

class Penelope : public Actors
{
public:
    Penelope(int startX, int startY, StudentWorld *sWorld);
    virtual void doSomething();
    virtual bool blockActors(int, int);
     ~Penelope();
   // virtual bool blockActors() const;
//    virtual int direction();
//    virtual bool isAlive() const;
//    virtual void gotInfected() ;
//    virtual void killTheActor();
//private:
//    int m_infectionCount;
};
class Exit :public Actors
{
public:
    Exit(int startX, int startY, StudentWorld *sWorld);
    virtual void doSomething();
    //virtual bool blockActors() ;
    ~Exit();
};





//for part 2 submission
//class DumbZombies : public Actors
//{
//
//};
//class SmartZombies : public Actors
//{
//
//};
//class DumbZombies : public Actors
//{
//
//};
//class Landmines : public Actors
//{
//
//};
//class Pits: public Actors
//{
//
//};
//class Flames : public Actors
//{
//
//};
//class Vomit : public Actors
//{
//
//};
//class VaccineGoodies : public Actors
//{
//
//};
//class GasCanGoodies : public Actors
//{
//
//};
//class LandminesGoodies : public Actors
//{
//
//};


#endif /* representPenelope_hpp */
