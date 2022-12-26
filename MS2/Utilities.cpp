#include "Utilities.h"

namespace sdds {
char Utilities::m_delimiter{};

void Utilities::setFieldWidth(size_t newWidth) { m_widthField = newWidth; }

size_t Utilities::getFieldWidth() const { return m_widthField; }

std::string Utilities::extractToken(const std::string &str, size_t &next_pos,
                                    bool &more) {
  size_t indexOfDelimiter = str.find(getDelimiter(), next_pos);
  std::string token = str.substr(next_pos, indexOfDelimiter - next_pos);

  if (indexOfDelimiter == next_pos) {
    more = false;
    throw std::string("Failed to find delimiter");
  }
  next_pos = indexOfDelimiter + 1;
  auto tokenSize = token.size();
  auto updateWidthField =
      (tokenSize > m_widthField) ? tokenSize : m_widthField;

  setFieldWidth(updateWidthField);
  more = (indexOfDelimiter != std::string::npos);

  return token;
}

void Utilities::setDelimiter(char newDelimiter) { m_delimiter = newDelimiter; }

char Utilities::getDelimiter() {
  return m_delimiter;
}
}