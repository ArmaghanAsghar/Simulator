
#include "aircraft.h"

/*!
 * @brief: These are the classes representing different aircraft types.
 *  Subclasses of parent Aircraft class.
 */
class A : public Aircraft {
 public:
  A(std::shared_ptr<StatsStore> ss) : Aircraft(EV_TYPE::TYPE_A, 120, 320, 0.6, 1.6, 4, 0.25, ss) {}
};

class B : public Aircraft {
 public:
  B(std::shared_ptr<StatsStore> ss) : Aircraft(EV_TYPE::TYPE_B, 100, 100, 0.2, 1.5, 5, 0.10, ss) {}
};

class C : public Aircraft {
 public:
  C( std::shared_ptr<StatsStore> ss) : Aircraft(EV_TYPE::TYPE_C, 160, 220, 0.8, 2.2, 3, 0.05, ss) {}
};

class D : public Aircraft {
 public:
  D(std::shared_ptr<StatsStore> ss) : Aircraft(EV_TYPE::TYPE_D, 90, 120, 0.62, 0.8, 2, 0.22, ss) {}
};

class E : public Aircraft {
 public:
  E(std::shared_ptr<StatsStore> ss) : Aircraft(EV_TYPE::TYPE_E, 30, 150, 0.3, 5.8, 2, 0.61, ss) {}
};

/*!
 * @brief: just used for pretty printing by the of aircraft type.
 * @param ev_type An enum defining type of aircraft to construct.
 * @return a string of type aircraft.
 */
static std::string getVerboseName(EV_TYPE ev_type) {
  switch (ev_type) {
    case EV_TYPE::TYPE_A:
      return std::string("Aircraft A");
    case EV_TYPE::TYPE_B:
      return  std::string("Aircraft B");
    case EV_TYPE::TYPE_C:
      return std::string("Aircraft C");
    case EV_TYPE::TYPE_D:
      return  std::string("Aircraft D");
    case EV_TYPE::TYPE_E:
      return  std::string("Aircraft E");
  }
}

/*!
 * @brief: factory method to return shared
 *  pointer of a Aircraft type.
 * @param ev_type An enum defining type of aircraft to construct.
 * @param data_store A pointer to data store where each Aircraft type stores data.
 * @return a shared pointer of Aircraft Type.
 */
static std::shared_ptr<Aircraft> factoryAircraft(EV_TYPE ev_type, std::shared_ptr<StatsStore> data_store) {
  switch (ev_type) {
    case EV_TYPE::TYPE_A:
      return std::make_shared<A>(data_store);
    case EV_TYPE::TYPE_B:
      return std::make_shared<B>(data_store);
    case EV_TYPE::TYPE_C:
      return std::make_shared<C>(data_store);
    case EV_TYPE::TYPE_D:
      return std::make_shared<D>(data_store);
    case EV_TYPE::TYPE_E:
      return std::make_shared<E>(data_store);
  }
}
