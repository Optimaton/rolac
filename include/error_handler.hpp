#ifndef __ERROR_HANDLER_HPP__
#define __ERROR_HANDLER_HPP__

enum class IntrnlErr {
  ERROR_CREATING_TMP_KEYSTORE,
  USR_CREATION_FAILED,
  USR_DELETION_FAILED,
};

enum class UsrErr {
  INVLD_ARG_CNT,
  INVLD_MAIN_ARG,
  INVLD_SUB_ARG,
  INVLD_USR_NAM,
  INVLD_PATH,
  INVLD_KEY, 
  USR_ALREADY_PRSNT,
  PASSWD_MISMATCH,
  INVLD_USR_LVL,
};

/* overload to handle internal error */
bool hndl_err(IntrnlErr intrnl_err);

/* overload to handle user error */
bool hndl_err(UsrErr usr_err);

#endif // __ERROR_HANDLER_HPP__

