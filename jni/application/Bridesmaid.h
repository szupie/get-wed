#ifndef BRIDESMAID_H
#define BRIDESMAID_H

#include <zenilib.h>
#include "Person.h"

using namespace std;
using namespace Zeni;

class Bridesmaid : public Person {
  public:
    Bridesmaid(float x=0, float y=0, float size=0, float depth=1);
    virtual bool isSatisfied();
    vector<string> feelings;
    int currentFeeling;
  
  static vector< vector<string> > allFeelings;
  static void initFeelings();
};

class Hobo : public Person {
  public:
    Hobo(float x=0, float y=0, float size=0, float depth=1);
    virtual bool isSatisfied();
};

#endif // HEADER FILE
