#ifndef _STORY_HPP_
#define _STORY_HPP_

#include <iostream>
#include <vector>

#include "page.hpp"

// self-explanatory, the class for story
class Story {
 private:
  std::vector<Page> pages;
  std::string getFileName(std::string dir, int index);
  bool areValidRefernces();
  bool areReferenced();
  bool haveWinAndLose();

 public:
  Story(const std::string & dir);
  void play(int index = 1);
  std::vector<int> getDepth();
  std::vector<std::vector<std::pair<int, int> > > getWinPaths();
};
#endif
