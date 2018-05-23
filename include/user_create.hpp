#ifndef __USER_CREATE_HPP__
#define __USER_CREATE_HPP__
#include "rolac.hpp"

/* Class to create new user */
class Create : Rolac {
  public:
    Create() = default;
    void exec(int argc, byte** argv) override;
    ~Create() {}
  protected:
  private:
    /* primary methods */
    bool argchk(int argc, byte** argv) override;
    bool cmd() override;
    void usage() override;
  
    /* common utility methods */
    void set_arg_cnt(int argc) override;
    void populate_arg_lst(byte** argv) override;
    bool chk_cmd_prms(byte** argv) override;

    std::string passwd_prmpt(std::string prmpt);
    void get_passwd();
    void encrypt_passwd();
    void create_admin_usr();
    void create_basic_usr();
    
    bool m_is_usr_created;
    std::string m_passwd;
    uint8_t m_arg_cnt;
    CommandArgList m_arg_lst;
    
    
    /* Create  Argument Count */
    const uint8_t MIN_ARG_CNT = 4;
    const uint8_t MAX_ARG_CNT = 4;

    /* Default command index */
    const uint8_t CMD_IDX = 2; /* starts with username field */

    /* Argument Name */
    const std::string MAIN_ARG_NAM = "./rolac";
    const std::string MAIN_ARG_NAM2= "/home/raghu/Development/rolac/rolac";
    const std::string SUB_ARG_NAM = "create";

    /* home directory */
    const std::string HOME_DIR = "/home/";

    /* user level */
    const std::string ADMIN = "admin";
    const std::string USR = "user";

    /* SEED char */
    const char* const SEED_CHAR = "./0123456789ABCDEFGHIJKLMNOPQRST"
                                    "UVWXYZabcdefghijklmnopqrstuvwxyz";
};

#endif // __USER_CREATE_HPP__

