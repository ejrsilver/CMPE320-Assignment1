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
  string talkToMe() {
    int x = generateRandom();
    return (in1[(x-x%2500)/2500] + " " + in2[(x%2500 - x%50)/50] + " " + in3[x%50]);
  }
  

  vector<string> generate(int num) {
    if(num >= 0 && num <= 10000) {
      
      vector<string> voutput;
      
      // Random values are generated, compared against existing results to ensure unique outputs, then sorted.
      int ran[num];
      for(int y = 0; y < num; y++) {
        int x = generateRandom();
        while(contains(ran, x, num)) {
          x = generateRandom();
        }
        ran[y] = x;
      }
      sort(ran, ran+num);
      
      // Integers from sorted array are decoded into indexes for the three arrays. Those indexes are used to write the insult to an output vector and output file.
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
  
  vector<string> generateAndSave(string s, int num) {
    if(num >= 0 && num <= 10000) {
      
      // Open output file
      ofstream writeOut;
      writeOut.open(s);
      
      vector<string> voutput;
      
      // Random values are generated, compared against existing results to ensure unique outputs, then sorted.
      int ran[num];
      
      for(int y = 0; y < num; y++) {
        int x = generateRandom();
        while(contains(ran, x, num)) {
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
  
// Gap between public and private members
  
private:
  // Random number generator. Fully random, but entropy pool is limited so only being used for seeding.
  random_device rd;
  
  // 19937 state-size Mersenne Twister Engine. Not quite random, but more random than an LCG.
  mt19937 gen;
  
  // Conform the randomly generated output to a uniform distribution. There are 50^3 valid results, for a range of [0,124999].
  uniform_int_distribution<> distr = uniform_int_distribution<>(0,124999);
  
  string in1[50];
  string in2[50];
  string in3[50];
  
  // Ensure results are unique. Binary search was ultimately much slower, as the array need to be resorted every time. C++'s built-in find function was also slower on average.
  bool contains(int  *arr, int i, int index) {
    for(int x = 0; x < index; x++) {
      if(*(arr + x) == i) {
        return true;
      }
    }
    return false;
  }
  
  // This random generator is slightly slower on average than the srand and rand functions, but produces a nearly uniform distribution of results. Since the goal is primarily to generate random values, and the performance difference was only ~2ms, the Mersenne won out.
  int generateRandom() {
    return distr(gen);
  }
};

#endif /* insultgenerator_19es25_h */
