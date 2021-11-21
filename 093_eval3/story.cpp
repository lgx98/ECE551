#include "story.hpp"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <sstream>

std::string Story::getFileName(std::string dir, int index) {
  std::stringstream ss;
  ss << dir << "/page" << index << ".txt";
  return ss.str();
}

Story::Story(const std::string & dir) {
  int i = 1;
  std::string fileName = getFileName(dir, i);
  std::ifstream ifs(fileName.c_str(), std::ifstream::in);
  if (!ifs.is_open()) {
    throw std::runtime_error("Story not found in: \"" + dir + "\".");
  }
  do {
    this->pages.push_back(Page(ifs));
    i++;
    fileName = getFileName(dir, i);
    ifs.close();
    ifs.open(fileName.c_str());
  } while (ifs.is_open());
  ifs.close();
  if (!areValidRefernces()) {
    throw std::runtime_error("Invalid references.");
  }
  if (!areReferenced()) {
    throw std::runtime_error("Some pages are not referenced.");
  }
  if (!haveWinAndLose()) {
    throw std::runtime_error("The story do not have both win and lose.");
  }
}

bool Story::areValidRefernces() {
  for (size_t i = 0; i < this->pages.size(); i++) {
    std::vector<int> neigh = this->pages[i].getNeighbors();
    for (size_t j = 0; j < neigh.size(); j++) {
      if (neigh[j] > (int)pages.size()) {
        return false;
      }
    }
  }
  return true;
}

bool Story::areReferenced() {
  std::vector<bool> isReferenced(this->pages.size(), false);
  for (size_t i = 0; i < this->pages.size(); i++) {
    std::vector<int> neigh = this->pages[i].getNeighbors();
    for (size_t j = 0; j < neigh.size(); j++) {
      isReferenced[neigh[j] - 1] = true;
    }
  }
  bool accumulator = true;
  for (size_t i = 1; i < isReferenced.size(); i++) {
    accumulator &= isReferenced[i];
  }
  return accumulator;
}

bool Story::haveWinAndLose() {
  bool haveWin = false;
  bool haveLose = false;
  for (size_t i = 0; i < this->pages.size(); i++) {
    haveWin |= this->pages[i].getType() == Page::WIN;
    haveLose |= this->pages[i].getType() == Page::LOSE;
  }
  return haveWin & haveLose;
}

void Story::play(int index) {
  Page & currentPage = this->pages[index - 1];
  std::cout << currentPage;
  if (currentPage.getType() == Page::WIN || currentPage.getType() == Page::LOSE) {
    return;
  }
  std::vector<int> choiceIndexes = currentPage.getNeighbors();
  std::string userInput;
  int userChoice;
  while (true) {
    std::cin >> userInput;
    userChoice = std::atoi(userInput.c_str());
    if (userChoice > 0 && userChoice <= (int)choiceIndexes.size()) {
      break;
    }
    std::cout << "That is not a valid choice, please try again" << std::endl;
  }
  play(choiceIndexes[userChoice - 1]);
}

std::vector<int> Story::getDepth() {
  std::vector<int> depth(this->pages.size(), 0);
  std::queue<int> toVisit({1});
  std::vector<bool> visited(this->pages.size(), false);
  visited[0] = true;
  while (!toVisit.empty()) {
    int currNode = toVisit.front();
    toVisit.pop();
    std::vector<int> neigh = this->pages[currNode - 1].getNeighbors();
    for (std::vector<int>::iterator it = neigh.begin();
         (it != neigh.end()) && (!visited[*it - 1]);
         ++it) {
      depth[*it - 1] = depth[currNode - 1] + 1;
      toVisit.push(*it);
      visited[*it - 1] = true;
    }
  }
  return depth;
}

std::vector<std::pair<int, int> > Story::getWinPath() {
  std::vector<std::pair<int, int> > visitedFrom(this->pages.size(),
                                                std::make_pair(-1, 0));
  std::queue<int> toVisit({1});
  std::vector<bool> visited(this->pages.size(), false);
  visited[0] = true;
  int currNode = 1;
  while (this->pages[currNode - 1].getType() != Page::WIN) {
    if (toVisit.empty()) {
      return std::vector<std::pair<int, int> >();
    }
    currNode = toVisit.front();
    toVisit.pop();
    std::vector<int> neigh = this->pages[currNode - 1].getNeighbors();
    for (int i = 0; (i < (int)neigh.size()) && (!visited[neigh[i] - 1]); ++i) {
      visitedFrom[neigh[i] - 1] = std::make_pair(currNode, i + 1);
      toVisit.push(neigh[i]);
      visited[neigh[i] - 1] = true;
    }
  }
  int winNode = currNode;
  std::vector<std::pair<int, int> > path;
  for (; visitedFrom[currNode - 1].first != -1;
       currNode = visitedFrom[currNode - 1].first) {
    path.push_back(visitedFrom[currNode - 1]);
  }
  std::reverse(path.begin(), path.end());
  path.push_back(std::make_pair(winNode, 0));
  return path;
}
