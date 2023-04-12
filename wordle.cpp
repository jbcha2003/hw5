#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(int emptySpots, int currentLocation, string floating, string& word, set<string>& dict, set<string>& validWords, set<char> floatChars);

// Definition of primary wordle function
/*
 * test with: 
 *./wordle-driver -i-- dn
 * example input: 
 * wordle(-i-- dn)
 */
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<std::string> validWords;
    string fltChars = floating;
    set<char> floatChars;
    //add each floating character to the map
    for (char i : fltChars) {
       floatChars.insert(i);
    }
    string word = in;
    set<string> dictionary = dict;
    int emptySpots = 0;
    for (unsigned int i = 0; i < in.length(); i++) {
        //if empty spot, ....
        if (in[i] == '-') {
            emptySpots++;
        }
    }
    wordleHelper(emptySpots, 0, fltChars, word, dictionary, validWords, floatChars);
    return validWords;
}

void wordleHelper(
    int emptySpots, 
    int currentLocation, 
    string floating, 
    string& word, 
    set<string>& dict,
    set<string>& validWords,
    set<char> floatChars) 
{

    //use a map to check how many times we have used each float
    //use string to check if float has been used or not
    //check the size of the remaining floating to the number of empty emptySpots
    //place the alphabet one by one and check the remaining spots 
    //if the size of the floating is less than or equal to the number of empty spots, place them in the spots

    //if we have itereated through the whole word
    if (currentLocation >= word.size()) {
        if (dict.find(word) != dict.end()) {
            validWords.insert(word);
            return;
        }
        else {
            return;
        }
    }
    //if the current location is an empty spot
    else if (word[currentLocation] == '-') {
        //if there are remaining floating characters
        if (floating.size() == emptySpots) {
            //set<char> temp = floatChars;
            string temp = floating;
            //set<char>::iterator it = temp.begin();
            for (auto i : temp) {
                word[currentLocation] = i;
                //floatChars.erase(*it);
                floating.erase(floating.find(i), 1);
                wordleHelper(emptySpots - 1, currentLocation + 1, floating, word, dict, validWords, floatChars);
                //floatChars.insert(*it);
                floating+=i;
                word[currentLocation] = '-';
            }
        }
        //if there are no floating characters left
        else {
            string alphabet = "abcdefghijklmnopqrstuvwxyz";
            for (char letter : alphabet) {
                //check if the letter in the alphabet has been used already in the float
                //word[currentLocation - 1] = letter;
                //if the letter is in float
                if (floating.find(letter) != std::string::npos) {
                    word[currentLocation] = letter;
                    floating.erase(floating.find(letter), 1);
                    wordleHelper(emptySpots - 1, currentLocation + 1, floating, word, dict, validWords, floatChars);
                    word[currentLocation] = '-';
                    floating+=letter;
                }
                //if the letter is not in float
                else{
                    word[currentLocation] = letter;
                    wordleHelper(emptySpots - 1, currentLocation + 1, floating, word, dict, validWords, floatChars);
                    word[currentLocation] = '-';
                }
            }
        }
    }
    else if (word[currentLocation] != '-') {
        //cout <<"working";
        wordleHelper(emptySpots, currentLocation + 1, floating, word, dict, validWords, floatChars);
    }
    return;
}
