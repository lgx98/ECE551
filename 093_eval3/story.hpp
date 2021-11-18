#ifndef _STORY_HPP_
#define _STORY_HPP_

#include <iostream>
#include <vector>

#include "page.hpp"

class Story {
private:
  std::vector<Page> pages;
  std::string getFileName(std::string dir, int index);
  bool areValidRefernces();
  bool areReferenced();
  bool haveWinAndLose();

public:
  Story(const std::string &dir);
  void play(int index=1);
};
#endif