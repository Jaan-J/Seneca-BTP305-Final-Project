// Name: Jaan Javed
// Seneca Student ID: 100131192
// Seneca email: jjaved3@myseneca.ca
// Date of completion: December 4th
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include <algorithm>
#include <functional>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "LineManager.h"
#include "Workstation.h"
#include "Utilities.h"

namespace sdds {
LineManager::LineManager() {
  m_cntCustomerOrder = 0;
  m_firstStation = nullptr;
}

void LineManager::display(std::ostream &os) const {
  std::for_each(activeLine.begin(), activeLine.end(),
                [&os](Workstation *ws) { ws->display(os); });
}

void LineManager::linkStations() {
  size_t d = 0;
  std::vector<Workstation *> sortedTemp{m_firstStation};
  std::for_each(
      activeLine.begin(), activeLine.end(), [&](Workstation *current) {
        std::for_each(activeLine.begin(), activeLine.end(),
                      [&](Workstation *next) {
                        if (sortedTemp[d]->getNextStation())
                          if (sortedTemp[d]->getNextStation()->getItemName() ==
                              next->getItemName()) {
                            sortedTemp.push_back(next);
                            d++;
                          }
                      });
      });
  activeLine = sortedTemp;
}

bool LineManager::run(std::ostream &os) {
  static size_t counter = 0;
  size_t compleOrders = completed.size() + incomplete.size();
  os << "Line Manager Iteration: " << ++counter << std::endl;
  if (!pending.empty()) {
    *m_firstStation += std::move(pending.front());
    pending.pop_front();
  }

  std::for_each(activeLine.begin(), activeLine.end(),
                [&](Workstation *ws) { ws->fill(os); });

  std::for_each(activeLine.begin(), activeLine.end(),
                [&](Workstation *ws) { ws->attemptToMoveOrder(); });

  m_cntCustomerOrder -= ((completed.size() + incomplete.size()) - compleOrders);
  return m_cntCustomerOrder <= 0;
}

LineManager::LineManager(const std::string &file,
                         const std::vector<Workstation *> &stations) {
  try {
    m_cntCustomerOrder = pending.size();
    m_firstStation = nullptr;
    std::fstream f(file);
    if (!f)
      throw("");
    std::string buffer;
    Utilities util;
    while (std::getline(f, buffer)) {
      size_t nextPos = 0;
      bool flag;
      std::string temp1, temp2;
      temp1 = util.extractToken(buffer, nextPos, flag);
      if (flag)
        temp2 = util.extractToken(buffer, nextPos, flag);
      std::for_each(
          stations.begin(), stations.end(), [&](Workstation *station) {
            if (station->getItemName() == temp1) {

              std::for_each(stations.begin(), stations.end(),
                            [&](Workstation *nextStation) {
                              if (nextStation->getItemName() == temp2) {
                                station->setNextStation(nextStation);
                              }
                            });
              activeLine.push_back(station);
            }
          });
      m_firstStation = activeLine.front();
    }
  } catch (...) {
    throw std::string("Error: Cannot Load LineManager");
  }
}
} 
