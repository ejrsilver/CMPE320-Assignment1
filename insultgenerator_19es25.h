//
//  insultgenerator_19es25.h
//  CMPE320-Assignment1
//
//  Created by Ethan Silver on 2022-09-09.
//

using namespace std;

#ifndef insultgenerator_19es25_h
#define insultgenerator_19es25_h
#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string.h>
#include <vector>

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
    const char * what() const throw() {
      return "File not found!";
    }
  
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
  }
  
  string talkToMe() {
    long *p;
    string s;
    p = generateRandom(10, 15005, 8371, 19993, 100);
    for(int x = 0; x < 100; x++) {
      s += *(p + x) + "\n";
    }
    return "";
  }
  
  vector<string> generate(int num) {
    vector<string> voutput;
    
    return voutput;
  }
  
  vector<string> generateAndSave(string s, int num) {
    vector<string> voutput;
    
    return voutput;
  }
  
// Gap between public and private members
  
private:
  // Methodology for input selection: Finding near optimal parameters for Linear Congruential Pseudorandom Number Generators by means of Evolutionary Computation
  string in1[50];
  string in2[50];
  string in3[50];
  long * generateRandom (long x0, long a, int b ,int m, int n) {
    long *r[n];
    // Linear congurential generator for n inputs
    for(int i = 0;i < n; i++) {
      x0 = (a * x0 + b) % m;
      *r[i] = x0;
    }
    return r[n];
  }

  
};

#endif /* insultgenerator_19es25_h */
