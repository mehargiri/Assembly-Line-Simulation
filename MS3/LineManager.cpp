#include "LineManager.h"
#include <fstream>
#include <algorithm>

namespace sdds {

LineManager::LineManager(const std::string &file,
                         const std::vector<Workstation *> &stations) {
  std::ifstream theFile(file);
  if (!theFile)
    throw std::string("Cannot open the file");
  else {
    Workstation* currentWS{};
    Workstation* nextWS{};
    Workstation *firstWS{};

    std::string tempStr;
    std::string currentWSName;
    std::string nextWSName;

    Utilities util;
    size_t nextPos{};
    bool more{};

    while (std::getline(theFile, tempStr)) {
      currentWSName = util.extractToken(tempStr, nextPos, more);
      currentWS = *std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
        return ws->getItemName() == currentWSName;
      });
      m_activeLine.push_back(currentWS);

      if (more) {
        nextWSName = util.extractToken(tempStr, nextPos, more);
        nextWS = *std::find_if(stations.begin(), stations.end(), [&](Workstation*ws) {
          return ws->getItemName() == nextWSName;
        });
        currentWS->setNextStation(nextWS);
      }
    }

    std::for_each(stations.begin(), stations.end(), [&](Workstation* temp) {
      firstWS = *std::find_if(stations.begin(), stations.end(), [&](Workstation *ws) {
        return ws->getNextStation() == firstWS;
      });
    });

    m_firstStation = firstWS;
  }
  theFile.close();
  m_cntCustomerOrder = g_pending.size();
}

void LineManager::reorderStations() {
  Workstation *temp = m_firstStation;
  size_t i{};
  while (temp != nullptr) {
    m_activeLine[i] = temp;
    temp = temp->getNextStation();
    ++i;
  }
}

bool LineManager::run(std::ostream &os) {
  static size_t iterationNum{};
  os << "Line Manager Iteration: " << ++iterationNum << '\n';

  if (!g_pending.empty()) {
    *m_firstStation += std::move(g_pending.front());
    g_pending.pop_front();
  }
  std::for_each(m_activeLine.begin(), m_activeLine.end(),
                [&os](Workstation *ws) { ws->fill(os); });
  std::for_each(m_activeLine.begin(), m_activeLine.end(),
                [](Workstation *ws) { ws->attemptToMoveOrder(); });
  bool result = (m_cntCustomerOrder == (g_completed.size() + g_incomplete.size()));
  return result;
}

void LineManager::display(std::ostream &os) const {
  if (!m_activeLine.empty()) {
    for (auto &elem : m_activeLine) {
      elem->display(os);
    }
  }
}
}