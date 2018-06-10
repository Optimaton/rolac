#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <random>
#include <termios.h>
#include <unistd.h>
#include <crypt.h>
#include "user_create.hpp"
#include "error_handler.hpp"

/* Interface to execute key import */
void Create::exec(int argc, byte** argv)
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
bool Create::argchk(int argc, byte** argv) 
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
  if (is_usr(usr_nam) ) /* user present*/
    return hndl_err(UsrErr::USR_ALREADY_PRSNT);
 
  if(!chk_cmd_prms(argv)) 
    return FAILURE;
    
  populate_arg_lst(argv);
  return SUCCESS;
}

void Create::set_arg_cnt(int argc)
{
  m_arg_cnt = static_cast<uint8_t>(argc);
}

/* populate m_arg_lst with command data */
void Create::populate_arg_lst(byte** argv)
{
  for (auto idx = 0; idx < m_arg_cnt; idx++)  {
    m_arg_lst.push_back(std::string(argv[idx]));
  }
}

/* check command parameters */
bool Create::chk_cmd_prms(byte** argv)
{
  std::string usr_lvl(argv[CMD_IDX + 1]);
  /* argument count doesnot matter here as it is going to be same */
  if (usr_lvl != ADMIN && usr_lvl != USR)
    return hndl_err(UsrErr::INVLD_USR_LVL);
    
  return SUCCESS;
}

bool Create::cmd() 
{
  get_passwd(); /* return if password don't match on confirmation */
  if (m_passwd.empty())
    return  hndl_err(UsrErr::PASSWD_MISMATCH);
 
  /* argument count does not matter here as both min and max are same */
  std::string usr_lvl(m_arg_lst[CMD_IDX + 1]); /* user level - ADMIN | USER */
  if (usr_lvl == ADMIN)
    create_admin_usr();
  else
    create_basic_usr();

  
  return m_is_usr_created;
}

/* Escape special characters before copying to /etc/passwd */
void Create::esc_spl_seq()
{
  size_t pos, prev = 0;
  while ((pos = m_passwd.find(esc_seq, prev)) != std::string::npos) {
    if (pos >= prev) {
      m_passwd.replace(pos, 1, "\\$");
    }

    prev = pos + 2;
  } 
}

/* https://www.gnu.org/software/libc/manual/html_node/crypt.html */
void Create::encrypt_passwd()
{

  char salt[] = "$1$........";
  const char* const  seed_char = {SEED_CHAR};
  uint32_t seed[2];
  // std::mt19937 rnd_gen;
  // rnd_gen.seed(std::random_device()());
  // std::uniform_int_distribution<std::mt19937::result_type> dist(1,200);
  seed[0] = time(NULL);
  seed[1] = getpid() ^ (seed[0] >> 14 & 0x30000);

  for (int i = 0; i < 8; i++)
    salt[3+i] = seed_char[(seed[i/5] >> (i%5)*6) & 0x3f];

  char* encrypted_passwd = crypt(m_passwd.c_str(), salt);
 
  if (encrypted_passwd != nullptr) {
    std::string ep(encrypted_passwd);
    m_passwd = ep;
  }

  esc_spl_seq();
}

/* prompt for passwd and return if passwd don't match on confirmation */
void Create::get_passwd()
{
  /* prompt for passwd */
  std::string new_passwd = passwd_prmpt("new password: ");
  std::string confirm_passwd = passwd_prmpt("confirm password: ");
  
  if (new_passwd == confirm_passwd)
    m_passwd = new_passwd;

  encrypt_passwd();
}

/* terminal prompt to get confidential user input 
   Note to self: termios works onl with tty like 
   terminals.
*/
std::string Create::passwd_prmpt(std::string prompt)
{
  std::cout << prompt;

  termios oldt;
  tcgetattr(STDIN_FILENO, &oldt);
  termios newt = oldt;
  newt.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  
  std::string tmp_passwd;
  std::getline(std::cin, tmp_passwd);

  newt.c_lflag |= ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  std::cout << std::endl;

  return tmp_passwd;
}

/* create admin users registered to rolac-admin group */
void Create::create_admin_usr()
{
  std::string cmd = std::string("useradd -m -p ") + 
                    m_passwd + 
                    " -s /bin/bash -G rolac-admin " + 
                    m_arg_lst[CMD_IDX];
  if (get_cmd_out(cmd.c_str()).empty() && get_sta_code() != 0)
   m_is_usr_created = hndl_err(IntrnlErr::USR_CREATION_FAILED); 
 
  m_is_usr_created = SUCCESS;  
}


/* create basic user registered to rolac-users group */
void Create::create_basic_usr()
{
  std::string cmd = std::string("useradd -m -p ") + 
                    m_passwd + 
                    " -s /bin/bash -G rolac-usr " + 
                    m_arg_lst[CMD_IDX];
  if (get_cmd_out(cmd.c_str()).empty() && get_sta_code() != 0)
   m_is_usr_created = hndl_err(IntrnlErr::USR_CREATION_FAILED); 
 
  m_is_usr_created = SUCCESS;
}

/* Function to show usage of Create */
void Create::usage() 
{
  std::ostringstream out;
  out << "Usage: rolac create \"username\" [ user | admin ]"
      << std::endl;
  std::cout << out.str() << std::endl;
  std::exit(EXIT_FAILURE);
}

