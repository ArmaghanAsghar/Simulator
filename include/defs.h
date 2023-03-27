//
// Created by Armaghan Wahid Asghar on 22/03/2023.
//

#ifndef SIM_INCLUDE_EV_DEFS_H_
#define SIM_INCLUDE_EV_DEFS_H_

#include <map>
#include <condition_variable>
#include <mutex>
#include "logger.h"


/// The types of aircraft.
enum EV_TYPE{
  TYPE_A = 0,
  TYPE_B = 1,
  TYPE_C = 2,
  TYPE_D = 3,
  TYPE_E = 4
};

/// Define one static instance of logger class.
static Logger logger;

/*!
 * @brief: The data store used to keep track of stats.
 *  using a map<id,value> where id is type of aircraft.
 *
 */

struct StatsStore {
  std::map<EV_TYPE, int> flight_count;
  std::map<EV_TYPE, int> charge_count;
  std::map<EV_TYPE, double> total_flight_time;
  std::map<EV_TYPE, double> total_distance_flown;
  std::map<EV_TYPE, double> total_time_charging;
  std::map<EV_TYPE, int> num_aircraft;

  std::map<EV_TYPE, double> probability_fault;
  std::map<EV_TYPE, int> passenger_count;
  std::map<EV_TYPE, int> cruise_speed;
};

/// Used to scale simulation to milliseconds from hours.
static int h_to_ms(double h) {
  return h*1000;
}

/// Use if we want to record marginal values in stats.
static double ms_to_hr(int ms) {
  return ms/1000.0;
}


#endif //SIM_INCLUDE_EV_DEFS_H_
