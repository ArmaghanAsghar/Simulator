//
// Created by Armaghan Wahid Asghar on 21/03/2023.
//

#ifndef EVTOL_INCLUDE_LOGGER_H_
#define EVTOL_INCLUDE_LOGGER_H_

#include <iostream>
#include <string>
#include <mutex>
#include <chrono>
#include <ctime>

using namespace std::chrono;


/// source: https://stackoverflow.com/questions/52728952/how-do-i-write-a-message-timestamp-to-a-log-file
#define LOGGER_PRETTY_TIME_FORMAT "%Y-%m-%d %H:%M:%S"
#define LOGGER_PRETTY_MS_FORMAT ".%03d"

template <typename T>
static int to_ms(const std::chrono::time_point<T>& tp)
{
  using namespace std::chrono;

  auto dur = tp.time_since_epoch();
  return static_cast<int>(duration_cast<milliseconds>(dur).count());
}
static std::string pretty_time()
{
  auto tp = std::chrono::system_clock::now();
  std::time_t current_time = std::chrono::system_clock::to_time_t(tp);

  // this function use static global pointer. so it is not thread safe solution
  std::tm* time_info = std::localtime(&current_time);

  char buffer[128];

  int string_size = strftime(
      buffer, sizeof(buffer),
      LOGGER_PRETTY_TIME_FORMAT,
      time_info
  );

  int ms = to_ms(tp) % 1000;

  string_size += std::snprintf(
      buffer + string_size, sizeof(buffer) - string_size,
      LOGGER_PRETTY_MS_FORMAT, ms
  );

  return std::string(buffer, buffer + string_size);
}



/*!
 * @brief: A thread-safe out stream logger.
 * */
class Logger {
 private:
  std::mutex mx;

 public:

  void info(std::string th_id, std::string msg2) {
    std::unique_lock lk(mx);
    std::cout << pretty_time() << " [" << th_id << "] " << msg2
              << std::endl;
  }

};

#endif //EVTOL_INCLUDE_LOGGER_H_
