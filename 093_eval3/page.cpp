#include "page.hpp"

#include <cstdlib>
#include <cstring>
void Page::Page_inner::parseText(std::istream &s) {
  char c;
  while (s.get(c)) {
    text.push_back(c);
  }
  return;
}

Page::Page_inner *Page::Page_inner::create(std::istream &s) {
  Page::Page_inner *result;
  std::string line;
  std::getline(s, line);
  if (line == "WIN") {
    // Case 1: Win page.
    result = new Page::EndPage(true);
    getline(s, line);
  } else if (line == "LOSE") {
    // Case 2: Lose page.
    result = new Page::EndPage(false);
    getline(s, line);
  } else {
    // Case 3: Choice page. (or invalid page)
    Page::ChoicePage *temp;
    try {
      temp = new Page::ChoicePage(line);
    } catch (const std::domain_error &e) {
      std::cerr << "Invalid Page Format" << std::endl;
      exit(EXIT_FAILURE);
    }
    while (getline(s, line)) {
      if (line[0] == '#') {
        break;
      }
      try {
        temp->addChoice(line);
      } catch (const std::domain_error &e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
      }
    };
    result = temp;
  }
  // Check the line starting with #
  if (line[0] != '#') {
    std::cerr << "Missing \"#\" Line" << std::endl;
    exit(EXIT_FAILURE);
  }
  // Parse the following text.
  result->parseText(s);
  return result;
}

void Page::EndPage::print(std::ostream &s) const {
  s << this->text << std::endl;
  if (this->type==Page::WIN) {
    s << "Congratulations! You have won. Hooray!" << std::endl;
  } else {
    s << "Sorry, you have lost. Better luck next time!" << std::endl;
  }
}

void Page::ChoicePage::addChoice(std::string const &line) {
  // cite: code from eval2
  const char *c_line = line.c_str();
  // Find the colon
  const char *ptr_colon = strchr(c_line, ':');
  if (ptr_colon == NULL) {
    throw std::runtime_error("No Colon Found in Choice Line");
  }
  // Check the number
  char *ptr_after_number = (char *)c_line;
  int num = strtoll(c_line, &ptr_after_number, 10);
  if (ptr_after_number != ptr_colon || num <= 0) {
    throw std::runtime_error("Invalid Number");
  }
  this->choicePages.push_back(num);
  // Parse the text.
  this->choiceText.push_back(ptr_colon + 1);
}

void Page::ChoicePage::print(std::ostream &s) const {
  s << this->text << std::endl;
  s << "What would you like to do?" << std::endl;
  s << std::endl;
  for (size_t i = 0; i < this->choiceText.size(); ++i) {
    s << ' ' << i + 1 << ". " << this->choiceText[i] << std::endl;
  }
}

Page &Page::operator=(const Page &rhs) {
  if (this != &rhs) {
    if (rhs.page != NULL) {
      Page::Page_inner *temp = rhs.page->clone();
      if (this->page != NULL) {
        delete this->page;
      }
      this->page = temp;
    } else {
      if (this->page != NULL) {
        delete this->page;
      }
      this->page = NULL;
    }
  }
  return *this;
}

Page::~Page() {
  if (this->page != NULL) {
    delete this->page;
  }
}

std::istream &operator>>(std::istream &s, Page &rhs){
  Page::Page_inner *temp = Page::Page_inner::create(s);
  if (rhs.page!=NULL)
  {
    delete rhs.page;
  }
  rhs.page=temp;
  return s;
}