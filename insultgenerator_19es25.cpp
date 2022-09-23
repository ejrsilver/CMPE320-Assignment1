//
//  insultgenerator_19es25.cpp
//  CMPE320-Assignment1
//
//  Created by Ethan Silver on 2022-09-13.
//

#include <stdio.h>
#include "insultgenerator_19es25.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <random>


const char * FileException::what() const throw() {
      return "File not found!";
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
  

  vector<string> InsultGenerator::generate(int num) {
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
         likely to generate the same value repeatedly than the traditional library, as a linear congruential generator
         isn't very random, and will eventually repeat values*/
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
        voutput.push_back(in1[(ran[i]-x1)/2500] + " " + in2[(x1 - x2)/50] + " " + in3[x2]);
      }
      return voutput;
    }
    else {
      throw NumInsultsOutOfBounds();
    }
  }
  
  vector<string> InsultGenerator::generateAndSave(string s, int num) {
    if(num >= 0 && num <= 10000) {
      
      // Open output file
      ofstream writeOut;
      writeOut.open(s);
      
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
      
      // Integers from sorted array are decoded into indexes for the three arrays. Those indexes are used to write the insult to an output vector and output file.
      for(int i = 0; i < num; i++) {
        int x1 = ran[i]%2500;
        int x2 = ran[i]%50;
        string sout = in1[(ran[i]-x1)/2500] + " " + in2[(x1 - x2)/50] + " " + in3[x2];
        voutput.push_back(sout);
        writeOut << (sout) <<endl;
      }
      return voutput;
    }
    else {
      throw NumInsultsOutOfBounds();
    }
  }
  
  // Ensure results are unique. Binary search was ultimately much slower with overhead. C++'s built-in find function was also slower on average.
  bool InsultGenerator::contains(int  *arr, int i, int index) {
    for(int x = 0; x < index; x++) {
      if(*(arr + x) == i) {
        return true;
      }
    }
    return false;
  }
  
  // This random generator is slightly slower on average than the srand and rand functions, but produces a nearly uniform distribution of results. Since the goal is primarily to generate random values, and the performance difference was only ~2ms, the Mersenne won out.
  int InsultGenerator::generateRandom() {
    distr = uniform_int_distribution<>(0,124999);
    return distr(gen);
  }

/*
 This is an odd result. When testing my program at home, It get speeds around
 185ms, with a range of about 10ms. When I ran the same code in class, my performance was around 275ms, with a range of about 20ms. It's possible that startup or other processes limited performance in class, and that running the same test in Stauf after working for a few hours might produce the same results as at home. If anything, home results should be worse since the processor needs to dedicate far more cycles to I/O requests.*/
