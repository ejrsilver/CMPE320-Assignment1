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

#include <vector>
#include <string>
#include <random>

class FileException:public exception {
  public:
  const char * what() const throw();
};

class NumInsultsOutOfBounds:public exception {
  public:
  const char * what() const throw();
};


class InsultGenerator {
  
  public:
  
  void initialize();
  
  // Generate and return a randomly generated insult
  string talkToMe();
  

  vector<string> generate(int num);
  
  vector<string> generateAndSave(string s, int num);
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
  bool contains(int  *arr, int i, int index);
  
  // This random generator is slightly slower on average than the srand and rand functions, but produces a nearly uniform distribution of results. Since the goal is primarily to generate random values, and the performance difference was only ~2ms, the Mersenne won out.
  int generateRandom();
};

#endif /* insultgenerator_19es25_h */
