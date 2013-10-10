#ifndef THINGSLIST_H
#define THINGSLIST_H

#include <algorithm>
#include <vector>
#include "CompareThings.h"

using namespace std;

class ThingsList {
public:
  ThingsList() {}
  
  Thing * operator[] (int n) {
    return queue[n];
  }
  
  int length() {
    return queue.size();
  }
  
  void reorder() {
    make_heap(queue.begin(), queue.end(), CompareThings::compare);
    sort_heap(queue.begin(), queue.end(), CompareThings::compare);
  }
  
  void append(Thing* thing) {
    queue.push_back(thing);
    reorder();
    last = thing;
  }
  
  Thing * remove(int n) {
    Thing * result = queue[n];
    queue.erase(queue.begin()+n);
    return result;
  }
  
  Thing * top() {
    return queue.front();
  }
  
  Thing * pop() {
    Thing * result = queue.front();
    queue.erase(queue.begin());
    return result;
  }
  
  Thing * newest() {
    return last;
  }
  
  bool empty() {
    return queue.empty();
  }
  
  
  
private:
  vector<Thing *> queue;
  Thing * last;
};

#endif // HEADER FILE
