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
 State() : step(0), parent(NULL)
    {
      board.resize(NUM_PANEL);
  
      for(int i = 0; i < NUM_PANEL - 1; i++){
	board.at(i) = i;
      }
      board.at(NUM_PANEL - 1) = SPACE;
      board = {
	5, 0, 3, 8, 4,
	1, 17, 6, 2, 9,
	15, 12, SPACE, 18, 13,
	7, 10, 16, 14, 19,
	20, 11, 21, 22, 23};
    }
  int getNumber(int pos) const;
  void setNumber(int pos, int num);
  bool moveSpace(Direction dir);
  void display();
  void shuffle(int numMove);
  /* bool operator==(const State& obj) const */
  /* { */
  /*   for(int i = 0; i < NUM_PANEL; i++){ */
  /*     if(board.at(i) != obj.getNumber(i)){ */
  /* 	return false; */
  /*     } */
  /*   } */
  /*   return true; */
  /* } */
  bool operator<(const State& obj) const
  {
    for(int i = 0; i < NUM_PANEL; i++){
      if(board.at(i) < obj.getNumber(i)){
  	return true;
      }else if(board.at(i) > obj.getNumber(i)){
  	return false;
      }
    }
    return false;
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
  int step;
  vector<byte> board;  
  shared_ptr<State> parent;
  void swapTwoPos(int firstPos, int secondPos);  
};
