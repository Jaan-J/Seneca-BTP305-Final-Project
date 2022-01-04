// Name: Jaan Javed
// Seneca Student ID: 100131192
// Seneca email: jjaved3@myseneca.ca
// Date of completion: December 4th
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include "Workstation.h"
#include <vector>

namespace sdds {
class LineManager {
  std::vector<Workstation *> activeLine;
  size_t m_cntCustomerOrder;
  Workstation *m_firstStation;

public:
  LineManager();
  LineManager(const std::string &file,
              const std::vector<Workstation *> &stations);
  void linkStations();
  bool run(std::ostream &os);
  void display(std::ostream &os) const;
  ~LineManager(){};

  LineManager(const LineManager &co) = delete;
  LineManager &operator=(const LineManager &co) = delete;
  LineManager(LineManager &&co) noexcept = delete;
  LineManager &operator=(LineManager &&co) noexcept = delete;
};
} // namespace sdds
#endif