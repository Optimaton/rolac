#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
// #include "boost/filesystem.hpp"
#include "rolac.hpp"

/* Check if user is present */
bool Rolac::is_usr(std::string usr_nam)
{
  /* compile list of users to eliminate comparision with garbage values in /etc/passwd  
     ex. /etc/passwd could contain username:garbagehash - and user could actually mess if 
     wanted
  */

  std::vector<std::string> usr_lst;
  std::ifstream passwd;
  passwd.open(passwd_path.c_str());
  std::string line;
  uint16_t pos, orig = 0;
  if (!passwd.bad()) {
    while (getline(passwd, line)) {
      if ((pos =  line.find(SEPARATOR, orig)) != std::string::npos) {
        usr_lst.push_back(line.substr(orig, pos));
      }
    }
  }

  for (auto& usr : usr_lst) {
    if (usr == usr_nam)
      return SUCCESS;
  }
  
  return FAILURE;
}

/* Return cmd output if any */
std::string Rolac::get_cmd_out(std::string cmd)
{
  std::string suppress_stderr = " 2> /dev/null"; /* suppress stderr */
  cmd += suppress_stderr; /* append to cmd */
  std::array<byte, 128> buff;
  std::string res;
  std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
  if (!pipe)
    throw std::runtime_error("popen failed !");
  while (!feof(pipe.get())) {
    if (fgets(buff.data(), 128, pipe.get()) !=  nullptr)
      res += buff.data(); /* does not take into account stderr output */
  }
  return res;
}
