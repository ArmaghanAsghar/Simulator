
#include "c_semaphore.h"

C_semaphore::C_semaphore(int count) : max(count) {}

/*!
 * @brief: As a thread enters acquire() it increments curr by 1
 *  if the count of curr == max, then threads wait in condition_variable
 *  queue until the count of curr is decremented.
 * @param void
 * @return void
 */
void C_semaphore::acquire() {

  std::unique_lock lk(mx); // Critical Section.
  cv.wait(lk, [&] { return curr < max; });
  curr++;
}

/*!
 * @brief: As a thread enters release() it decrements curr by 1
 * and notifies one thread waiting in queue to wake up and increment
 * the count by 1.
 * @param void
 * @return void
 */
void C_semaphore::release() {
  std::unique_lock lk(mx);
  curr--;
  cv.notify_one();
}
