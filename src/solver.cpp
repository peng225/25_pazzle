#include "solver.h"

int Solver::solve(State &initState)
{
  cout << "start!" << endl;
  
  shared_ptr<State> initStatePtr = shared_ptr<State>(new State());  
  *initStatePtr = initState;  
  
  int dist = distance(initStatePtr);
  
  // 初期状態が解だったら終了
  if(dist == 0){
    displaySolvedMessage(initStatePtr);
    return 0;
  }  

  // 初期状態をopen stateに突っ込む
  initStatePtr->setParent(NULL);
  openState[*initStatePtr] = dist;

  while(!openState.empty()){
    shared_ptr<State> s = shared_ptr<State>(new State());
    *s = drawBestState();
    // 4方向に空白を動かす
    for(Direction d : dir){
      // コピーを作成
      shared_ptr<State> copyState = shared_ptr<State>(new State());
      *copyState = *s;
      
      // 方向dに動かすことができたら
      if(copyState->moveSpace(d)){
	dist = distance(copyState);
	copyState->incStep();
	copyState->setParent(s);
	
	// 解である
	if(dist == 0){
	  displaySolvedMessage(copyState);
	  return 0;
	}
	
	// close stateである
	if(closeState.find(*copyState) != end(closeState)){
	  // cout << "Copied state is already in the close state. Skip." << endl;
	  continue;
	}
	
	// unordered_map<State, int>::iterator found;
	map<State, int>::iterator found;
	
	// open stateである
	if((found = openState.find(*copyState)) != end(openState)){
	  // 既存のものより、新しいものの方が良ければupdate
	  if(dist + copyState->getStep() < found->second){
	    openState.erase(found);
	    openState[*copyState] = dist + copyState->getStep();
	  }else{
	    // cout << "Copied state is already in the open state, and it's worse than the one. Skip."
		 // << endl;
	  }
	}else{
	  openState[*copyState] = dist + copyState->getStep();
	}
      }      
    }
    closeState[*s] = 0;
  }
  return 0;
}

int Solver::distance(const shared_ptr<State> s) const
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

State Solver::drawBestState()
{
  // unordered_map<State, int>::iterator selected;
  map<State, int>::iterator selected;
  int minValue = LARGE;
  State s;
  // for(unordered_map<State, int>::iterator itr = begin(openState);
  for(map<State, int>::iterator itr = begin(openState);
      itr != end(openState); itr++){
    if(itr->second < minValue){
      minValue = itr->second;
      s = itr->first;
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

// list<shared_ptr<State> >::iterator
// Solver::findState(list<shared_ptr<State> >::iterator b,
// 		  list<shared_ptr<State> >::iterator e,
// 		  shared_ptr<State> s)
// {
//   for(list<shared_ptr<State> >::iterator itr = b;
//       itr != e; itr++){
//     if(**itr == *s){
//       return itr;
//     }
//   }
//   return e;
// }
