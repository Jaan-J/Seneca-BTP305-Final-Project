// Name: Jaan Javed
// Seneca Student ID: 100131192
// Seneca email: jjaved3@myseneca.ca
// Date of completion: December 4th
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <iostream>
using namespace std;

namespace sdds {
class Utilities {
  size_t m_widthField = 1;
  static char m_delimiter;

public:
  void setFieldWidth(size_t newWidth);
  size_t getFieldWidth() const;
  string extractToken(const string &str, size_t &next_pos, bool &more);

  static void setDelimiter(char newDelimiter);
  static char getDelimiter();
};
} // namespace sdds
#endif
