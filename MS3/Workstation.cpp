// Name: Jaan Javed
// Seneca Student ID: 100131192
// Seneca email: jjaved3@myseneca.ca
// Date of completion: December 4th
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include "Workstation.h"

std::deque<sdds::CustomerOrder> pending{};
std::deque<sdds::CustomerOrder> completed{};
std::deque<sdds::CustomerOrder> incomplete{};

namespace sdds {

Workstation::Workstation() { m_pNextStation = nullptr; }

Workstation::Workstation(const std::string val) : Station(val) {m_pNextStation = nullptr;}

Workstation *Workstation::getNextStation() const { return m_pNextStation; }

void Workstation::setNextStation(Workstation *station = nullptr) {
  m_pNextStation = station;
}


void Workstation::fill(std::ostream &os) {
  if (!m_orders.empty())
    m_orders.front().fillItem(*this, os);
}

void Workstation::display(std::ostream &os) const {
  os << getItemName() << " --> "
     << (m_pNextStation ? m_pNextStation->getItemName() : "End of Line")
     << std::endl;
}

Workstation &Workstation::operator+=(CustomerOrder &&neworder) {
  m_orders.push_back(std::move(neworder));
  return *this;
}

bool Workstation::attemptToMoveOrder() {
  if (m_orders.size() > 0) {
    if (getQuantity() <= 0 || m_orders.front().isItemFilled(getItemName())) {
      if (m_pNextStation) {
        *m_pNextStation += std::move(m_orders.front());
        m_orders.pop_front();
        return true;
      } else {
        if (!m_orders.front().isFilled()) {
          incomplete.push_back(std::move(m_orders.front()));
        } else {
          completed.push_back(std::move(m_orders.front()));
        }
        m_orders.pop_front();
        return true;
      }
    }
  }
  return false;
}

}