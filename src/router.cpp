#include <iostream>
#include <vector>
#include <ostream>
#include <fstream>
#include <cassert>
#include <map>
#include <string>
#include "key_import.hpp"
#include "user_create.hpp"
#include "user_delete.hpp"
#include "router.hpp"

Router::Router(int argc, char** argv )
{
  init_rolac_typ_map();
  route(argc, argv);
}

void Router::route(int argc, char** argv)
{
  switch(get_type(argv[1])) {
  
  case RolacType::CREATE: {
              Create create;
              create.exec(argc, argv);
              break;
  }
  case RolacType::DELETE: {
	      Delete del;
	      del.exec(argc, argv);
	      break; 
  }
  case RolacType::MODIFY: break; // TODO(raghu): complete modify
  case RolacType::LOCKOUT: break; // TODO(raghu): complete lockout
  case RolacType::COPY: { 
             Key key;
             key.exec(argc, argv);
             break;
  }
  default: break;
  }
}


RolacType Router::get_type(char* sub_arg)
{ 
  std::string sub_arg_str(sub_arg);
  auto rolac_iter = rolac_typ_map.find(sub_arg_str);
  if (rolac_iter != rolac_typ_map.end())
    return rolac_iter->second;

  return RolacType::INVALID;
}

void Router::init_rolac_typ_map()
{
  rolac_typ_map["create"] = RolacType::CREATE;
  rolac_typ_map["delete"] = RolacType::DELETE;
  rolac_typ_map["modify"] = RolacType::MODIFY;
  rolac_typ_map["lockout"] = RolacType::LOCKOUT;
  rolac_typ_map["copy"] = RolacType::COPY;
}
