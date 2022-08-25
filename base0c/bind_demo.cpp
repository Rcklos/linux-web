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
  std::function<void()> task;
  B(): A() {}
  B(const std::function<void()> &task_): task(task_), A() {}
  virtual void run(char *buff) {
    printf("hello, i'm b: %s\n", buff);
  }
  void call() {
    task();
  }
};

void call_func(const function<void()> &func) {
  func();
}

void call_func(A *a) {
  a->call_func();
}

void call_func2(A *a) {
  call_func(a);
}


int main(){
  // B *a = new B();
  // B a;
  // call_func2(a);

  // call_func([](){
  //     cout << "hello" << endl;
  // });

  // B *a = new B([](){
  //     printf("hello\n");
  // });
  // B b([](){
  //     printf("hello 2\n");
  // });
  // a->call();
  // b.call();

  B b([](){});
  b.task = NULL;
  B a(NULL);
  printf("b.task = %d\n", b.task == NULL);
  printf("a.task = %d\n", a.task == NULL);
  return 0;
}
