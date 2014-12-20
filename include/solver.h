#pragma once

#include <list>
/* #include <unordered_map> */
#include <map>
#include <algorithm>
#include <math.h>
#include "state.h"

using std::list;
/* using std::unordered_map; */
using std::map;
using std::begin;
using std::end;

const int LARGE = 100000;

/* namespace std { */
/*   template <> */
/*     class hash<State> { */
/*   public: */
/*     size_t operator()(const State &x) const{ */
/*       size_t xorSum = 0; */
/*       for(int i = 0; i < SIDE_LENGTH; i++){ */
/* 	xorSum ^= hash<int>()(x.getNumber(i)); */
/*       } */
/*       return xorSum; */
/*     } */
/*   }; */
/* } */

class Solver
{
 public:  
  int solve(State &initState);
 private:
  int distance(const shared_ptr<State> s) const;
  State drawBestState();
  void displaySolvedMessage(const shared_ptr<State> s) const;
  /* unordered_map<State, int> openState; */
  /* unordered_map<State, int> closeState; */
  map<State, int> openState;
  map<State, int> closeState;
  /* list<shared_ptr<State> > openState; */
  /* list<shared_ptr<State> > closeState; */  
  /* list<shared_ptr<State> >::iterator */
  /*   findState(list<shared_ptr<State> >::iterator b, */
  /* 	      list<shared_ptr<State> >::iterator e, */
  /* 	      shared_ptr<State> s); */
};
