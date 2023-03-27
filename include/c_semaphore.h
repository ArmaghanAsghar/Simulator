#ifndef SIM_INCLUDE_C_SEMAPHORE_H_
#define SIM_INCLUDE_C_SEMAPHORE_H_

#include <mutex>
#include <condition_variable>

/*!
 * @brief: A semaphore used for bounding flow of threads upto max.
 *  default value of max: 1. A custom value can be provided
 *  at initialization.
 */
class C_semaphore {
 protected:
  unsigned curr = 0;
  unsigned int max = 1;
  std::mutex mx;
  std::condition_variable cv;

 public:

  C_semaphore() = default;
  C_semaphore(int count);

  void acquire();
  void release();

};

#endif //SIM_INCLUDE_C_SEMAPHORE_H_
