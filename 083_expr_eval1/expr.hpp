#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  long num;

 public:
  NumExpression(long n) : num(n) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << num;
    std::string s = ss.str();
    return s;
  }
};

class OpExpression : public Expression {
  char op;
  Expression * lhs;
  Expression * rhs;

 public:
  OpExpression(char op, Expression * lhs, Expression * rhs) :
      op(op),
      lhs(lhs),
      rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << '(' << lhs->toString() << ' ' << op << ' ' << rhs->toString() << ')';
    return ss.str();
  }
  virtual ~OpExpression() {
    delete lhs;
    delete rhs;
  }
};

class PlusExpression : public OpExpression {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : OpExpression('+', lhs, rhs) {}
};

#endif
