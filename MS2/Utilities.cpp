// Name: Jaan Javed
// Seneca Student ID: 10031192
// Seneca email: jjaved3@myseneca.ca
// Date of completion: November 27th
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include "Utilities.h"
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

namespace sdds {
char Utilities::m_delimiter = ' ';

size_t Utilities::getFieldWidth() const { return m_widthField; }

void Utilities::setFieldWidth(size_t newWidth) { m_widthField = newWidth; }

string Utilities::extractToken(const string& str, size_t& next_pos,
			       bool& more) {
	string buffer = "";

	size_t first_pos = next_pos;
	next_pos = str.find(m_delimiter, first_pos);

	if (next_pos == string::npos) {
		buffer = str.substr(first_pos);
		m_widthField = max(buffer.length(), m_widthField);
		more = false;
	} else if (first_pos == next_pos) {
		more = false;
		throw "Token not found between delimeters";
	} else {
		buffer = str.substr(first_pos, next_pos - first_pos);
		m_widthField = max(buffer.length(), m_widthField);
		more = true;
	}
	next_pos++;
	return buffer;
}

void Utilities::setDelimiter(char newDelimiter) { m_delimiter = newDelimiter; }

char Utilities::getDelimiter() { return m_delimiter; }
}  // namespace sdds
