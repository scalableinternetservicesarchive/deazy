#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <fstream> // needed to open files
#include "Trie.h"
using namespace std;

class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    ~GenomeImpl();
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    string m_name,
           m_sequence;
//    void loadFunction()
//    {
//        // Specify the full path and name of the gene data file on your hard drive.
//        string filename = "/Users/alimirabzadeh/desktop/Project 4/data/Halorubrum_chaoviator.txt";
//        // Open the data file and get a ifstream object that can be used to read its
//        // contents.
//        ifstream strm(filename);
//        if (!strm)
//        {
//            cerr << "Cannot open " << filename << endl;
//            return;
//        }
//        vector<Genome> vg;
//        bool success = Genome::load(strm, vg); // Load the data via the stream.
//        if (success)
//        {
//            cerr << "Loaded " << vg.size() << " genomes successfully:" << endl;
//            for (int k = 0; k != vg.size(); k++)
//                cerr << vg[k].name() << endl;
//        }
//        else
//            cerr << "Error loading genome data" << endl;
//    } // destructor for ifstream closes the file
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
    /*
     The Genome constructor must initialize a new Genome object with the indicated name
     and DNA sequence. You implementation may assume the sequence contains at least one
     character, and all characters in the sequence are upper case A, C, T, G, or N (we'll explain
     N later). It should run in O(S) time, where S is the length of the longer string.
     */
    //===============TO DO ================
    for (int i=0; i< nm.length(); i++)
    {
        m_name[i]=nm[i];
    }
    for (int i=0; i< sequence.length(); i++)
    {
        m_sequence[i]=sequence[i];
    }
}
GenomeImpl:: ~GenomeImpl()
{
    //===================TO-DO=====================
}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes) 
{
    /*
     provided genome text files. Notice that you pass in to this method an istream object,
     which is associated with a genomic data file. (For more information on what an istream
     is and how to open data files in C++, see the File I/O writeup on the class web site.) This
     function fills the vector second parameter with Genome objects, one for each genome
     specified in the data file.
     
     This method is a static member function, which means that it is not generally called for a
     particular Genome object (e.g., g.load(...) or gp->load(...)), but instead is called for
     the class itself, on no particular object (i.e., Genome::load(...)). Static member
     functions are never passed a this pointer that would point to one particular object.3
     Static member functions are often used when you have some functionality that might
     otherwise be an ordinary global function, not a member of any class, that bears a strong
     relationship with one particular class. Loading genomes seems pretty tightly associated
     with the Genome type, so making it a static member function of Genome is appropriate.
     
     Don’t worry about the complexities of C++ input streams! The only input function
     your load() method needs is std::getline()!
     */
    //while there is something in the file to read
    string s, name, seq;
    char ch;
    genomeSource.get(ch);
    //if the file doesn't start with a name
    if(ch!='>')
        return false;
    //read each line in the file
    while(getline(genomeSource,s))
    {
//        Extract the genome name from a line in the file that begins with a greater than sign; everything following the greater-than sign (and excluding the newline at the end of the line) is the name, so for the line
        //if the first char of the current line has starts with '>'
        if(s[0]=='>')
        {
            //make seq and name empty whenever found a new name;
            seq="";
            name="";
            //if no char after the '>', return false
            if(s[1]==' ')
                return false;
            for(int i=1; i<s.length();i++)
            {
                name[i-1]=s[i];
            }
        }
        //if there is no base line after the name line, return false
        else if(s=="")
            return false;
//        Extract the sequence of DNA bases for that name from the file into one concatenated string. The bases are on the lines following the name up to but not including the next line starting with a greater-than sign (or the end of the file
        else
        {
            for (int j=0; j<s.length();j++)
            {
                if(toupper(s[j])=='A' || toupper(s[j])=='C' || toupper(s[j])=='G'|| toupper(s[j])=='T' || toupper(s[j])=='N')
                    seq+=s[j];
                else
                    return false;
            }
        }
    }
//    3. Create a Genome object with the extracted name and DNA sequence, and add it to the vector of Genomes that is the second parameter. if file is properly formatted
    genomes.push_back(new Genome(name,seq));
    return true;
}

int GenomeImpl::length() const
{
//    The length() method returns the complete length of the DNA sequence, specifically the
//    total count of As, Cs, Ts, Gs (and Ns) found in the sequence held by the object. This
//    method must run in O(1) time
    int count=0;
    for (int i=0; i< m_sequence.length(); i++)
    {
        if(toupper(m_sequence[i])=='A' || toupper(m_sequence[i])=='C' || toupper(m_sequence[i])=='T' ||toupper(m_sequence[i])=='G' ||toupper(m_sequence[i])=='N' )
            count++;
    }
    return count;
}

string GenomeImpl::name() const
{
    return m_name;
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    /*
     The extract() method must set fragment to a copy of a portion of the Genome's DNA
     sequence: the substring length characters long starting at position (where the first
     character of the sequence is at position 0). For example, if a Genome object were created
     with an 80-base DNA sequence:
     Genome g("oryx",
     "GCTCGGNACACATCCGCCGCGGACGGGACGGGATTCGGGCTGTCGATTGTCTCACAGATCGTCGACGTACATGACTGGGA");
     Then calling the extract() method would produce the following results:
     string f1, f2, f3;
     bool result1 = g.extract(0, 5, f1); // result1 = true, f1 = “GCTCG”;
     bool result2 = g.extract(74, 6, f2); // result2 = true, f1 = “CTGGGA”;
     bool result3 = g.extract(74, 7, f3); // result3 = false, f1 is unchanged
     The extract() method must return true if it successfully extracts a string of the specified
     length, and false otherwise (e.g., you try to extract a string that goes past the end of the
     genome); if extract returns false, fragment must remain unchanged.
     This method must run in O(S) time where S is the length of the extracted sequence.
     */
    //you try to extract a string that goes past the end of the genome
    if(position+length> GenomeImpl::length()-1)
        return false;
    if(position<0 || position > GenomeImpl::length()-1)
        return false;
    for(int count=position; count<position+length;count++)
    {
        fragment[count-position]=m_sequence[position];
    }
    return true;
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes) 
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}
