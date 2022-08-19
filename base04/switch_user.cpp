#include <unistd.h>
#include <iostream>

static bool switch_to_user(uid_t user_id, gid_t gp_id) {
  // 确定不是root
  if((user_id == 0) && (gp_id == 0)) return false;
  uid_t uid = getuid();
  gid_t gid = getgid();
  // 确定是合法用户
  if((gid!=0) || (uid != 0) && ((gid != gp_id) || (uid != user_id))) return false;
  if(uid != 0) return true;
  if((setgid(gp_id) < 0) || (setuid(user_id) < 0)) return false;
  return true;
}

int main() {

  std::cout << "before switch" << std::endl;

  uid_t uid = getuid();
  uid_t euid = geteuid();

  std::cout << "user id: " << uid << " effective user id: " << euid << std::endl;

  switch_to_user(1000, 1000);

  std::cout << "after switch" << std::endl;

  uid = getuid();
  euid = geteuid();

  std::cout << "user id: " << uid << " effective user id: " << euid << std::endl;

  return 0;
}
