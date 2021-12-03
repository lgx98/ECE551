#include "story.hpp"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <sstream>

/* A helper function that formats the filename.
 */
std::string Story::getFileName(std::string dir, int index) {
  std::stringstream ss;
  ss << dir << "/page" << index << ".txt";
  return ss.str();
}

/* Construct story from the given directory, plus basic checks.
 */
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
    throw std::runtime_error("The story does not have both win and lose.");
  }
}

/* Check if the references are valid numbers.
 */
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

/* Check if all the pages are being referenced by others.
 */
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

/* Check if there are both win and lose pages in the story.
 */
bool Story::haveWinAndLose() {
  bool haveWin = false;
  bool haveLose = false;
  for (size_t i = 0; i < this->pages.size(); i++) {
    haveWin |= this->pages[i].getType() == Page::WIN;
    haveLose |= this->pages[i].getType() == Page::LOSE;
  }
  return haveWin & haveLose;
}

/* Play the story from the given page.
   I think this is equivalent to a tail recursion.
 */
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
  return;
}

/* Calculate the depth of each page by BFS.
 */
std::vector<int> Story::getDepth() {
  std::vector<int> depth(this->pages.size(), 0);
  std::queue<int> toVisit({1});
  std::vector<bool> visited(this->pages.size(), false);
  visited[0] = true;
  while (!toVisit.empty()) {
    int currNode = toVisit.front();
    toVisit.pop();
    std::vector<int> neigh = this->pages[currNode - 1].getNeighbors();
    /* This did not work somehow
    for (std::vector<int>::iterator it = neigh.begin();
         (it != neigh.end()) && (!visited[*it - 1]);
         ++it) {
      depth[*it - 1] = depth[currNode - 1] + 1;
      toVisit.push(*it);
      visited[*it - 1] = true;
    }
    */
    for (std::vector<int>::iterator it = neigh.begin(); it != neigh.end(); ++it) {
      if (!visited[*it - 1]) {
        depth[*it - 1] = depth[currNode - 1] + 1;
        toVisit.push(*it);
        visited[*it - 1] = true;
      }
    }
  }
  return depth;
}

/* Search all the paths from starting page to a winning page by DFS.
 */
std::vector<std::vector<std::pair<int, int> > > Story::getWinPaths() {
  /* pair.first: which node is this (counting from 1)
     pair.second: which choice led to this node (counting from 1)
   */
  std::vector<std::vector<std::pair<int, int> > > winPaths;
  /* when all the paths from 3rd Node are traversed and we backtracked:
   *
   * toVisit:
   * buttom                top
   * V                     V
   * | Neighs of| Neighs of| 
   * | 1st Node | 2nd Node |
   *
   * visitedPath:
   *   1st Node   2nd Node   3rd Node
   *
   * At this moment, we need to pop 3rd Node from visitedPath
   * before visiting other neighbors of 2nd Node.
   * And we need a reminder("|") in toVisit to determine that.
   * In the code, that is std::make_pair(0, 0)
   */
  std::vector<std::pair<int, int> > toVisit;  // used as a stack
  toVisit.push_back(std::make_pair(1, 0));    // starting page
  std::vector<std::pair<int, int> > visitedPath;
  // Cache the visited nodes to avoid O(n) search in visitedPath
  std::vector<bool> visited(this->pages.size(), false);

  while (toVisit.size() > 0) {
    std::pair<int, int> currNode = *toVisit.rbegin();
    toVisit.pop_back();
    if (currNode.first == 0) {  // backtrack
      visited[visitedPath.rbegin()->first - 1] = false;
      visitedPath.pop_back();
      continue;
    }
    // "visit" the node
    visitedPath.push_back(currNode);
    visited[currNode.first - 1] = true;
    // save winning path
    if (this->pages[currNode.first - 1].getType() == Page::WIN) {
      winPaths.push_back(visitedPath);
      std::vector<std::pair<int, int> > & currPath = *winPaths.rbegin();
      /* convert pair.second
       * from "which choice led to this node"
       * to "which choice leads to the next node"
       */
      for (int i = 0; i < (int)currPath.size() - 1; ++i) {
        currPath[i].second = currPath[i + 1].second;
      }
      currPath.rbegin()->second = 0;
    }
    // indicator for entering a deeper node
    toVisit.push_back(std::make_pair(0, 0));
    // add all unvisited neighbors to toVisit
    std::vector<int> neigh = this->pages[currNode.first - 1].getNeighbors();
    for (int i = (int)neigh.size() - 1; i >= 0; --i) {
      if (!visited[neigh[i] - 1]) {
        toVisit.push_back(std::make_pair(neigh[i], i + 1));
      }
    }
  }
  return winPaths;
}
