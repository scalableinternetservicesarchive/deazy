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
// ------------------------------------------------------------------

class StudentWorld;

//========================= Actor class derived from GraphOnject =========================
class Actors: public GraphObject
{
public:
    Actors(int imageID, double startX, double startY, int startDirection = 0, int depth = 0, StudentWorld *sWorld=nullptr );
    virtual void doSomething()=0;
    virtual bool blockActors(double, double);
    virtual bool doesOverlap(Actors *);
    //===========MIGHT NEED TO  IMPLEMENT FOR THER ACTORS
    virtual bool isAlive() const;
    void setAlive(bool);
    virtual bool isInfected() const;
//    virtual void killTheActor();
    virtual void setInfection(bool);
//    virtual bool isMoved();
//    virtual void setMove(bool);
    StudentWorld *getWorld() const;
    virtual ~Actors();
    virtual Direction randomDir();
    virtual bool isCitizen();
    virtual bool isZombie();
    virtual bool levelHasZombie();
    virtual void flameDamagable(double,double);
    virtual void vomitInfectable(double, double);
    virtual bool flameBlockable(double, double);
    virtual bool isPerson();
    
private:
    //private members
    bool m_alive;
    StudentWorld *m_StudentWorld;
    bool m_infected;
//    bool m_isMoved;
    //bool m_block;
};


class Walls: public Actors
{
public:
    Walls(double startX, double startY, StudentWorld *sWorld);
    virtual void doSomething();
    virtual bool blockActors(double, double);
    virtual bool flameBlockable(double, double);
     ~Walls();
    
};

class Penelope : public Actors
{
public:
    Penelope(double startX, double startY, StudentWorld *sWorld);
    virtual void doSomething();
    virtual bool blockActors(double, double);
     ~Penelope();
    virtual void flameDamagable(double,double);
    virtual void vomitInfectable(double, double);
    virtual bool isPerson();
//    int numOfLandmines();
//    int numOfFlamethrower_charges();
//    int numOfVaccines();
   // virtual bool blockActors() const;
//    virtual int direction();
   // virtual bool isAlive() const;
//    virtual void gotInfected() ;
//    virtual void killTheActor();
private:
    int m_infectionCount;
};
class Exit :public Actors
{
public:
    Exit(double startX, double startY, StudentWorld *sWorld);
    virtual void doSomething();
    virtual bool doesOverlap(Actors*);
    virtual bool flameBlockable(double, double);
    ~Exit();
};
class Citizen: public Actors
{
public:
    Citizen(double, double, StudentWorld*);
    virtual void doSomething();
    ~Citizen();
    virtual bool isCitizen();
    virtual bool blockActors(double, double);
    virtual void flameDamagable(double, double);
    virtual void vomitInfectable(double, double);
    virtual bool isPerson();
private:
    int m_infectionCount;
    bool m_paralyzedCounter;
};
class DumbZombies : public Actors
{
public:
    DumbZombies(double, double, StudentWorld*);
    virtual void doSomething();
    ~DumbZombies();
    virtual bool isZombie();
    virtual bool levelHasZombie();
    virtual bool blockActors(double, double);
    virtual void flameDamagable(double, double);
private:
    bool m_paralyzedCounter;
     int   m_movementPlan;

};
class SmartZombies : public Actors
{
public:
    SmartZombies(double, double, StudentWorld*);
    virtual void doSomething();
    ~SmartZombies();
    virtual bool isZombie();
    virtual bool levelHasZombie();
    virtual bool blockActors(double, double);
    virtual void flameDamagable(double, double);
private:
    bool m_paralyzedCounter;
     int  m_movementPlan;
};

class Landmines : public Actors
{
public:
    Landmines (double, double, StudentWorld*);
    virtual void doSomething();
    ~Landmines ();
    virtual void flameDamagable(double, double);
    bool activeState();
private:
    int m_safteyTick;
    bool m_activeState;
};
class Pits: public Actors
{
public:
    Pits(double, double, StudentWorld*);
    virtual void doSomething();
    ~Pits();
};
class Flames : public Actors
{
public:
    Flames(double, double, Direction,StudentWorld*);
    virtual void doSomething();
    ~Flames();
private:
   int m_creationCount;

};
class Vomit : public Actors
{
public:
    Vomit(double, double, StudentWorld*);
    virtual void doSomething();
    ~Vomit();
private:
    int m_creationCount;
};
class VaccineGoodies : public Actors
{
public:
    VaccineGoodies(double, double, StudentWorld*);
    virtual void doSomething();
    ~VaccineGoodies();
    virtual void flameDamagable(double, double);
};
class GasCanGoodies : public Actors
{
public:
    GasCanGoodies(double, double, StudentWorld*);
    virtual void doSomething();
    ~GasCanGoodies();
    virtual void flameDamagable(double, double);
};
class LandminesGoodies : public Actors
{
public:
    LandminesGoodies(double, double, StudentWorld*);
    virtual void doSomething();
    ~LandminesGoodies();
    virtual void flameDamagable(double, double);
};


#endif /* representPenelope_hpp */
