#include "./page.hpp"

#include <cstring>
void Page::parseText(std::istream & s) {
  char c;
  while (s.get(c)) {
    text.push_back(c);
  }
  return;
}

std::ostream & operator<<(std::ostream & s, const Page & rhs) {
  rhs.print(s);
  return s;
}

Page * parsePage(std::istream & s) {
  Page * result;
  std::string line;
  std::getline(s, line);
  if (line == "WIN") {
    // Case 1: Win page.
    result = new EndPage(true);
    getline(s, line);
  }
  else if (line == "LOSE") {
    // Case 2: Lose page.
    result = new EndPage(false);
    getline(s, line);
  }
  else {
    // Case 3: Choice page. (or invalid page)
    ChoicePage * temp;
    try {
      temp = new ChoicePage(line);
    }
    catch (const std::domain_error & e) {
      std::cerr << "Invalid Page Format" << std::endl;
      exit(EXIT_FAILURE);
    }
    while (getline(s, line)) {
      if (line[0] == '#') {
        break;
      }
      try {
        temp->addChoice(line);
      }
      catch (const std::domain_error & e) {
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

void EndPage::print(std::ostream & s) const {
  s << this->text << std::endl;
  s << std::endl;
  if (this->isWin) {
    s << "Congratulations! You have won. Hooray!" << std::endl;
  }
  else {
    s << "Sorry, you have lost. Better luck next time!" << std::endl;
  }
}

void ChoicePage::addChoice(std::string const & line) {
  // cite: code from eval2
  const char * c_line = line.c_str();
  // Find the colon
  const char * ptr_colon = strchr(c_line, ':');
  if (ptr_colon == NULL) {
    std::cerr << "No Colon Found in Choice Line" << std::endl;
    exit(EXIT_FAILURE);
  }
  // Check the number
  char * ptr_after_number = (char *)c_line;
  int num = strtoll(c_line, &ptr_after_number, 10);
  if (ptr_after_number != ptr_colon || num <= 0) {
    std::cerr << "Invalid Number" << std::endl;
    exit(EXIT_FAILURE);
  }
  this->choicePages.push_back(num);
  // Parse the text.
  this->choiceText.push_back(ptr_colon + 1);
}

void ChoicePage::print(std::ostream & s) const {
  s << this->text << std::endl;
  s << std::endl;
  s << "What would you like to do?" << std::endl;
  s << std::endl;
  for (size_t i = 0; i < this->choiceText.size(); ++i) {
    s << ' ' << i << ". " << this->choiceText[i] << std::endl;
  }
}
