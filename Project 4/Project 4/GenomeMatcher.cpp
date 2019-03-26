#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Trie.h"
using namespace std;


//Your GenomeMatcher implementation must use your Trie class template in the
//implementation of all data structures that hold DNA sequences. It may use any other STL
//container classes so long as these are not used to hold DNA sequence data (i.e., strings of
//As, Cs, Ts, Gs, or Ns). It may also use any functions from <algorithm>.

//template <typename ValueType>
class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    ~GenomeMatcherImpl();
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
    Trie<Genome> trieNode;
    int m_minSearchLength;
};

//template <typename ValueType>
GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
//    The GenomeMatcher constructor takes a single argument which specifies the minimum
//    length of a DNA sequence that the user can later search for within the genome library.
//    (Your constructor should save this into a data member for later use.) For example, if the
//    user were to pass in a value of six for the minimum search length, then the shortest DNA
//    sequence the user could search for using the findGenomesWithThisDNA() method would
//    be six bases long, e.g. “GATTAC”. Attempting to search for shorter sequences like
//    “GATTA” or “ACTG” would result in findGenomesWithThisDNA() returning false.
//    This method must run in O(1) time
    m_minSearchLength=minSearchLength;
}
//template <typename ValueType>
GenomeMatcherImpl:: ~GenomeMatcherImpl()
{
    //====================== TO-DO ============================
}
//template <typename ValueType>
void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    // This compiles, but may not be correct
}
//template <typename ValueType>
int GenomeMatcherImpl::minimumSearchLength() const
{
    return 0;  // This compiles, but may not be correct
}
//template <typename ValueType>
bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return false;  // This compiles, but may not be correct
}
//template <typename ValueType>
bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return false;  // This compiles, but may not be correct
}

//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
