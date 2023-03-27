
#ifndef AIRCRAFT_INCLUDE_EV_TOL_H_
#define AIRCRAFT_INCLUDE_EV_TOL_H_

#include <memory>
#include <iostream>
#include <map>
#include <mutex>

#include "defs.h"

/*!
 * @brief: A superclass that defines functionality for
 *  aircraft type. All aircraft types inherit from this base
 *  class.
 */
class Aircraft {
 private:
  /// The aircraft properties.
  int cruise_speed;
  int battery_capacity;
  double charge_time;
  double energy_consume_rate;
  double passenger_count;
  double prob_fault_rate;
  std::shared_ptr<StatsStore> ss_ptr;
  using time_unit = std::chrono::milliseconds;

  /// The custom metrics calculated.
  EV_TYPE my_type;
  double miles_travel_per_charge;
  double hrs_travel_per_charge;

 public:
  Aircraft(EV_TYPE this_type, int cr, int bc, double ct,
            double ecr, double pc,
            double pfr,
            std::shared_ptr<StatsStore> ss);
  EV_TYPE get_type();
  void isFlying();
  void isCharging();
};

#endif //AIRCRAFT_INCLUDE_EV_TOL_H_
