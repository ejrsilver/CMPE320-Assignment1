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
#include <string>

class FileException:public exception {
  public:
    const char * what() const throw() {
      return "File not found!";
    }
};

class NumInsultsOutOfBounds:public exception {
  public:
    const char * what() const throw() {
      return "File not found!";
    }
};

class InsultGenerator {
  
  public:
    const char * what() const throw() {
      return "File not found!";
    }
private:
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
};

#endif /* insultgenerator_19es25_h */
