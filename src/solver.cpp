#include "solver.h"

int Solver::solve(State &initState)
{
  shared_ptr<State> initStatePtr = shared_ptr<State>(&initState);
  
  // 初期状態が解だったら終了
  if(initStatePtr->ordered()){
    displaySolvedMessage();
    return 0;
  }

  vector<Direction> dir = {UP, RIGHT, DOWN, LEFT};
  openState.push_back(initStatePtr);

  while(!openState.empty()){
    shared_ptr<State> s = drawBestState();
    if(s->ordered()){
      displaySolvedMessage();
      break;
    }else{
      for(Direction d : dir){
	shared_ptr<State> copyState;
	*copyState = *s;
	if(copyState->moveSpace(d)){
	  if(find(begin(closeState), end(closeState), copyState)
	     != end(closeState)){
	    continue;
	  }
	}

	list<shared_ptr<State> >::iterator found;
	if((found = find(begin(openState), end(openState), copyState))
	   != end(openState)){
	  if(copyState->getValue() < (*found)->getValue()){
	    copyState->setParent(s);
	    *found = copyState;
	  }
	}else{
	  copyState->setParent(s);
	  openState.push_back(copyState);
	}
      }
    }
  }
  return 0;
}

int Solver::evaluate(shared_ptr<State> s)
{
  return 0;
}

shared_ptr<State> Solver::drawBestState()
{
  list<shared_ptr<State> >::iterator selected;
  int minValue = LARGE;
  shared_ptr<State> s;
  for(list<shared_ptr<State> >::iterator itr = begin(openState);
      itr != end(openState); itr++){
    if((*itr)->getValue() < minValue){
      minValue = (*itr)->getValue();
      s = *itr;
      selected = itr;
    }
  }
  openState.erase(selected);
  return s;
}

void Solver::displaySolvedMessage() const
{
  cout << "Solved!" << endl;
}
