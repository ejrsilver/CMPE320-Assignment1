//
//  main.cpp
//  CMPE320-Assignment1
//
//  Created by Ethan Silver on 2022-09-08.
//

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

string in1[50];
string in2[50];
string in3[50];

void generateRandom (long x0, long a, int b ,int m, int n) {
  long r[n];
  for(int i = 0;i < n; i++) {
    x0 = (a * x0 + b) % m;
    r[i] = x0;
  }
  
}

void initialize() {
  ifstream myFile;
  myFile.open("./InsultsSource.txt");
  string s;
  
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
  /*
  cout << (112457 - 112457%(50*50))/(50*50) << endl;
  cout << (112457%(50*50) - 112457%50)/50 << endl;
  cout << 112457%50 << endl;*/
}

int main(int argc, const char * argv[]) {
  initialize();
}
