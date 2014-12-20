#include "state.h"

/****************************************************
                   public methods
 ***************************************************/

// State::State(int value, int step, shared_ptr<State> parent)
// {
//   board.resize(NUM_PANEL);
  
//   for(int i = 0; i < NUM_PANEL - 1; i++){
//     board.at(i) = i;
//   }
//   board.at(NUM_PANEL - 1) = SPACE;

//   this->value = value;
//   this->step = step;
//   this->parent = parent;
// }

int State::getNumber(int pos) const
{
  return board[pos];
}

void State::setNumber(int pos, int num)
{
  board.at(pos) = num;
}


bool State::moveSpace(Direction dir)
{
  int spacePos;
  for(int i = 0; i < NUM_PANEL; i++){
    if(board.at(i) == SPACE){
      spacePos = i;
    }
  }

  switch(dir){
  case UP:
    if(spacePos / SIDE_LENGTH == 0){
      return false;
    }else{
      swapTwoPos(spacePos, spacePos - SIDE_LENGTH);
    }
    break;
  case RIGHT:
    if(spacePos % SIDE_LENGTH == SIDE_LENGTH - 1){
      return false;
    }else{
      swapTwoPos(spacePos, spacePos + 1);
    }
    break;
  case DOWN:
    if(spacePos / SIDE_LENGTH == SIDE_LENGTH - 1){
      return false;
    }else{
      swapTwoPos(spacePos, spacePos + SIDE_LENGTH);
    }
    break;
  case LEFT:
    if(spacePos % SIDE_LENGTH == 0){
      return false;
    }else{
      swapTwoPos(spacePos, spacePos - 1);
    }
    break;    
  }
  
  return true;
}

void State::display()
{
  for(int i = 0; i < NUM_PANEL; i++){
    if(board.at(i) == SPACE){
      cout << MULTIPLE_SPACE;
    }else{
      cout << setw(NUM_DISPLAY_WIDTH) << right << (int)board.at(i);
    }

    if(i % SIDE_LENGTH == SIDE_LENGTH - 1){
      cout << endl;
    }else{
      cout << SEPARATOR;
    }
  }
  cout << endl;
}

void State::shuffle(int numMove)
{
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::uniform_int_distribution<> dist(0, dir.size() - 1);
  int count = 0;
  while(count < numMove){
    if(moveSpace(dir.at(dist(engine)))){
      count++;
    }
  }
}


/****************************************************
                   private methods
 ***************************************************/

void State::swapTwoPos(int firstPos, int secondPos)
{
  assert(0 <= firstPos);
  assert(firstPos < NUM_PANEL);
  assert(0 <= secondPos);
  assert(secondPos < NUM_PANEL);
  
  int swapBuf = board.at(firstPos);
  board.at(firstPos) = board.at(secondPos);
  board.at(secondPos) = swapBuf;
}
