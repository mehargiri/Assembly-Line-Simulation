#include "CustomerOrder.h"
#include <iostream>
#include <iomanip>
namespace sdds {
size_t CustomerOrder::m_widthField{};

CustomerOrder::CustomerOrder(const std::string &str) {
  Utilities util;
  size_t nextPos{};
  bool more{};
  try {
    m_name = leftTrim(rightTrim(util.extractToken(str, nextPos, more)));
    m_product = leftTrim(rightTrim(util.extractToken(str, nextPos, more)));

    char delimiter = util.getDelimiter();
    size_t count{0};
    for (size_t i{nextPos}; i < str.length() - 1; ++i) {
      if (str[i] == delimiter) count++;
    }

    m_cntItem = ++count;
    // auto tempItemList = new Item*[m_cntItem];
    // for (size_t i{0}; i < m_cntItem; ++i) {
    //   std::string tempToken = leftTrim(util.extractToken(str, nextPos, more));
    //   tempItemList[i]->m_itemName = tempToken;
    // }
    m_lstItem = new Item *[m_cntItem];
    for (size_t i{0}; i < m_cntItem; ++i) {
      m_lstItem[i] = new Item;
      m_lstItem[i]->m_itemName = leftTrim(util.extractToken(str, nextPos, more));
      m_lstItem[i]->m_serialNumber = 0;
      m_lstItem[i]->m_isFilled = false;

    }

    auto utilWidthField = util.getFieldWidth();
    m_widthField =
        (utilWidthField > m_widthField) ? utilWidthField : m_widthField;

    // for (size_t i{0}; i < m_cntItem; ++i) {
    //   delete tempItemList[i];
    // }
    // tempItemList = nullptr;

  } catch (const std::string &error) {
    std::cout << error << '\n';
  }
}

CustomerOrder::CustomerOrder(const CustomerOrder &) {
  throw std::string("Customer order cannot be copied!");
}
CustomerOrder::CustomerOrder(CustomerOrder &&order) noexcept {
  *this = std::move(order);
}

CustomerOrder &CustomerOrder::operator=(CustomerOrder &&order) noexcept {
  if (this != &order) {
    for (size_t i{0}; i < m_cntItem; ++i) {
      delete m_lstItem[i];
    }
    delete[] m_lstItem;

    m_name = order.m_name;
    m_product = order.m_product;
    m_cntItem = order.m_cntItem;
    m_lstItem = order.m_lstItem;

    order.m_name = "";
    order.m_product = "";
    order.m_lstItem = nullptr;
    order.m_cntItem = 0;
  }
  return *this;
};

CustomerOrder::~CustomerOrder() {
  for (size_t i{0}; i < m_cntItem; ++i) {
    delete m_lstItem[i];
    m_lstItem[i] = nullptr;
  }
  delete[] m_lstItem;
  m_lstItem = nullptr;
}

bool CustomerOrder::isOrderFilled() const {
  bool isOrderFilled{true};
  for (size_t i{0}; i < m_cntItem; ++i) {
    if (m_lstItem[i]->m_isFilled == false) {
      isOrderFilled = false;
      break;
    }
  }
  return isOrderFilled;
}

bool CustomerOrder::isItemFilled(const std::string &itemName) const {
  bool allFilled{true};
  for (size_t i{0}; i < m_cntItem; ++i) {
    if (m_lstItem[i]->m_itemName == itemName) {
      if (m_lstItem[i]->m_isFilled == false) {
        allFilled = false;
        break;
      }
    }
  }
  return allFilled;
}

void CustomerOrder::fillItem(Station &station, std::ostream &os) {
  int count{};
  for (size_t i{0}; i < m_cntItem; ++i) {
    if (station.getItemName() == m_lstItem[i]->m_itemName) {
      ++count;
      if (count == 1) {
        if (station.getQuantity() > 0) {
          station.updateQuantity();
          m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
          m_lstItem[i]->m_isFilled = true;
          os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
        } else {
          os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
        }
      }
    }
  }
}

void CustomerOrder::display(std::ostream &os) const {
  os << m_name << " - " << m_product << "\n";
  for (size_t i{0}; i < m_cntItem; ++i) {
    os << "[" << std::setfill('0') << std::setw(6) << std::right
       << m_lstItem[i]->m_serialNumber << "] ";
    os << std::setfill(' ') << std::setw(m_widthField) << std::left
       << m_lstItem[i]->m_itemName << " - ";
    std::string str = (m_lstItem[i]->m_isFilled) ? "FILLED" : "TO BE FILLED";
    os << str << "\n";
  }
}

std::string CustomerOrder::leftTrim(const std::string &str) {
  auto start = str.find_first_not_of(' ');
  return (start == std::string::npos) ? "" : str.substr(start);
}

std::string CustomerOrder::rightTrim(const std::string &str) {
  auto end = str.find_last_not_of(' ');
  return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}
}