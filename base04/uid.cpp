#include <unistd.h>
#include <iostream>

int main() {
  uid_t uid = getuid();
  uid_t euid = geteuid();

  std::cout << "user id: " << uid << " effective user id: " << euid << std::endl;

  return 0;
}
