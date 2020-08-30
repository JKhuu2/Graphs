//Jennifer Khuu, jtk2eh, April 21, 2020
//middleearth.h

/**
@file middleearth.h
 */

#ifndef MIDDLEEARTH_H
/**
@def MIDDLEEARTH_H
 */
#define MIDDLEEARTH_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <random>

/**
@namespace std
*/
using namespace std;

// see the comments in the lab11 write-up, or in middleearth.cpp

class MiddleEarth {
public:
  /**
     @brief MiddleEarth constructor

     Creates a world given the size and number of cities

     @param xsize Creates the size in the x dimension
     @param ysize Creates the size in the y dimension
     @param num_cities Denotes how many cities in this world
     @param seed Random seed

   */
    MiddleEarth(int xsize, int ysize, int num_cities, int seed);
    /**
       Prints out info on the created 'world'
     */
    void print();
    /**
        Prints a tab-separated table of the distances, which can be loaded into Excel or similar
     */
    void printTable();
    /**
       @brief Returns the distance between city1 and city2
       @param city1 First city
       @param city2 Second city
     */
    float getDistance(const string& city1, const string& city2);
    /**
       @brief Returns the list of cities to travel to
       
      Returns a vector of cities of size length+1 since length doesn't include the start city and the start city is the same as the end city
      @param length How many cities are in the itinerary
     */
    vector<string> getItinerary(unsigned int length);

private:
    /**
       @var int num_city_names
       number of cities
       @var int xsize
       x dimension of our world
       @var int ysize
       y dimension of our world
     */
    int num_city_names, xsize, ysize;
    /**
       map of x position and y position
     */
    unordered_map<string, float> xpos, ypos;
    /**
       vector of cities
     */
    vector<string> cities;
    /**
       a map of distances
     */
    unordered_map<string, unordered_map<string, float>> distances;
    /**
       Mersenne-Twister random number engine
     */
    mt19937 gen; // Mersenne-Twister random number engine
};

#endif
