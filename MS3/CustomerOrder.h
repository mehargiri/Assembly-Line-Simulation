#ifndef CUSTOMORDER_H_
#define CUSTOMORDER_H_

#include "Station.h"
#include "Utilities.h"
#include <string>
#include <stdbool.h>
namespace sdds {
struct Item {
  std::string m_itemName{};
  size_t m_serialNumber{0};
  bool m_isFilled{false};
  Item() = default;
  Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder {
  std::string m_name{};
  std::string m_product{};
  size_t m_cntItem{};
  Item **m_lstItem{};
  static size_t m_widthField;

public:
  CustomerOrder() = default;
  CustomerOrder(const std::string &str);
  CustomerOrder(const CustomerOrder &);
  CustomerOrder& operator=(const CustomerOrder&) = delete;
  CustomerOrder(CustomerOrder && order) noexcept;
  CustomerOrder &operator=(CustomerOrder && order) noexcept;
  ~CustomerOrder();
  bool isOrderFilled() const;
  bool isItemFilled(const std::string &itemName) const;
  void fillItem(Station &station, std::ostream &os);
  void display(std::ostream& os) const;

  std::string leftTrim(const std::string& str);
  std::string rightTrim(const std::string& str);
};
}
#endif