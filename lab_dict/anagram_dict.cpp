/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename){
    /* Your code goes here! */
	ifstream in(filename);
	string temp;
	if(in.is_open()){
	    while(getline(in, temp)){
	    	string key = temp;
			std::sort(key.begin(), key.end());
			dict[key].push_back(temp);
	    }
	}
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words){
    /* Your code goes here! */
	std::vector<string>::const_iterator it;
	for(it = words.begin(); it < words.end(); it++){
	    string key = *it;
	    std::sort(key.begin(), key.end());
	    dict[key].push_back(*it);
	}
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const{
    /* Your code goes here! */
	string temp = word;
	std::sort(temp.begin(), temp.end());
	auto lookup = dict.find(temp);
	if (lookup != dict.end())
		return lookup->second;
	else
    	return vector <string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are omitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const{
    /* Your code goes here! */
	vector< vector<string> > temp_vector;

    for(auto it = dict.begin(); it != dict.end(); it++){
    	if(it->second.size() > 1)
    	temp_vector.push_back(it->second);
    }

	if(!temp_vector.empty())
		return temp_vector;
	else
    	return vector< vector<string> >();
}
