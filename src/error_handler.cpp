#include <iostream>
#include <cstdint>
#include <cstdio>
#include "error_handler.hpp"

bool hndl_err(UserError userError)
{
  std::string errorMsg = "Command Failed. ";

  switch(userError) {
    case UserError::INVALID_ARG_COUNT: errorMsg += "Invalid number of arguments provided."; break;
    case UserError::INVALID_MAIN_ARG: errorMsg += "Main argument is not 'accounts'"; break;
    case UserError::INVALID_SUB_ARG: errorMsg += "Invalid sub argument"; break;
    case UserError::INVALID_USER_NAME: errorMsg += "Invalid Username"; break;
    case UserError::INVALID_PATH: errorMsg += "Path to public key not found"; break;
    case UserError::INVALID_KEY: errorMsg += "Invalid public key fed in"; break;
  }
  
  std::cout << errorMsg << std::endl;
  return 0;
}

bool hndl_err(InternalError internalError)
{
  std::string errorMsg = "Command Failed. ";
  
  switch(internalError) {
    case InternalError::ERROR_CREATING_TMP_KEYSTORE: errorMsg += "Error creating temporary key store. Please try to run with elevated privilege"; break;
  }
  
  std::cout << errorMsg << std::endl;
  return 0;
}

