
#include "simulator.h"

///
extern std::mutex fly_mx, charge_mx;
extern std::condition_variable fly_cv, charge_cv;
extern bool stop_flying;
extern bool stop_charging;

Simulator::Simulator() {}

Simulator::Simulator(int total_aircraft,
                     int total_chargers,
                     int simulator_hrs) : total_aircraft(total_aircraft),
                                          total_chargers(total_chargers),
                                          simulator_hrs(simulator_hrs),
                                          sema(total_chargers) {

}

/*!
 * @brief: starts the simulation by creating objects, starting threads
 *  and stopping them based on condition.
 * @param void
 * @return void
 */
void Simulator::start() {

  logger.info("Main", "Starting Planes!");
  create_objects();
  start_threads();
  stop_simulation();
  join_threads();
  logger.info("Main", "All simulations stopped!");
}

/*!
 * @brief: getter method to the store pointer.
 * @param void
 * @return shared pointer to the stats store.
 */
std::shared_ptr<StatsStore> Simulator::get_store() {
  return ss_ptr;
}

/*!
 * @brief: create objects of Aircraft type using factory method.
 *  Populate the Aircraft instances to a vector.
 * @param void
 * @return void
 */
void Simulator::create_objects() {
  std::string aircraft_types = "Aircraft types: ";
  for (int i = 0; i < total_aircraft; i++) {
    auto num = gen_rand();
    aircraft_types += std::to_string(num) + ", ";
    ss_ptr->num_aircraft[EV_TYPE(num)] += 1;
    v_ar.push_back(factoryAircraft(EV_TYPE(num), ss_ptr));
  }
  logger.info("Main", aircraft_types);
}

/*!
 * @brief: start all threads. One thread per aircraft, associates an
 *  Aircraft object with the execution of a thread. Each thread executs
 *  thread_job() function on the Aircraft object instance.
 * @param void
 * @return void
 */
void Simulator::start_threads() {
  for (int i = 0; i < total_aircraft; i++) {
    v_th.push_back(std::thread(&Simulator::thread_job, this, v_ar[i]));
  }
}

/*!
 * @brief: join all threads that were created.
 * @param void
 * @return void
 */
void Simulator::join_threads() {
  for (int i = 0; i < total_aircraft; i++) {
    v_th[i].join();
  }
}

/*!
 * @brief: the job executed by every thread instance.
 * @param plane a shared pointer to the Aircraft object associated with a thread.
 * @return void
 */
void Simulator::thread_job(std::shared_ptr<Aircraft> plane) {

  while (keep_alive) {
    plane->isFlying();
    sema.acquire();
    plane->isCharging();
    sema.release();
  }
}

/*!
 * @brief: the logic for stopping the simulation. The main thread starts 'n' number of threads
 *  and then sleeps for 'duration' of simulation. Once 'duration' has passed the main thread
 *  notifies all the child threads which represent the aircraft types to stop executing.
 * @param void
 * @return void
 */
void Simulator::stop_simulation() {

  std::this_thread::sleep_for(std::chrono::milliseconds(h_to_ms(simulator_hrs)));

  logger.info("Main", "Stop all simulation");
  keep_alive = false;
  {
    std::scoped_lock lk(fly_mx, charge_mx);
    stop_flying = true;
    stop_charging = true;
  }
  fly_cv.notify_all();
  charge_cv.notify_all();
}

/*!
 * @brief: get random number between 0 to 4.
 * @param void
 * @return void
 */
int Simulator::gen_rand()  {
  //(TODO)(aasghar) this function is biased. Need a better random function.
  return rand()/((RAND_MAX + 1u)/5);
}
