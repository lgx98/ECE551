#include "story.hpp"

#include <cstdlib>
#include <fstream>
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
