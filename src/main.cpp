#include <cassert>
#include <map>
#include <string>
#include "router.hpp"

int main(int argc, char** argv)
{
  assert(argc >= 2);
  Router route(argc, argv);
  return 0; 
}



