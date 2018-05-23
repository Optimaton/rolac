#ifndef __ROUTER_HPP__
#define __ROUTER_HPP__

/* command  to route appropriate input*/
enum class RolacType {
  CREATE = 1,
  DELETE = 2,
  MODIFY = 3,
  LOCKOUT = 4,
  COPY = 5,
  INVALID = 6,
};



class Router {
public:
  Router() = default;
  explicit Router(int argc, char** argv);
  void route(int argc, char** argv);
protected:
private:
  void init_rolac_typ_map();
  RolacType get_type(char* sub_arg);
  std::map<std::string, RolacType> rolac_typ_map;
};

#endif // __ROUTER_HPP__
