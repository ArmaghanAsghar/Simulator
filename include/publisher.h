//
// Created by Armaghan Wahid Asghar on 23/03/2023.
//

#ifndef SIM_SRC_PUBLISHER_H_
#define SIM_SRC_PUBLISHER_H_

#include "simulator.h"

#include <sstream>

/*!
 * @brief: This class is responsible for publishing the results of simulation.
 */
class Publisher {
 private:
  std::shared_ptr<StatsStore> ss_ptr;
  std::stringstream ss;
 public:
  Publisher();
  void publish(Simulator &sim);
};

#endif //SIM_SRC_PUBLISHER_H_
