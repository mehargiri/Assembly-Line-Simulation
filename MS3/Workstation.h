#ifndef WORKSTATION_H_
#define WORKSTATION_H_

#include "CustomerOrder.h"
#include <deque>
#include <ostream>
#include <string>
namespace sdds {
extern std::deque<CustomerOrder> g_pending;
extern std::deque<CustomerOrder> g_completed;
extern std::deque<CustomerOrder> g_incomplete;

class Workstation : public Station {
  std::deque<CustomerOrder> m_orders{};
  Workstation *m_pNextStation{};

public:
  Workstation(const std::string &str);
  void fill(std::ostream &os);
  bool attemptToMoveOrder();
  void setNextStation(Workstation *station);
  Workstation *getNextStation() const;
  void display(std::ostream &os) const;
  Workstation &operator+=(CustomerOrder &&newOrder);

  Workstation(const Workstation &temp) = delete;
  Workstation& operator=(const Workstation &temp) = delete;
  Workstation(Workstation &&temp) = delete;
  Workstation& operator=(Workstation &&temp) = delete;
};
}
#endif