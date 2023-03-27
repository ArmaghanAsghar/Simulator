//
// Created by Armaghan Wahid Asghar on 23/03/2023.
//

#ifndef SIM_INCLUDE_SIMULATOR_H_
#define SIM_INCLUDE_SIMULATOR_H_

#include <thread>
#include <vector>
#include <atomic>
#include <cstdlib>
#include <random>

#include "aircraft_types.h"
#include "c_semaphore.h"


//(TODO)(aasghar) If we want to define additional simulations we can define here.
/*!
 * @brief defines a simulation on an aircraft types.
 */
class Simulator {
 public:
  std::shared_ptr<StatsStore> get_store();
  Simulator();
  Simulator(int total_aircraft,
            int total_chargers,
            int simulator_hrs);
  void start();

 protected:
  int total_aircraft = 0;
  int total_chargers = 0;
  int simulator_hrs = 0;
  std::vector<std::thread> v_th;
  std::vector<std::shared_ptr<Aircraft>> v_ar;
  C_semaphore sema;
  std::shared_ptr<StatsStore> ss_ptr = std::make_shared<StatsStore>();
  std::atomic_bool keep_alive = true;

  void create_objects();
  void start_threads();
  void stop_simulation();
  void join_threads();
  void thread_job(std::shared_ptr<Aircraft> plane);
  int gen_rand();

};

#endif //SIM_INCLUDE_SIMULATOR_H_
