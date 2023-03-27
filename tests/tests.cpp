//
// Created by Armaghan Wahid Asghar on 23/03/2023.
//
#include <typeinfo>

#include "simulator.h"
#include "publisher.h"

using namespace std;

/// A class that encapsulate the unit tests for the Simulator class. Define all units these here.
class TestSimulator : public Simulator {
 private:
  int types_of_aircraft = 5;

 public:
  TestSimulator(){};
  void runTest() {
    testRandomGenerator();
    testFactoryMethod();
  }

 private:

  /// Test to verify if the type of objects returned by factory are correct.
  void testFactoryMethod() {
    for (int i = 0; i < types_of_aircraft; ++i) {
      auto ret = factoryAircraft(EV_TYPE(i), make_shared<StatsStore>());
      assert(EV_TYPE(i) == ret->get_type());
    }
  }

  /// Test if random number generator is random.
  void testRandomGenerator(){
    bool not_same = false;
    for (int i = 0; i < 20; i++) {
      int ret = gen_rand();
      int ret2 = gen_rand();
      if (ret != ret2) {
        not_same = true;
      }
    }
    not_same ? assert(true) : assert (false);
  }
};

/// Unit test to verify the semaphore is increasing and decreasing 'curr' count.
class TestSemaphore : public C_semaphore {
 public:
  void runTest(int max_count) {
    this->max = max_count;
    for (auto i = 0; i < max_count - 1; i++)
      this->acquire();
    assert(curr == this->max - 1);
    for (auto i = 0; i < max_count - 1; i++)
      this->release();
    assert(curr == 0);
  }
};

class TestPublisher : public Publisher {

};

int main(int argc, char* argv[]) {

  TestSimulator tsim;
  tsim.runTest();

  TestSemaphore tsema;
  tsema.runTest(3);


  cout << "All Tests Passed!\n";
}



