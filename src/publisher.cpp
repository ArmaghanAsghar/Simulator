
#include "publisher.h"

Publisher::Publisher() {}

/*!
 * @brief Output the results of the simulation to console.
 * @param sim the reference to the simulator object.
 * @return void
 */
void Publisher::publish(Simulator &sim) {


  //TODO(aasghar) Can make this program more generic to include output to different streams.
  ss_ptr = sim.get_store();

  for (int i = 0; i < 5; ++i) {
    auto my_type = EV_TYPE(i);
    double avg_flight_per_flight = ss_ptr->total_flight_time[my_type] / ss_ptr->flight_count[my_type];
    double avg_distance_per_flight = ss_ptr->total_distance_flown[my_type] / ss_ptr->flight_count[my_type];
    double avg_charge_per_session =
        ss_ptr->charge_count[my_type] > 0 ? ss_ptr->total_time_charging[my_type] / ss_ptr->charge_count[my_type] : 0;
    double total_hrs_operating = ss_ptr->total_flight_time[my_type] + ss_ptr->total_time_charging[my_type];
    double total_number_of_faults = ss_ptr->probability_fault[my_type] * total_hrs_operating;
    int passenger_miles =
        ss_ptr->num_aircraft[my_type] * ss_ptr->passenger_count[my_type] * (ss_ptr->total_flight_time[my_type])
            * ss_ptr->cruise_speed[my_type];

    ss << "\n\nType: " << my_type
       << "\nAverage flight time per flight: " << avg_flight_per_flight
       << "\nAverage distance traveled per flight: " << avg_distance_per_flight
       << "\nAverage time charging per charge session: " << avg_charge_per_session
       << "\nTotal number of faults: " << total_number_of_faults
       << "\nTotal number of passenger miles: " << passenger_miles;

  }
  std::cout << ss.str() << std::endl;

}

