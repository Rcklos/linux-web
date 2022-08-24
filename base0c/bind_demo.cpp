#include <iostream>
#include <functional>
using namespace std;

class A {
public:
  A() {}
  virtual void run(char *buff);
  void call_func();
};

void A::call_func() {
  char *buff = const_cast<char *>("test");
  std::bind(&A::run, this, buff)();
}

void A::run(char *buff) {
  printf("default: %s", buff);
}

class B: public A {
public:
  virtual void run(char *buff) {
    printf("hello, i'm b: %s\n", buff);
  }
};

// void call_func(const function<void()> &func) {
//   func();
// }

void call_func(A *a) {
  a->call_func();
}

void call_func2(A *a) {
  call_func(a);
}


int main(){
  B *a = new B();
  // B a;
  // call_func(std::bind(&A::run, a));
  call_func2(a);
  return 0;
}
