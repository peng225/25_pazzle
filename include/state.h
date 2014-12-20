#pragma once

#include <stdint.h>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <random>

using std::cout;
using std::endl;
using std::right;
using std::setw;
using std::string;
using std::vector;
using std::shared_ptr;

typedef uint8_t byte;

const int SIDE_LENGTH = 5;
const int NUM_PANEL = ((SIDE_LENGTH) * (SIDE_LENGTH));
const int SPACE = 0xff;
const int NUM_DISPLAY_WIDTH = 3;
const string MULTIPLE_SPACE = "   ";
const string SEPARATOR = " ";

enum Direction{UP, RIGHT, DOWN, LEFT};

const vector<Direction> dir = {UP, RIGHT, DOWN, LEFT};

class State
{
 public:
 State() : value(0), step(0), parent(NULL)
    {
      board.resize(NUM_PANEL);
  
      for(int i = 0; i < NUM_PANEL - 1; i++){
	board.at(i) = i;
      }
      board.at(NUM_PANEL - 1) = SPACE;
      /* board = {0, 1, 2, 3, 4, */
      /* 	       5, 6, 8, 13, 9, */
      /* 	       10, 11, 7, 18, 14, */
      /* 	       15, 16, 12, 22, SPACE, */
      /* 	       20, 21, 17, 23, 19}; */
    }
  /* State(int value, int step, shared_ptr<State> parent); */
  int getNumber(int pos) const;
  void setNumber(int pos, int num);
  bool moveSpace(Direction dir);
  void display();
  void shuffle(int numMove);
  bool operator==(const State& obj) const
  {
    for(int i = 0; i < NUM_PANEL; i++){
      if(board.at(i) != obj.getNumber(i)){
	return false;
      }
    }
    return true;
  }

  bool ordered() const
  {
    return (value - step == 0);
  }

  int getValue() const
  {
    return value;
  }

  void setValue(int value)
  {
    this->value = value;
  }

  int getStep() const
  {
    return step;
  }

  void incStep()
  {
    step++;
  }

  shared_ptr<State> getParent() const
  {
    return parent;
  }
  void setParent(shared_ptr<State> parent)
  {
    this->parent = parent;
  }
 private:
  int value;
  int step;
  vector<byte> board;  
  shared_ptr<State> parent;  
  void swapTwoPos(int firstPos, int secondPos);  
};
