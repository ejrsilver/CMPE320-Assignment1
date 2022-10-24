//
//  insultgenerator_19es25.h
//  CMPE320-Assignment1
//
//  Created by Ethan Silver on 2022-09-09.
//

#ifndef insultgenerator_19es25_h
#define insultgenerator_19es25_h

#include <vector>
#include <string>
#include <random>

class FileException:public std::exception {
  public:
  const char * what() const throw();
};

class NumInsultsOutOfBounds:public std::exception {
  public:
  const char * what() const throw();
};


class InsultGenerator {
  
  public:
  
  void initialize();
  
  // Generate and return a randomly generated insult
  std::string talkToMe();
  

  std::vector<std::string> generate(const int num);
  
  std::vector<std::string> generateAndSave(const std::string &s, const int num);
  // Gap between public and private members
  
  private:
  // Random number generator. Fully random, but entropy pool is limited so only being used for seeding.
  std::random_device rd;
  
  // 19937 state-size Mersenne Twister Engine. Not quite random, but more random than an LCG.
  std::mt19937 gen;
  
  // Conform the randomly generated output to a uniform distribution. There are 50^3 valid results, for a range of [0,124999].
  std::uniform_int_distribution<> distr;
  
  std::string in1[50];
  std::string in2[50];
  std::string in3[50];
  
  // Ensure results are unique. Binary search was ultimately much slower, as the array need to be resorted every time. C++'s built-in find function was also slower on average.
  bool contains(const int  * arr, const int i, const int index);
  
  // This random generator is slightly slower on average than the srand and rand functions, but produces a nearly uniform distribution of results. Since the goal is primarily to generate random values, and the performance difference was only ~2ms, the Mersenne won out.
  int generateRandom();
};

#endif /* insultgenerator_19es25_h */
