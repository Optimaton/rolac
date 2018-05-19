#ifndef __ERROR_HANDLER_HPP__
#define __ERROR_HANDLER_HPP__

enum class InternalError {
  ERROR_CREATING_TMP_KEYSTORE,
};

enum class UserError {
  INVALID_ARG_COUNT,
  INVALID_MAIN_ARG,
  INVALID_SUB_ARG,
  INVALID_USER_NAME,
  INVALID_PATH,
  INVALID_KEY,
};

/* overload to handle internal error */
bool hndl_err(InternalError internalError);

/* overload to handle user error */
bool hndl_err(UserError userError);

#endif // __ERROR_HANDLER_HPP__

