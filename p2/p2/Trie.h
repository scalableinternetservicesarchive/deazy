//
//  Trie.h
//  p2
//
//  Created by ali mirabzadeh on 3/8/19.
//  Copyright © 2019 AMZ Development. All rights reserved.
//
#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#inc
#include <vector>
int ALPHABET_SIZE=26;

template<typename ValueType>
class Trie
{
public:
    Trie();
    ~Trie();
    void reset();
    void insert(const std::string& key, const ValueType& value);
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;
    // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
private:
    // Trie node structure
    struct TrieNode
    {
        TrieNode *children[ALPHABET_SIZE];           //Your Trie class template must work for key strings containing any characters, not just A, C, G, T, and N
        vector<ValueType> values;         //store the values, ValueType, in each TrieNode
        bool isEndOfWord;                 //isEndOfWord is true if the node represents end of a word
    };
    Trie *root;
    //helper function for destructor; recursively delete nodes
    void clearTrie(TrieNode *current)
    {
        if(current==nullptr)
            return;
        else
        {
            for(int i=0; i<ALPHABET_SIZE; i++)
            {
                clearTrie(current->children[i]);
                delete current;
            }
        }
    }
};
//constructor implementation
template<typename ValueType>
Trie :: Trie()
{
    // It should create a root trie node with no children and no values, and set the root pointer (if any) to point to this root node. This method must run in O(1) time.
    root= new Trie();
    root->isEndofWord=false;
    for (int i=0; i < ALPHABET_SIZE; i++)
    {
        root->children[i]=nullptr;
    }
}
//implementation of Destructor
template<typename ValueType>
Trie :: ~Trie()
{
    //The destructor must free all memory associated with trie. This method must run in O(N)
    // time where N is the number of nodes in the trie.
    clearTrie(root);//call the private function by passing the root node
}
//reset()
template<typename ValueType>
void Trie:: reset()
{
    //Your trie’s reset() method must free all of the memory associated with the current trie,
    //then allocate a new empty trie with a single root node (with no children or values). This
    //method must run in O(N) time where N is the number of nodes in the trie
}
//insert()
template<typename ValueType>
void Trie:: insert(const std::string& key, const ValueType& value)
{
    //================================ DESCRIPTION ====================================
    //The insert() method associates the specified key with the specified value in your trie, e.g.
    //    “GATTACA” à 42 by adding the appropriate nodes (if any are required) to the trie, and
    //    then adding the specified value (e.g., 42) to the existing set of values in the appropriate
    //    node. A given key inserted in the trie may map to one or more values, e.g., “GATTACA”
    //    à {42, 17, 32, 42, 42, 19, 17}, and those values may include duplicates. Here’s how you
    //    might define a trie variable that maps strings to ints and insert a few items:
    //    Trie<int> trie; // This is like std::multimap<std::string,int> trie;
    //    trie.insert("GATTACA", 42); // GATTACA à {42}
    //    trie.insert("GATTACA", 17); // GATTACA à {42, 17}
    //    trie.insert("GATTACA", 42); // GATTACA à {42, 17, 42}
    //    ...
    //    trie.insert("GCTTACA", 30); // GCTTACA à {30}
    //    There are a number of ways you can associate a given trie node with one or more values,
    //    including having a vector or list of values associated with each trie node. You can choose
    //    any approach you wish.
    //    Your insert() function must run in O(L*C) time where L is the length of the inserted key
    //    and C is the average number of children per node in your trie. With a clever approach,
    //    you may be able to get your insert() function to run in O(L) time, but this is not required.
    //Hint: Don’t try to deal with mismatch-handling in your insert() method – just insert
    //    strings into your trie exactly as they are passed into your insert() method. Instead deal
    //    with searching for mismatches in your find() method.
    
    Trie *cur= root;//a pointer that points to the root
    for(int counter=0; counter< key.length(); counter++)
    {
        //create a new node if the path doesn't exist
        if(cur->children[key[counter]]==nullptr)
        {
            //create a new node
            cur->children[key[counter]]= new Trie();
            //push the value in that node
            values.push_back(value);
        }
        //if the path does exist
        else
            //push the value in the vector for the current node
            values.push_back(value);
        //go to the next node
        cur=cur->children[i];
    }
    // mark last node as leaf
    cur->isEndofWord=true;
}
//find()
template<typename ValueType>
std::vector<ValueType> Trie:: find(const std::string& key, bool exactMatchOnly) const
{
    /*
     ================================ DESCRIPTION ====================================
     The find() method is used to search for the values associated with a given key string, e.g.,
     “GATTACA”.
     If exactMatchOnly is true, the find() method must return a vector containing all of the
     values associated with the exact key string specified. There is no required ordering of the
     returned values. If no values are associated with the specified key, then the find() method
     should return an empty vector.
     In the tree depicted in the diagram several pages above, searching for “hit” with an
     exactMatchOnly of true would return values of {1, 2} in any order you choose:
     std::vector<int> result1 = trie.find("hit", true); // returns {1, 2} or {2, 1}
     If exactMatchOnly is false, the find() method must return a vector containing all of the
     values associated with both the exact search term as well as all values associated with
     keys in the trie that:
     1. Match the first character of the search term exactly, and
     2. Have a single mismatching character (i.e., are a SNiP) of the specified key
     anywhere past the first character.
     There is no required ordering of the returned values. If no values are associated with the
     specified key or SNiPs of that key, then the find() method should return an empty vector.
     In the tree depicted in the diagram above, searching for “hit” with an exactMatchOnly of
     false would return values of {1, 2, 10, 20, 7, 8, 9} in any order you choose:
     std::vector<int> result2 = trie.find("hit", false); // returns {1, 2, 10, 20, 7, 8, 9}
     Why {1, 2, 10, 20, 7, 8, 9}? The {1, 2} are associated with the exact match, “hit”, the
     {10, 20} are associated with the SNiP of “hip”, and the {7, 8, 9} are associated with the
     SNiP of “hat”. (If instead of {7, 8, 9} “hat” were associated with {10, 2, 5, 10}, then the
     resulting vector would be {1, 2, 10, 20, 10, 2, 5, 10} in any order.
     In the tree depicted in the diagram above, searching for “sit” with an exactMatchOnly of
     false would return an empty vector:
     std::vector<int> result3 = trie.find("sit", false); // returns {}
     Why? Because no nodes in our trie begin with ‘s’, and the find() method must only
     returns (a) exact matches or (b) SNiPs where the first letter of the searched for string is an
     exact match with some string in the trie. So even while “sit” is technically a SNiP of “hit”
     since the first letters differ, the results associated with “hit” in the trie would not be
     returned.
     Your find() function must run in O(L * C) time where L is the length of the searched-for
     key and C is the average number of children per node in your trie.
     Hint: Recursion is your friend! With some clever coding you can easily find exact
     matches and single-character mismatches with the same code!
     */
    
    //   returns false if the trie is empty
    if(root==nulptr)
        return false;
    //   if looking for exact match
    if(exactMatchOnly==true)
    {
        vector<ValueType> tempVector;
        int countMissMatch=0;
        
        Trie *cur= root;   // a pointer that points to the root
        for(int counter=0; counter< key.length(); counter++)
        {
            //if there is a missmatch
            if(!cur->children[key[i]])
                return false;
            tempVector.push_back(values);
            //go to the next node
            cur = cur->children[key[i]];
        }
        // if not nullptr and end of the leaf; found the match
        if(cur != nullptr && cur->isEndOfWord)
            return tempVector;
    }
    //if not looking for exact match
    if(exactMatchOnly==false)
    {
        int countMissMatch=0;
        
        Trie *cur= root;   // a pointer that points to the root
        for(int counter=0; counter< key.length(); counter++)
        {
            //if the fisrt letter is not the same, return false
            if(key[0]!=cur->children[key[0]])
                return false;
            //if there is a missmatch
            if(!cur->children[key[i]])
            {
                //fisst increment the number of missmatches
                countMissMatch++;
                //if foud two missmatches
                if(countMissMatch==2)
                    return false;
            }
            //go to the next node
            cur = cur->children[key[i]];
        }
        //return true if not nullptr and end of the leaf; found the match
        return (cur != nullptr && cur->isEndOfWord);
    }
    
    
}
#endif // TRIE_INCLUDED
