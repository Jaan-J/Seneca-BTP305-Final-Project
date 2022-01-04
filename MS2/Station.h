// Name: Jaan Javed
// Seneca Student ID: 10031192
// Seneca email: jjaved3@myseneca.ca
// Date of completion: November 27th
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
using namespace std;
namespace sdds {

class Station {
	int s_ID;
	string itemName;
	string stationDesc;
	unsigned int serialNum;
	unsigned int numStock;
	static size_t m_widthField;
	static int id_generator;

       public:
	Station(const string&);
	const string& getItemName() const;
	size_t getNextSerialNumber();
	size_t getQuantity() const;
	void updateQuantity();
	void display(ostream& os, bool full) const;
};
}  // namespace sdds
#endif
