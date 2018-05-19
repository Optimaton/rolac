#ifndef __ROLAC_HPP__
#define __ROLAC_HPP__

using StringVec = std::vector<std::string>;
using CommandArgList = std::vector<std::string>;
using byte = char;

const uint8_t SUCCESS = 1;
const uint8_t FAILURE = 0;

/* user separator */
const byte SEPARATOR = ':';

/* default passwd path */
const std::string passwd_path = "/etc/passwd";

/* Main class */
class Rolac {
  public:
    Rolac() = default;
    virtual ~Rolac() {}
    virtual void exec(int argc, byte** argv) = 0;    
  protected:
    std::string main_arg_nam;
    std::string sub_arg_nam;
    std::string usr_nam;
    
    bool is_usr(std::string usr_nam);
    std::string get_cmd_out(std::string cmd);
  private:
    /* We are going to keep it pure virtual for time being */
    virtual bool argchk(int argc, byte** argv) = 0;
    virtual bool cmd() = 0;
    virtual void usage() = 0;
    virtual void set_arg_cnt(int argc) = 0;
    virtual void populate_arg_lst(byte** argv) = 0;
    virtual bool chk_cmd_prms(byte** argv) = 0;
    
};

#endif // __ROLAC_HPP__

