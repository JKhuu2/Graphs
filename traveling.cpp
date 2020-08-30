//Jennifer Khuu, jtk2eh, April 23, 2020
//traveling.cpp

/**
   @file traveling.cpp
 */

#include <iostream>
#include <cstdlib>
#include <algorithm>

/**
   @namespace std
 */
using namespace std;

#include "middleearth.h"

float computeDistance(MiddleEarth me, const string& start, vector<string> dests);
void printRoute(const string& start, const vector<string>& dests);
/**
   It will first sort all of the cities not including the start city and then go through all of the permutations until it find the one with the shortest distance and then print out the destinations in order for that distance.
   @todo Input five parameters that specify the width, height, number of cities, random seed, and number of cities to visit.
 */
int main(int argc, char** argv) {
    // check the number of parameters
    if (argc != 6) {
        cout << "Usage: " << argv[0] << " <world_height> <world_width> "
             << "<num_cities> <random_seed> <cities_to_visit>" << endl;
        exit(0);
    }

    // we'll assume the parameters are all well-formed
    int width = stoi(argv[1]);
    int height = stoi(argv[2]);
    int num_cities = stoi(argv[3]);
    int rand_seed = stoi(argv[4]);
    int cities_to_visit = stoi(argv[5]);

    // create the world, and select your itinerary
    MiddleEarth me(width, height, num_cities, rand_seed);
    vector<string> dests = me.getItinerary(cities_to_visit);

    //sort the cities not including the start city
    sort(dests.begin()+1,dests.end());
    
    string start=dests.at(0);
    float minDist=computeDistance(me,start,dests);;
    float tempDist=0;
    vector<string>minDests=dests;

    //call next_permutation on all cities except the starting city
    while(next_permutation(dests.begin()+1,dests.end())){
      tempDist=computeDistance(me,start,dests);
      if(tempDist<minDist){
	minDist=tempDist;
	minDests=dests;
      }
    }

    //print
    start=minDests.at(0);
    cout<<"Minimum path has distance "<<minDist<<": ";
    printRoute(start,minDests);
    return 0;
}

/**
   This method will compute the full distance of the cycle that starts at the 'start' parameter, goes to each of the cities in the dests vector IN ORDER, and ends back at the 'start' parameter.
   @param me The world we're looking at
   @param start Starting city
   @param dests Vector of destination cities
 */
float computeDistance(MiddleEarth me, const string& start, vector<string> dests) {
    float distance=0.0;
    string begin=start;
    //get the total distance between each city
    for(int i=0;i<dests.size();i++){
      distance+=me.getDistance(begin,dests.at(i));
      begin=dests.at(i);
    }
    //add on the distance on the way back to start city
    distance+=me.getDistance(dests.back(),dests.at(0));
    return distance;
}

/**
   This method will print the entire route, starting and ending at the 'start' parameter. The output should be similar to: Erebor -> Khazad-dum -> Michel Delving -> Bree -> Cirith Ungol -> Erebor
   @param start Starting city
   @param dests Vector of destination cities
*/
void printRoute(const string& start, const vector<string>& dests) {
    for(int i=0;i<dests.size();i++){
      cout<<dests.at(i)<<" -> ";
    }
    cout<<start<<endl;
}
