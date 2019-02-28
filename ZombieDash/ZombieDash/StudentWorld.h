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
    bool isBlocked( double, double, Actors * );
    Direction randmonDir();
    void addNewZombie(double, double);
    double distanceToPenelope(double, double);
    double distanceToNearestZombie(double, double);
    bool euclideanDistanceFromPenelope(double, double);
    bool zombieExist();
    bool isCitizenOnTheSameRowOrColumnWithPenelope(double, double);
    Direction findWhatDirectionCitizenShouldFaceToFollowPenelope(double,double);
    Direction determineOneHorizontalOneVerticalDirectionRandomly(double, double,int);
    bool euclideanDistanceFromCitizenToZombie(double,double);
    bool doesOverlapWithPenelope(double, double);
    bool doesOverlapWithPit(double, double,Actors*);
    bool doesExitOverlapWithCitizen(double, double);
    bool isPersonInFrontOfZommbie(double, double);
    bool isPersonWhoseEuclideanDistanceFromVomitCoordinates(double, double);
    void introduceVomitAtThisPoint(double, double);
    Direction randomDir();
    void addVaccineGoodieHere(double, double);
    Actors* findClosestPersonToSmartZombie(double, double);
    double findTheDistanceFromSmartZombieToPerson(double, double,Actors*);
    bool smartZombieSameRowOrColWithThePerson(double, double, Actors*);
    Direction pickDirectionToGetCloserToPerson(double, double, Actors*);
    Direction pickRandomDirForSmartZombieToFollowPerson(double, double, int,Actors*);
    bool doesOverlapsWithcitizenPenelope(Actors *);
    void introduceFlameObject(double, double, Direction);
     void introducePitObject(double, double);
    bool isFlameDamagable();
    void vomitOverlapsWithcitizenPenelopeToInfect(Actors *);
    void flameDamagesWhenOverlapsWithTheseObjecr(Actors *);
    void introduceLandmineHere(double, double);
    int flamethrowerCharges();
    void incrementFlamethrowerCharges(int);
    void decrementFlamethrowerCharges();
    int landminesCounter();
    void incrementLandmines(int);
    void decrementLandmines();
    int vaccineCounter();
    void incrementVaccine(int);
    void decrementVaccine();
    string stingStreamTextDisplay();
    double score();
    void changeScore(double);
    bool isBlockedFromFlame( double, double, Actors * );
    int infectionCounter();
    void incrementInfection();
    void intitailStatusInfection(int);
    bool noCitizenOnLevel();

private:
    //2D list for stroing all the actors
    vector<Actors*> m_level;
    Penelope *penelopePtr;
    int  m_landmines,
         m_flamethrower_charges,
         m_vaccines,
         m_score,
         m_infectionCount;
};

#endif // STUDENTWORLD_H_

