#include <iostream>
#include <cstdint>
#include <cstdio>
#include "error_handler.hpp"

bool hndl_err(UsrErr usr_err)
{
  std::string err_msg = "Command Failed. ";

  switch(usr_err) {
    case UsrErr::INVLD_ARG_CNT: err_msg += "Invalid number of arguments provided."; break;
    case UsrErr::INVLD_MAIN_ARG: err_msg += "Main argument is not 'accounts'"; break;
    case UsrErr::INVLD_SUB_ARG: err_msg += "Invalid sub argument"; break;
    case UsrErr::INVLD_USR_NAM: err_msg += "Invalid Username"; break;
    case UsrErr::INVLD_PATH: err_msg += "Path to public key not found"; break;
    case UsrErr::INVLD_KEY: err_msg += "Invalid public key fed in"; break;
    case UsrErr::USR_ALREADY_PRSNT: err_msg += "User is already present"; break;
    case UsrErr::PASSWD_MISMATCH: err_msg += "Passwords don't match"; break;
    case UsrErr::INVLD_USR_LVL: err_msg += "Invalid user level"; break;
  }
  
  std::cout << err_msg << std::endl;
  return 0;
}

bool hndl_err(IntrnlErr intrnl_err)
{
  std::string err_msg = "Command Failed. ";
  
  switch(intrnl_err) {
    case IntrnlErr::ERROR_CREATING_TMP_KEYSTORE: err_msg += "Error creating temporary key store. Please try to run with elevated privilege"; break;
    case IntrnlErr::USR_CREATION_FAILED: err_msg += "Error creating user. Internal Error"; break;
    case IntrnlErr::USR_DELETION_FAILED: err_msg += "Error deleting user. Internal Error"; break;
  }
  
  std::cout << err_msg << std::endl;
  return 0;
}

