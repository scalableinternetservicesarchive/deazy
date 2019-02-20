#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include <list>
#include <string>
using namespace std;

class Actor;
class Level;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    virtual ~StudentWorld();
    void displayText();
    bool isBlocked( int, int ,int, int );
private:
    //2D list for stroing all the actors
    list<Actors*> m_level[VIEW_WIDTH][VIEW_HEIGHT];
    Penelope *penelopePtr;
};

#endif // STUDENTWORLD_H_

