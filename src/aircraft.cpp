
#include "aircraft.h"

/// Synchronization variables used by Aircraft and Simulator.
std::mutex fly_mx, charge_mx;
std::condition_variable fly_cv, charge_cv;
bool stop_flying = false;
bool stop_charging = false;

/*!
 * @brief: The constructor initializes the properties associated with each aircraft type.
 *
 * @param this_type represents the type of aircraft for logging and stats logging.
 * @param cr cruise speed in mph
 * @param bc battery capacity in kWh
 * @param ct charging time in hrs
 * @param ecr consumption rate kWh/mile
 * @param pc passenger count
 * @param pfr probability of fault per hour of flying & charging.
 * @return void
 */
Aircraft::Aircraft(EV_TYPE this_type, int cr, int bc, double ct,
                   double ecr, double pc,
                   double pfr,
                   std::shared_ptr<StatsStore> ss) : my_type(this_type),
                                                     cruise_speed(cr),
                                                     battery_capacity(bc),
                                                     charge_time(ct),
                                                     energy_consume_rate(ecr),
                                                     passenger_count(pc),
                                                     prob_fault_rate(pfr),
                                                     ss_ptr(ss) {
  miles_travel_per_charge = battery_capacity / energy_consume_rate; // miles
  hrs_travel_per_charge = miles_travel_per_charge / cruise_speed; // hrs.
  ss_ptr->probability_fault[my_type] = prob_fault_rate;
  ss_ptr->passenger_count[my_type] = passenger_count;
  ss_ptr->cruise_speed[my_type] = cruise_speed;

}
/// Add documentioation
EV_TYPE Aircraft::get_type() {
  return my_type;
}

/*!
 * @brief: simulates flying functionality of aircraft. And records data in
 *  global data store respectively. The function uses condition_variables
 *  to capture notify issued by Simulator for more fine grained stats.
 * @param void
 * @return void
 */
void Aircraft::isFlying() {

  logger.info(std::to_string(my_type), "isFlying");
  std::unique_lock u_lk(fly_mx);
  ss_ptr->flight_count[my_type] += 1;

  int sleep_time = h_to_ms(charge_time);
  auto is_interrupted = fly_cv.wait_for(u_lk, time_unit(sleep_time),
                                   [] { return stop_flying; });
  if (is_interrupted) {
    //TODO(aasghar) Can add marginal flight time to global stats.
    logger.info(std::to_string(my_type), "FlightInterrupted");
  } else {
    logger.info(std::to_string(my_type), "hasCompleteFlight");
    ss_ptr->total_flight_time[my_type] += hrs_travel_per_charge;
    ss_ptr->total_distance_flown[my_type] += miles_travel_per_charge;
  }

}

/*!
 * @brief: simulates charging functionality of aircraft. And records data in
 *  global data store respectively. The function uses condition_variables
 *  to capture notify issued by Simulator for more fine grained stats.
 * @param void
 * @return void
 */
void Aircraft::isCharging() {

  //TODO(aasghar) When the notify is captured still the threads proceed to this method from semaphore.
  // We can handle this by including if condition.

  logger.info(std::to_string(my_type), "InQueueToCharge");

  std::unique_lock u_lk(charge_mx);
  int sleep_time = h_to_ms(charge_time);
  auto is_interrupted = charge_cv.wait_for(u_lk, time_unit(sleep_time),
                                      [] { return stop_charging; });
  if (is_interrupted) {
    //TODO(aasghar) Can add marginal charging time to global stats.
    logger.info(std::to_string(my_type), "ChargeInterrupted");
  } else {
    logger.info(std::to_string(my_type), "ChargeFull");
    ss_ptr->charge_count[my_type] += 1;
    ss_ptr->total_time_charging[my_type] += charge_time;
  }
}
