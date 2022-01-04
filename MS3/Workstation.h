// Name: Jaan Javed
// Seneca Student ID: 100131192
// Seneca email: jjaved3@myseneca.ca
// Date of completion: December 4th
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include "CustomerOrder.h"
#include "Station.h"
#include <deque>


extern std::deque<sdds::CustomerOrder> pending;
extern std::deque<sdds::CustomerOrder> completed;
extern std::deque<sdds::CustomerOrder> incomplete;

namespace sdds {
class Workstation : public Station {
  std::deque<CustomerOrder> m_orders{};
  Workstation *m_pNextStation;

public:
  Workstation();
  Workstation(const std::string val);
  void fill(std::ostream &os);
  bool attemptToMoveOrder();
  void setNextStation(Workstation *station);
  Workstation *getNextStation() const;
  void display(std::ostream &os) const;
  Workstation &operator+=(CustomerOrder &&newOrder);
  ~Workstation() = default;

  Workstation(const Workstation &) = delete;
  Workstation &operator=(const Workstation &) = delete;
  Workstation(Workstation &&) noexcept = delete;
  Workstation &operator=(Workstation &&) noexcept = delete;
};
} // namespace sdds
#endif