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
    void addNewZombie(int, int);
    int distanceToPenelope(int, int);
    int distanceToNearestZombie(int, int);
    bool euclideanDistanceFromPenelope(int, int);
    bool zombieExist();
    bool isCitizenOnTheSameRowOrColumnWithPenelope(int, int);
    Direction findWhatDirectionCitizenShouldFaceToFollowPenelope(int,int);
    Direction determineOneHorizontalOneVerticalDirectionRandomly(int, int,int);
    bool euclideanDistanceFromCitizenToZombie(int,int);
    bool doesOverlapWithPenelope(int, int);
    bool doesOverlapWithPit(int, int,Actors*);
    bool doesExitOverlapWithCitizen(int, int);
    bool isPersonInFrontOfZommbie(int,int);
    bool isPersonWhoseEuclideanDistanceFromVomitCoordinates(int, int);
    void introduceVomitAtThisPoint(int, int);
    Direction randomDir();
    void addVaccineGoodieHere(int,int);
    Actors* findClosestPersonToSmartZombie(int,int);
    int findTheDistanceFromSmartZombieToPerson(int,int,Actors*);
    bool smartZombieSameRowOrColWithThePerson(int,int, Actors*);
    Direction pickDirectionToGetCloserToPerson(int, int, Actors*);
    Direction pickRandomDirForSmartZombieToFollowPerson(int, int, int,Actors*);
private:
    //2D list for stroing all the actors
    vector<Actors*> m_level;
    Penelope *penelopePtr;
};

#endif // STUDENTWORLD_H_

