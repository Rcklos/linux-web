#include "thread_pool.h"
#include "log/log.h"

class A {
public:
  void test() {
    LOGI("这是%s", "A");
  }

  virtual void virtual_test() {
    LOGI("这是%s的virtual", "A");
  }
};

class B: public A {
public:
  void test() {
    LOGI("这是%s", "B");
  }
  void virtual_test() {
    LOGI("这是%s的virtual", "B");
  }
};

int main() {
  A().test();
  B().test();

  A *p1 = new A();
  A *p2 = new B();
  p1->test();
  p2->test();

  // virtual
  LOGI("开始测试virtual");

  A().virtual_test();
  B().virtual_test();

  A *v1 = new A();
  A *v2 = new B();
  B *v3 = new B();
  v1->virtual_test();
  v2->virtual_test();
  v3->virtual_test();
  return 0;
}
