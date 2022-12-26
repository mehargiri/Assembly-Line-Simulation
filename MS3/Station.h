#ifndef STATION_H_
#define STATION_H_

#include <ostream>
#include <string>
#include <stdbool.h>
namespace sdds {
class Station {
  int m_stationId{};
  std::string m_itemName{};
  std::string m_stationDescri{};
  unsigned int m_serialNumber{};
  unsigned int m_totalItems{};
  static size_t m_widthField;
  static int id_generator;

public:
  Station(const std::string &str);
  const std::string &getItemName() const;
  size_t getNextSerialNumber();
  size_t getQuantity() const;
  void updateQuantity();
  void display(std::ostream &os, bool full) const;

  std::string leftTrim(const std::string& str);
  std::string rightTrim(const std::string& str);
};
}
#endif