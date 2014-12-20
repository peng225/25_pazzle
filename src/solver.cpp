#include "solver.h"

int Solver::solve(State &initState)
{
  shared_ptr<State> initStatePtr = shared_ptr<State>(new State());  
  *initStatePtr = initState;  

  int dist = distance(initStatePtr);
  initStatePtr->setValue(dist);
  initStatePtr->setParent(NULL);

  cout << "start!" << endl;
  
  // 初期状態が解だったら終了
  if(initStatePtr->ordered()){
    displaySolvedMessage(initStatePtr);
    return 0;
  }

  // 初期状態をopen stateに突っ込む
  openState.push_back(initStatePtr);

  while(!openState.empty()){
    shared_ptr<State> s = drawBestState();
    if(s->ordered()){
      displaySolvedMessage(s);
      break;
    }else{      
      for(Direction d : dir){
	shared_ptr<State> copyState = shared_ptr<State>(new State());
	*copyState = *s;
	if(copyState->moveSpace(d)){
	  if(findState(begin(closeState), end(closeState), copyState)
	     != end(closeState)){
	    // cout << "Copied state is already in the close state. Skip." << endl;
	    continue;
	  }
	}

	dist = distance(copyState);
	copyState->incStep();
	copyState->setValue(dist + copyState->getStep());
	copyState->setParent(s);
	list<shared_ptr<State> >::iterator found;
	if((found = findState(begin(openState), end(openState), copyState))
	   != end(openState)){
	  if(copyState->getValue() < (*found)->getValue()){
	    *found = copyState;
	  }else{
	    // cout << "Copied state is already in the open state, and it's worse than the one. Skip."
		 // << endl;
	  }
	}else{
	  openState.push_back(copyState);
	}
      }
      closeState.push_back(s);
    }
  }
  return 0;
}

int Solver::distance(shared_ptr<State> s)
{
  int sumDistance = 0;
  for(int i = 0; i < NUM_PANEL; i++){
    int x = i % SIDE_LENGTH;
    int y = i / SIDE_LENGTH;
    int rightX, rightY;
    if(s->getNumber(i) == SPACE){      
      rightX = (NUM_PANEL - 1) % SIDE_LENGTH;
      rightY = (NUM_PANEL - 1) / SIDE_LENGTH;
    }else{
      rightX = s->getNumber(i) % SIDE_LENGTH;
      rightY = s->getNumber(i) / SIDE_LENGTH;
    }
    sumDistance += abs(x - rightX) + abs(y - rightY);
  }
  return sumDistance;
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

void Solver::displaySolvedMessage(const shared_ptr<State> s) const
{
  cout << "Solved!" << endl;
  cout << "step: " << s->getStep() << endl;

  shared_ptr<State> ptr = s;
  list<shared_ptr<State> > answerStates;
  while(ptr != NULL){
    answerStates.push_back(ptr);
    ptr = ptr->getParent();
  }

  answerStates.reverse();
  for(list<shared_ptr<State> >::iterator itr = begin(answerStates);
      itr != end(answerStates); itr++){
    (*itr)->display();
  }
}

list<shared_ptr<State> >::iterator
Solver::findState(list<shared_ptr<State> >::iterator b,
		  list<shared_ptr<State> >::iterator e,
		  shared_ptr<State> s)
{
  for(list<shared_ptr<State> >::iterator itr = b;
      itr != e; itr++){
    if(**itr == *s){
      return itr;
    }
  }
  return e;
}
