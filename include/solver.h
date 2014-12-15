#pragma once

#include <list>
#include <algorithm>
#include "state.h"

using std::list;
using std::begin;
using std::end;

const int LARGE = 100000;

class Solver
{
 public:  
  int solve(State &initState);
 private:
  int evaluate(shared_ptr<State> s);
  shared_ptr<State> drawBestState();
  void displaySolvedMessage() const;
  list<shared_ptr<State> > openState;
  list<shared_ptr<State> > closeState;
};
