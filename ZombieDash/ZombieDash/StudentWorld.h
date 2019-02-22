#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include <vector>
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
    bool isBlocked( int, int, Actors * );
    Direction randmonDir();
private:
    //2D list for stroing all the actors
    vector<Actors*> m_level;
    Penelope *penelopePtr;
};

#endif // STUDENTWORLD_H_

