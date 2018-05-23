#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <iterator>
#include "key_import.hpp"
#include "error_handler.hpp"

/* Interface to execute key import */
void Key::exec(int argc, byte** argv)
{
  if (!argchk(argc, argv)) {
    usage();
    std::exit(EXIT_FAILURE);
  }
  if (!cmd()) {
    std::exit(EXIT_FAILURE);
  }
}

/* accounts import username path-to-key*/
bool Key::argchk(int argc, byte** argv) 
{
  if (argc != MIN_ARG_CNT && argc != MAX_ARG_CNT) 
    return hndl_err(UsrErr::INVLD_ARG_CNT);

  set_arg_cnt(argc); /* set argument count */

  /* First 3 Arguments will remain same irrespective of
     argument count */
  main_arg_nam = std::string(argv[0]); /* main_arg_name */
  sub_arg_nam = std::string(argv[1]); /* sub_arg_name */
  usr_nam = std::string(argv[2]); /* username */


  if (main_arg_nam != MAIN_ARG_NAM) /* Incorrect main arg*/
    return hndl_err(UsrErr::INVLD_MAIN_ARG);
  
  if (sub_arg_nam != SUB_ARG_NAM) /* Incorrect sub arg */
    return hndl_err(UsrErr::INVLD_SUB_ARG);

  /* username needs to be checked if present or not */
  if ( !is_usr(usr_nam) ) /* user not present*/
    return hndl_err(UsrErr::INVLD_USR_NAM);
 
  if(!chk_cmd_prms(argv)) 
    return FAILURE;
    
  populate_arg_lst(argv);
  return SUCCESS;
}

void Key::set_arg_cnt(int argc)
{
  m_arg_cnt = static_cast<uint8_t>(argc);
}

/* populate m_arg_lst with command data */
void Key::populate_arg_lst(byte** argv)
{
  for (auto idx = 0; idx < m_arg_cnt; idx++)  {
    m_arg_lst.push_back(std::string(argv[idx]));
  }
}

/* check command parameters */
bool Key::chk_cmd_prms(byte** argv)
{
  if (m_arg_cnt == MIN_ARG_CNT) {
    /* TODO(raghu): normalize path to prevent path injection */
    std::ifstream key_path(argv[CMD_IDX + 1]);
    if ( !key_path.good())
      return hndl_err(UsrErr::INVLD_PATH);

  }
  if (m_arg_cnt == MAX_ARG_CNT) {
  
  }

  return SUCCESS;
}

/* Function to import key */
bool Key::cmd() 
{
  /* when key is copied and is present in the same system */
  if (m_arg_cnt == MIN_ARG_CNT) {
    if (vrfy_key()) {
      cp_key();
      return SUCCESS;
    }     
  }

  /* when key is present in remote system and needs to be imported */
  if (m_arg_cnt == MAX_ARG_CNT)
    return SUCCESS; /* TODO(raghu): connect to remote system and import the key */
  
  return FAILURE;
}

/* copy key to specified user home dir/.ssh/authorized_keys 
   if authorized_keys doesnot exist, then create one */
void Key::cp_key() 
{
  /* check if username/.ssh/authorized_keys exists */
  std::string auth_keys_path = HOME_DIR + 
                               std::string(m_arg_lst[CMD_IDX]) + /* username */
                               AUTHORIZED_KEYS;
  std::filebuf auth_keys, pub_key;
  auth_keys.open(auth_keys_path.c_str(), std::ios::app | std::ios::binary);
  pub_key.open(m_arg_lst[CMD_IDX + 1], std::ios::in | std::ios::binary);

  std::copy(std::istreambuf_iterator<byte>(&pub_key),
            {},
            std::ostreambuf_iterator<byte>(&auth_keys));
  
}


/* verify key provided by user */
bool Key::vrfy_key()
{
  std::string cmd = "ssh-keygen -lf ";
  cmd += m_arg_lst[MIN_ARG_CNT - 1]; /* get id_rsa */
 
  if (get_cmd_out(cmd.c_str()).empty()) /* we are suppressing stderr */
    return hndl_err(UsrErr::INVLD_KEY);

  return SUCCESS;
}

/* Function to show usage of Key import */
void Key::usage() 
{
  std::ostringstream out;
  out << "Usage: rolac copy username [path-to-public-key]"
      << std::endl;
  std::cout << out.str() << std::endl;
  std::exit(EXIT_FAILURE);
}
