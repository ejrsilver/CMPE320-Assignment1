//
//  insultgenerator_19es25.cpp
//  CMPE320-Assignment1
//
//  Created by Ethan Silver on 2022-09-13.
//

#include <stdio.h>
#include "insultgenerator_19es25.hpp"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <random>


const char * FileException::what() const throw() {
      return "File could not be opened!";
};

const char * NumInsultsOutOfBounds::what() const throw() {
  return "The number of insults cannot be greater than 10000 or less than 1";
};


void InsultGenerator::initialize() {
  // Seed the Mersenne Twister. Not technically uniform, but closer than a Linear Congruential Generator and optimized for large sets. Starts with a random value from hardware.
  gen.seed(rd());
  
  // Open the input file. Hopefully your IDE allows custom working directories, because that's how I got this pathname to work.
  ifstream myFile;
  myFile.open("./InsultsSource.txt");
  string s = "";
  
  string delim = "\t";
  int x = 0;
  if(myFile.is_open()) {
    while(getline(myFile, s)) {
      // Get the first word, then erase it so the next can be retrieved
      in1[x] = s.substr(0, s.find(delim));
      s.erase(0, s.find(delim) + delim.length());
      
      in2[x] = s.substr(0, s.find(delim));
      s.erase(0, s.find(delim) + delim.length());
      
      in3[x] = s.substr(0, s.find(delim));
      
      x++;
    }
  }
  else {
    throw FileException();
  }
  myFile.close();
  }
  
  // Generate and return a randomly generated insult
  string InsultGenerator::talkToMe() {
    int x = generateRandom();
    return (in1[(x-x%2500)/2500] + " " + in2[(x%2500 - x%50)/50] + " " + in3[x%50]);
  }
  

  vector<string> InsultGenerator::generate(const int num) {
    if(num >= 0 && num <= 10000) {
      
      vector<string> voutput;
      
      /*Random values are generated, compared against existing results to ensure unique outputs, then sorted.
       Worst case for the algorithm is infinite, but average case is closer to nlog(n). Can't think of a way to
       reliably improve performance.*/
      int ran[num];
      for(int y = 0; y < num; y++) {
        
        // Create a new random integer in the range 0-124999
        int x = generateRandom();
        
        /* Continue generating and checking new random values until one isn't in the array. This could
         technically run forever, since that's the nature of random values. The Mersenne Twister is much less
         likely to generate the same value repeatedly than rand(), so this is less of a concern. */
        while(contains(ran, x, y)) {
          x = generateRandom();
        }
        ran[y] = x;
      }
      sort(ran, ran+num);
      
      /* Integers from sorted array are decoded into indexes for the three arrays.
       Those indexes are used to write the insult to an output vector. */
      for(int i = 0; i < num; i++) {
        int x1 = ran[i]%2500;
        int x2 = ran[i]%50;
        voutput.push_back(in1[(ran[i]-x1)/2500] + " " + in2[(x1 - x2)/50] + " " + in3[x2]);
      }
      return voutput;
    }
    else {
      throw NumInsultsOutOfBounds();
    }
  }
  
  vector<string> InsultGenerator::generateAndSave(const string &s, const int num) {
    if(num >= 0 && num <= 10000) {
      
      // Open output file
      ofstream writeOut;
      writeOut.open(s);
      
      // If the output file opened properly. It should always be true, since ofstream.open will create a file if none is found.
      if(writeOut.is_open()) {
        vector<string> voutput;
        
        // Random values are generated, compared against existing results to ensure unique outputs, then sorted.
        int ran[num];
        
        for(int y = 0; y < num; y++) {
          int x = generateRandom();
          while(contains(ran, x, y)) {
            x = generateRandom();
          }
          ran[y] = x;
        }
        sort(ran, ran+num);
        
        /* Integers from sorted array are decoded into indexes for the three arrays.
         Those indexes are used to write the insult to an output vector and output file. */
        for(int i = 0; i < num; i++) {
          int x1 = ran[i]%2500;
          int x2 = ran[i]%50;
          string sout = in1[(ran[i]-x1)/2500] + " " + in2[(x1 - x2)/50] + " " + in3[x2];
          voutput.push_back(sout);
          writeOut << (sout) <<endl;
        }
        writeOut.close();
        return voutput;
      }
      else {
        throw FileException();
      }
    }
    else {
      throw NumInsultsOutOfBounds();
    }
  }
  
  // Ensure results are unique. Binary search was ultimately much slower with overhead. C++'s built-in find function was also slower on average.
  bool InsultGenerator::contains(const int  *arr, const int i, const int index) {
    for(int x = 0; x < index; x++) {
      if(*(arr + x) == i) {
        return true;
      }
    }
    return false;
  }
  
  // Generate a nearly-random value in the range 0-124999. Not perfectly random, but more random than rand() and srand().
  int InsultGenerator::generateRandom() {
    distr = uniform_int_distribution<>(0,124999);
    return distr(gen);
  }
