#include "thread_pool.h"
#include "log/log.h"

class A {
public:
  void test() {
    LOGI("这是%s", "A");
  }
  virtual ~A(){}
};

class B: public A {
public:
  void test() {
    LOGI("这是%s", "B");
  }
};

class C {
private:
  int a, b;
public:
  C(int a) {
    this->a = a;
  }

  void test() {
    // 相当于printf
    LOGI("this->a = %d", this->a);
  }

  void test2() {
    LOGI("hello");
  }
};

int main() {

  C obj = 3;
  obj.test();

  C *p = NULL;
  p->test2();
  p->test();

  return 0;
}

// int main() {
//   A().test();
//   B().test();
//
//   A *p1 = new A();
//   A *p2 = new B();
//   p1->test();
//   p2->test();
//   return 0;
// }
