#include "state.h"
#include "solver.h"


int main()
{
  State s;
  s.shuffle(60);
  s.display();
  Solver solver;
  solver.solve(s);
  return 0;
}
