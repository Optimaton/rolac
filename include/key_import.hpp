#ifndef __KEY_IMPORT_HPP__
#define __KEY_IMPORT_HPP__
#include "rolac.hpp"

/* Class to import public key */
class Key : Rolac {
  public:
    Key() = default;
    void exec(int argc, byte** argv) override;
    ~Key() {}
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

    /* import specific methods */
    bool vrfy_key();
    void cp_key();
    
    uint8_t m_arg_cnt;
    CommandArgList m_arg_lst;
    
    /* Import Argument Count */
    const uint8_t MIN_ARG_CNT = 4;
    const uint8_t MAX_ARG_CNT = 5;

    /* Default command index */
    const uint8_t CMD_IDX = 2;

    /* Argument Name */
    const std::string MAIN_ARG_NAM = "./rolac";
    const std::string SUB_ARG_NAM = "copy";

    /* home directory */
    const std::string HOME_DIR = "/home/";
    /* ssh directory - authorized_keys */
    const std::string AUTHORIZED_KEYS = "/.ssh/authorized_keys";

};

#endif // __KEY_IMPORT_HPP__

