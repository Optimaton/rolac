#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <cstdio>
#include "user_delete.hpp"
#include "error_handler.hpp"

/* Interface to execute user delete command */
void Delete::exec(int argc, byte** argv)
{
  if (!argchk(argc, argv)) {
    usage();
    std::exit(EXIT_FAILURE);
  }
  if (!cmd()) {
    std::exit(EXIT_FAILURE);
  }
}

/* accounts delete username */
bool Delete::argchk(int argc, byte** argv) 
{
  if (argc != MIN_ARG_CNT && argc != MAX_ARG_CNT) 
    return hndl_err(UsrErr::INVLD_ARG_CNT);

  set_arg_cnt(argc); /* set argument count */

  /* First 3 Arguments will remain same irrespective of
     argument count */
  main_arg_nam = std::string(argv[0]); /* main_arg_name */
  sub_arg_nam = std::string(argv[1]); /* sub_arg_name */
  usr_nam = std::string(argv[2]); /* username */


  if (main_arg_nam != MAIN_ARG_NAM && main_arg_nam != MAIN_ARG_NAM2) /* Incorrect main arg*/
    return hndl_err(UsrErr::INVLD_MAIN_ARG);
  
  if (sub_arg_nam != SUB_ARG_NAM) /* Incorrect sub arg */
    return hndl_err(UsrErr::INVLD_SUB_ARG);

  /* username needs to be checked if present or not */
  if (!is_usr(usr_nam) ) /* user not present*/
    return hndl_err(UsrErr::INVLD_USR_NAM);
    
  populate_arg_lst(argv);
  return SUCCESS;
}

void Delete::set_arg_cnt(int argc)
{
  m_arg_cnt = static_cast<uint8_t>(argc);
}

/* populate m_arg_lst with command data */
void Delete::populate_arg_lst(byte** argv)
{
  for (auto idx = 0; idx < m_arg_cnt; idx++)  {
    m_arg_lst.push_back(std::string(argv[idx]));
  }
}

/* execute delete user command and return status */
bool Delete::cmd() 
{
  delete_usr();
  return m_is_usr_deleted;
}

void Delete::delete_usr() 
{
  std::string cmd = std::string("userdel -r ") +
	  	    m_arg_lst[CMD_IDX];
  if (get_cmd_out(cmd.c_str()).empty() && get_sta_code() != 0)
	  m_is_usr_deleted = hndl_err(IntrnlErr::USR_DELETION_FAILED);

  m_is_usr_deleted = SUCCESS;
}

/* Function to show usage of Delete */
void Delete::usage() 
{
  std::ostringstream out;
  out << "Usage: rolac delete \"username\""
      << std::endl;
  std::cout << out.str() << std::endl;
  std::exit(EXIT_FAILURE);
}

