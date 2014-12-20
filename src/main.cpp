#include "state.h"
#include "solver.h"


int main()
{
  State s;
  // s.shuffle(80);
  s.display();
  Solver solver;
  solver.solve(s);
  return 0;
}
