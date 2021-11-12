#ifndef _PAGE_HPP_
#define _PAGE_HPP_

#include <exception>
#include <iostream>
#include <vector>

class Page {
 protected:
  void parseText(std::istream & s);
  std::string text;

 public:
  virtual ~Page(){};
  virtual void print(std::ostream & s) const = 0;

  friend Page * parsePage(std::istream & s);
};

std::ostream & operator<<(std::ostream & s, const Page & rhs);

// Works like a constructor, but it needs to decide the type of the page.
// It fills in the text and choice text in place, avoiding copies.
Page * parsePage(std::istream & s);

class EndPage : public Page {
 private:
  bool isWin;

 public:
  EndPage(bool isWin) : isWin(isWin){};
  void print(std::ostream & s) const;
  friend Page * parsePage(std::istream & s);
};

class ChoicePage : public Page {
 private:
  std::vector<int> choicePages;
  std::vector<std::string> choiceText;
  void addChoice(std::string const & line);

 public:
  ChoicePage(std::string const & line) { this->addChoice(line); };
  void print(std::ostream & s) const;
  friend Page * parsePage(std::istream & s);
};

#endif
