#include <iostream>
#include <functional>
using namespace std;

class A {
public:
  void run() {
    printf("hello, i'm a\n");
  }
};

class B: public A {
public:
  void run() {
    printf("hello, i'm b\n");
  }
};

void call_func(const function<void()> &func) {
  func();
}

int main(){
  B *a = new B();
  call_func(std::bind(&A::run, a));
  return 0;
}
