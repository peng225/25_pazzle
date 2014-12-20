#pragma once

#include <list>
#include <algorithm>
#include <math.h>
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
  int distance(shared_ptr<State> s);
  shared_ptr<State> drawBestState();
  void displaySolvedMessage(const shared_ptr<State> s) const;
  list<shared_ptr<State> > openState;
  list<shared_ptr<State> > closeState;
  list<shared_ptr<State> >::iterator
    findState(list<shared_ptr<State> >::iterator b,
	      list<shared_ptr<State> >::iterator e,
	      shared_ptr<State> s);
};
