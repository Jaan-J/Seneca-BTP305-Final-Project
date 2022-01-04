// Name: Jaan Javed
// Seneca Student ID: 10031192
// Seneca email: jjaved3@myseneca.ca
// Date of completion: December 4th
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include "Station.h"
#include <iomanip>
#include <iostream>
#include <string>

using std::string;

namespace sdds {
class CustomerOrder {
  struct Item {
    string m_itemName;
    size_t m_serialNumber{0};
    bool m_isFilled{false};

    Item(const std::string &src) : m_itemName(src){};
  };
  string m_name{};
  string m_product{};
  size_t m_cntItem{0};
  Item **m_lstItem{nullptr};
  static size_t m_widthField;

public:
  CustomerOrder(){};
  CustomerOrder(const string &str);
  CustomerOrder(const CustomerOrder &);
  CustomerOrder &operator=(const CustomerOrder &) = delete;
  CustomerOrder(CustomerOrder &&) noexcept;
  CustomerOrder &operator=(CustomerOrder &&) noexcept;
  ~CustomerOrder();
  bool isFilled() const;
  bool isItemFilled(const string &itemName) const;
  void fillItem(Station &station, std::ostream &os);
  void display(std::ostream &os) const;
};
} // namespace sdds
#endif