#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <fstream>
#include <cassert>
// #include "boost/filesystem.hpp"
#include "key_import.hpp"

int main(int argc, char** argv)
{
  /* Test SSH Key Feature */
  Key key;
  key.exec(argc, argv);
  return 0; 
}



