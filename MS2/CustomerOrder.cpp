// Name: Jaan Javed
// Seneca Student ID: 10031192
// Seneca email: jjaved3@myseneca.ca
// Date of completion: November 27th
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds {
    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder(const CustomerOrder&) {
        throw std::string("Error: Not allowed to make copies!");
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& obj) noexcept {
        *this = std::move(obj);
    }

    CustomerOrder::CustomerOrder(const std::string& coObj) {
        if (!coObj.empty()) {

            Utilities buffer;
            char delimiter{ buffer.getDelimiter() };
            size_t startPoint{ 0 }, endPoint{ 0 };
            endPoint = coObj.find(delimiter);
            m_name = coObj.substr(0, endPoint);

            bool flag{ false };

            startPoint = endPoint + 1;
            endPoint = coObj.find(delimiter, startPoint); 
            m_product = buffer.extractToken(coObj, startPoint, flag);
            if (flag) {
                m_cntItem = std::count(coObj.begin(), coObj.end(), buffer.getDelimiter()) - 1;
                if (m_cntItem > 0) {
                    m_lstItem = new Item * [m_cntItem];
                    for (size_t i = 0u; i < m_cntItem; ++i) {
                        startPoint = endPoint + 1;
                        endPoint = coObj.find(delimiter, startPoint);
                        m_lstItem[i] = new Item(buffer.extractToken(coObj, startPoint, flag));
                    }
                }
            }
            m_widthField = m_widthField > buffer.getFieldWidth() ? m_widthField : buffer.getFieldWidth();
        }
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& obj) noexcept {
        if (this != &obj) {
            if (m_lstItem) {
                for (size_t i = 0u; i < m_cntItem; i++) {
                    delete m_lstItem[i];
                }
                delete[] m_lstItem;
            }
            m_product = obj.m_product;
            m_cntItem = obj.m_cntItem;
            m_name = obj.m_name;
            m_widthField = obj.m_widthField;
            m_lstItem = obj.m_lstItem;

            obj.m_lstItem = nullptr;
            obj.m_cntItem = 0u;
            obj.m_name = "";
            obj.m_product = "";
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
        m_lstItem = nullptr;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        bool flag{ true };
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
                flag = false;
            }
        }
        return flag;
    }

    bool CustomerOrder::isFilled() const {
        bool flag{ false };
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_isFilled) {
                flag = true;
            }
        }
        return flag;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        for (size_t i = 0u; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == station.getItemName()) {
                if (station.getQuantity() > 0) {
                    station.updateQuantity();
                    m_lstItem[i]->m_isFilled = true;
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName 
				   	    		<< "]" << std::endl;
                }
                else {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName 
			  			         << "]" << std::endl;
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0u; i < m_cntItem; i++) {
            os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] "
                                << std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName 
			     << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }
}