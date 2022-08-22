#include <unistd.h>
#include <iostream>
#include <thread>
using namespace std;

#define LOGI(format, ...) printf("[%s] " #format "\n", "simple_thread", ##__VA_ARGS__)
void run(long time, char *name) {
  sleep(time);
  // cout  << "thread: " << name << " ---------> sleep[" << time <<  "]s" << endl;
  LOGI("thread: %s ---------> sleep[%lds]", name, time);
}

int main() {
  thread t1(run, 2, (char *)"t1");
  thread t2(run, 2, (char *)"t2");
  thread t3(run, 2, (char *)"t3");
  thread t4(run, 2, (char *)"t4");
  thread t5(run, 2, (char *)"t5");
  // run(3, (char *)"ddd");
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  return 0;
}
