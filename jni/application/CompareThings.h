#ifndef COMPARETHINGS_H
#define COMPARETHINGS_H

#include "Thing.h"

using namespace std;
using namespace Zeni;

class CompareThings {
  public:
    static bool compare(Thing * t1, Thing * t2){ // True if t1 should be rendered after t2
      // Orders by depth (lowest first)
      // Then Weapons, Me, Person, others
      if (t1->getDepth() > t2->getDepth()) {
        return false;
      } else if (t1->getDepth() == t2->getDepth()) {
        if (t2->type & WEAPON) {
          return false;
        } else if (t1->type & WEAPON) {
          return true;
        }
        if (t2->type & ME) {
          return false;
        } else if (t1->type & ME) {
          return true;
        }
        if (t2->type & PERSON) {
          return false;
        } else if (t1->type & PERSON) {
          return true;
        }
      }
      return true;
    }
};

#endif // HEADER FILE
