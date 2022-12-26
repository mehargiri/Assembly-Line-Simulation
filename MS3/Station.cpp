#include "Utilities.h"
#include "Station.h"
#include <iostream>
#include <string>
#include <iomanip>
namespace sdds {
size_t Station::m_widthField{};
int Station::id_generator{};

Station::Station(const std::string &str) {
  m_stationId = id_generator++;
  Utilities util;
  size_t nextPos{};
  bool more{};
  try {
    m_itemName = leftTrim(rightTrim(util.extractToken(str, nextPos, more)));
    m_serialNumber = std::stoi(leftTrim(rightTrim(util.extractToken(str, nextPos, more))));
    m_totalItems = std::stoi(leftTrim(rightTrim(util.extractToken(str, nextPos, more))));

    auto utilWidthField = util.getFieldWidth();
    m_widthField =
        (utilWidthField > m_widthField) ? utilWidthField : m_widthField;

    m_stationDescri = leftTrim(rightTrim(util.extractToken(str, nextPos, more)));
  } catch (const std::string& error) {
    std::cout << error << '\n';
  }
}

const std::string &Station::getItemName() const { return m_itemName; }

size_t Station::getNextSerialNumber() { return m_serialNumber++; }

size_t Station::getQuantity() const { return m_totalItems; }

void Station::updateQuantity() {
  --m_totalItems;
  if (m_totalItems < 0) m_totalItems = 0;
}

void Station::display(std::ostream &os, bool full) const {
  os << std::setfill('0') << std::setw(3) << std::right << m_stationId << " | ";
  os << std::setfill(' ') << std::setw(m_widthField) << std::left << m_itemName << " | ";
  os << std::setfill('0') << std::setw(6) << std::right << m_serialNumber
     << " |";
  if (full) {
    os << " " << std::setw(4) << std::setfill(' ') << std::right << m_totalItems
       << " | ";
    os << m_stationDescri << '\n';
  } else {
    os << '\n';
  }
}

std::string Station::leftTrim(const std::string &str) {
  auto start = str.find_first_not_of(' ');
  return (start == std::string::npos) ? "" : str.substr(start);
}

std::string Station::rightTrim(const std::string &str) {
  auto end = str.find_last_not_of(' ');
  return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}

}