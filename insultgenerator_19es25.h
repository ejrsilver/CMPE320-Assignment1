//
//  insultgenerator_19es25.h
//  CMPE320-Assignment1
//
//  Created by Ethan Silver on 2022-09-09.
//

/* THIS IS A TEST OF CONVERSION FROM A LOCAL REPO TO A GITHUB REPO*/

using namespace std;

#ifndef insultgenerator_19es25_h
#define insultgenerator_19es25_h
#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <random>

class FileException:public exception {
  public:
    const char * what() const throw() {
      return "File not found!";
    }
};

class NumInsultsOutOfBounds:public exception {
  public:
    const char * what() const throw() {
      return "The number of insults cannot be greater than 10000 or less than 1";
    }
};

class InsultGenerator {
  
  public:
  
  void initialize() {
    ifstream myFile;
    myFile.open("./InsultsSource.txt");
    string s = "";
    
    string delim = "\t";
    int x = 0;
    if(myFile.is_open()) {
      while(getline(myFile, s)) {
        in1[x] = s.substr(0, s.find(delim));
        s.erase(0, s.find(delim) + delim.length());
        in2[x] = s.substr(0, s.find(delim));
        s.erase(0, s.find(delim) + delim.length());
        in3[x] = s.substr(0, s.find(delim));
        x++;
      }
    }
    else {
      throw system_error(error_code(), "File not found");
    }
    
    myFile.close();
  }
  
  string talkToMe() {
    string s = "";
    int x = generateRandom();
    s+= in1[(x-x%2500)/2500] + " " + in2[(x%2500 - x%50)/50] + " " + in3[x%50];
    
    return s;
  }
  
  vector<string> generate(int num) {
    if(num >= 0 && num <= 10000) {
      vector<string> voutput;
      int ran[num];
      for(int y = 0; y < num; y++) {
        int x = generateRandom();
        while(contains(ran, x, num)) {
          x = generateRandom();
        }
        ran[y] = x;
        int x1 = x%2500;
        int x2 = x%50;
        voutput.push_back(in1[(x-x1)/2500] + " " + in2[(x1 - x2)/50] + " " + in3[x2]);
      }
      return voutput;
    }
    else {
      throw NumInsultsOutOfBounds();
    }
  }
  
  vector<string> generateAndSave(string s, int num) {
    vector<string> voutput;
    
    return voutput;
  }
  
// Gap between public and private members
  
private:
  string in1[50];
  string in2[50];
  string in3[50];
  
  // Ensure results are unique. Algorithm is 20% faster when this method is removed.
  bool contains(int  *arr, int i, int index) {
    for(int x = 0; x < index; x++) {
      if(*(arr + x) == i) {
        return true;
      }
    }
    return false;
  }
  // I need to ask the prof about this. This is 50% faster, but is NOT actually random.
  int generateRandom() {
    return rand()%125000;
  }
  /*
  int generateRandom() {
    // Get a random value (truly random, from hardware)
    random_device rd;
    
    // Seed the 19937 state-size Mersenne Twister Engine. Not technically uniform, but closer than a Linear Congruential Generator and optimized for large sets. Starts with a random value from hardware.
    mt19937 gen(rd());
    
    // Conform the randomly generated output to a uniform distribution. There are 50^3 valid results, for a range of [0,124999].
    uniform_int_distribution<> distr(0, 124999);
    return distr(gen);
  }*/
};

#endif /* insultgenerator_19es25_h */
