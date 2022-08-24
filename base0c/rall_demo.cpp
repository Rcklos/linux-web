#include <cstdio>
#include <iostream>
using namespace std;

class A {
public:
  A() {
    printf("我是class a, 我来了\n");
  }
  ~A() {
    printf("我是class a, 我走了\n");
  }
};

class B: public A {
public:
  B() {
    printf("我是class b, 我来了\n");
  }
  ~B() {
    printf("我是class b, 我走了\n");
  }
};

void del1(A *a) {
  delete a;
}

int main() {
  // A *a = new A();
  // A *b1 = new B();
  B *b2 = new B();
  // delete a;
  // delete b1;
  // delete b2;
  del1(b2);
}
