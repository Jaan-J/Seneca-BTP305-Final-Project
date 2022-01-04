// Name: Jaan Javed
// Seneca Student ID: 100131192
// Seneca email: jjaved3@myseneca.ca
// Date of completion: December 4th
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include "Station.h"
#include "Utilities.h"
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

namespace sdds {
size_t Station::m_widthField = 0;
int Station::id_generator = 1;

Station::Station() {
  s_ID = 0;
  itemName = "";
  stationDesc = "";
  serialNum = 0;
  numStock = 0;
  m_widthField = 0;
  id_generator = 0;
}

Station::Station(const string &str) {
  s_ID = id_generator;
  Utilities utility;
  size_t next_pos = 0;
  bool more = true;

  try {
    itemName = utility.extractToken(str, next_pos, more);
    serialNum = stoi(utility.extractToken(str, next_pos, more));
    numStock = stoi(utility.extractToken(str, next_pos, more));
    m_widthField = max(utility.getFieldWidth(), m_widthField);
    stationDesc = utility.extractToken(str, next_pos, more);
  } catch (string &msg) {
    cout << msg;
  }
  id_generator++;
}

size_t Station::getNextSerialNumber() {
  serialNum++;
  return serialNum - 1;
}

void Station::updateQuantity() {
  numStock--;
  if (numStock < 0) {
    numStock = 0;
  }
}

size_t Station::getQuantity() const { return numStock; }

const string &Station::getItemName() const { return itemName; }

void Station::display(ostream &os, bool full) const {
  ios init(NULL);
  init.copyfmt(cout);

  os << right;
  os << "[";
  os << setw(3);
  os << setfill('0');
  os << s_ID;
  os << "]";
  os << left;

  os << " Item: ";
  os << setw(m_widthField);
  os << setfill(' ');
  os << itemName;
  os << right;
  os << " [";
  os << setw(6);
  os << setfill('0');
  os << serialNum;
  os << "]";
  os << left;

  if (full == false) {
    os << endl;

  }

  else {
    os << " Quantity: ";
    os << setw(m_widthField);
    os << setfill(' ');
    os << numStock;

    os << " Description: ";
    os.copyfmt(init);
    os << stationDesc;
    os << endl;
  }
}

} 
