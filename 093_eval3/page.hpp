#ifndef _PAGE_HPP_
#define _PAGE_HPP_

#include <exception>
#include <iostream>
#include <vector>

class Page {
public:
  enum type_t { EMPTY, WIN, LOSE, CHOICE };

private:
  class Page_inner {
  protected:
    std::string text;
    void parseText(std::istream &s);

  public:
    type_t type;
    virtual Page_inner *clone() const = 0;      // Copy constructor
    static Page_inner *create(std::istream &s); // Constructor
    Page_inner(type_t type) : type(type){};
    virtual ~Page_inner(){};
    virtual std::vector<int> getNeighbors() const = 0;
    virtual void print(std::ostream &s) const = 0;
  };

  class EndPage : public Page_inner {
  private:
  public:
    Page_inner *clone() const { return new EndPage(*this); };
    EndPage(bool isWin) : Page_inner(isWin ? WIN : LOSE){};
    void print(std::ostream &s) const;
    std::vector<int> getNeighbors() const { return std::vector<int>(); };
    friend Page_inner *Page_inner::create(std::istream &s);
  };

  class ChoicePage : public Page_inner {
  private:
    std::vector<int> choicePages;
    std::vector<std::string> choiceText;
    void addChoice(std::string const &line);

  public:
    Page_inner *clone() const { return new ChoicePage(*this); };
    ChoicePage(std::string const &line) : Page_inner(CHOICE) {
      this->addChoice(line);
    };
    void print(std::ostream &s) const;
    std::vector<int> getNeighbors() const { return this->choicePages; }
    friend Page_inner *Page_inner::create(std::istream &s);
  };

  Page_inner *page;

public:
  Page() : page(NULL) {}
  explicit Page(std::istream &s) : page(Page_inner::create(s)) {}
  Page(const Page &rhs) : page(NULL) {
    this->page = (rhs.page != NULL) ? rhs.page->clone() : NULL;
  }
  Page &operator=(const Page &rhs);
  ~Page();
  type_t getType() { return (this->page != NULL) ? this->page->type : EMPTY; };
  friend std::ostream &operator<<(std::ostream &s, const Page &rhs) {
    if (rhs.page != NULL) {
      rhs.page->print(s);
    }
    return s;
  };
  std::vector<int> getNeighbors() const {
    return (this->page != NULL) ? this->page->getNeighbors()
                                : std::vector<int>();
  }
  friend std::istream &operator>>(std::istream &s, Page &rhs);
};

#endif
