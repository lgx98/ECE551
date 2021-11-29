#ifndef _PAGE_HPP_
#define _PAGE_HPP_

#include <exception>
#include <iostream>
#include <vector>

/* This class creates the illusion of a simple plain Page class,
   while actually using complicated stuff like inheritance inside. */
class Page {
 public:
  enum type_t {
    EMPTY,  // page is NULL, default value
    WIN,
    LOSE,
    CHOICE
  };

 private:
  // This class is used as the parent class for all kinds of pages.
  class Page_inner {
   protected:
    std::string text;
    void parseText(std::istream & s);

   public:
    // Yes we have a property "type", but we are not relying on it to choose the right method.
    type_t type;
    virtual Page_inner * clone() const = 0;        // dynamic copy constructor
    static Page_inner * create(std::istream & s);  // dynamic constructor
    Page_inner(type_t type) : type(type){};
    virtual ~Page_inner(){};
    virtual std::vector<int> getNeighbors() const = 0;
    virtual void print(std::ostream & s) const = 0;
  };

  // win page or lose page
  class EndPage : public Page_inner {
   public:
    Page_inner * clone() const { return new EndPage(*this); };
    EndPage(bool isWin) : Page_inner(isWin ? WIN : LOSE){};
    void print(std::ostream & s) const;
    // end pages have no neighbors
    std::vector<int> getNeighbors() const { return std::vector<int>(); };
    friend Page_inner * Page_inner::create(std::istream & s);
  };

  class ChoicePage : public Page_inner {
   private:
    /* Could also be defined as std::pair<int, std::string> or even a choice_t,
       but this makes getNeighbors() much simpler. */
    std::vector<int> choicePages;
    std::vector<std::string> choiceText;
    void addChoice(std::string const & line);

   public:
    Page_inner * clone() const { return new ChoicePage(*this); };
    // Since the first choice is already read at this point, we can feed it into the constructor.
    ChoicePage(std::string const & line) : Page_inner(CHOICE) { this->addChoice(line); };
    void print(std::ostream & s) const;
    std::vector<int> getNeighbors() const { return this->choicePages; }
    friend Page_inner * Page_inner::create(std::istream & s);
  };

  // Actual page inside the Page class.
  Page_inner * page;

 public:
  Page() : page(NULL) {}
  // Actually the class of the page is dynamically decided by the input.
  explicit Page(std::istream & s) : page(Page_inner::create(s)) {}
  // Dynamically choose the proper way to copy construct.
  Page(const Page & rhs) : page(NULL) {
    this->page = (rhs.page != NULL) ? rhs.page->clone() : NULL;
  }
  // Rule of three: assignment operator.
  Page & operator=(const Page & rhs);
  // Rule of three: destructor.
  ~Page() {
    if (this->page != NULL) {
      delete this->page;
    }
  }
  type_t getType() { return (this->page != NULL) ? this->page->type : EMPTY; };
  friend std::ostream & operator<<(std::ostream & s, const Page & rhs) {
    if (rhs.page != NULL) {
      rhs.page->print(s);
    }
    return s;
  };
  std::vector<int> getNeighbors() const {
    return (this->page != NULL) ? this->page->getNeighbors() : std::vector<int>();
  }
  // Read a new page and overwrite the old content.
  friend std::istream & operator>>(std::istream & s, Page & rhs);
};

#endif
