#include <exception>
#include <iostream>
#include <stdexcept>

namespace yapparov
{
  class MinCounter
  {
  private:
    int min_;
    int count_;

  public:
    MinCounter();
    void operator()(int next);
    int operator()() const;
  };

  MinCounter::MinCounter() :
    min_(0),
    count_(0)
  {}

  void MinCounter::operator()(int next)
  {
    if (count_ == 0 || next < min_)
    {
      min_ = next;
      count_ = 1;
    }
    else if (next == min_)
    {
      ++count_;
    }
  }

  int MinCounter::operator()() const
  {
    return count_;
  }
  int func()
  {
    MinCounter count;
    int x = 0;
    while (std::cin >> x)
    {
      if (x == 0)
      {
        return count();
      }
      count(x);
    }
    throw std::invalid_argument("invalid x");
  }
}

int main()
{
  try
  {
    const int result = yapparov::func();
    std::cout << result << "\n";
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
