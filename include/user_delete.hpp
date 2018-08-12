#ifndef __USER_DELETE_HPP__
#define __USER_DELETE_HPP__
#include "rolac.hpp"

/* Class to create new user */
class Delete : Rolac {
  public:
    Delete() = default;
    void exec(int argc, byte** argv) override;
    ~Delete() {}
  protected:
  private:
    /* primary methods */
    bool argchk(int argc, byte** argv) override;
    bool cmd() override;
    void usage() override;
  
    /* common utility methods */
    void set_arg_cnt(int argc) override;
    void populate_arg_lst(byte** argv) override;
	
    void delete_usr();

    bool m_is_usr_deleted;
    uint8_t m_arg_cnt;
    CommandArgList m_arg_lst;
    
    
    /* Delete  Argument Count */
    const uint8_t MIN_ARG_CNT = 3;
    const uint8_t MAX_ARG_CNT = 3;

    /* Default command index */
    const uint8_t CMD_IDX = 2; /* starts with username field */

    /* Argument Name */
    const std::string MAIN_ARG_NAM = "./rolac";
    const std::string MAIN_ARG_NAM2= "/home/raghu/Development/rolac/rolac";
    const std::string SUB_ARG_NAM = "delete";

    /* home directory */
    const std::string HOME_DIR = "/home/";
};

#endif // __USER_DELETE_HPP__
