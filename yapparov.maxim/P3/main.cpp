#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <new>
#include <stdexcept>

namespace yapparov {
const size_t maxElements = 10000;
bool isNumber(const char *s);
void readDims(std::istream &in, size_t &str, size_t &stb);
void readElements(std::istream &in, int *data, size_t n);
size_t numRow(const int *data, size_t str, size_t stb);
} // namespace yapparov

int main(int argc, char **argv) {
  int *dynamic = nullptr;
  try {
    if (argc < 4) {
      throw std::invalid_argument("Not enough arguments");
    }
    if (argc > 4) {
      throw std::invalid_argument("Too many arguments");
    }
    int mode = 0;
    if (argv[1][0] == '1' && argv[1][1] == '\0') {
      mode = 1;
    } else if (argv[1][0] == '2' && argv[1][1] == '\0') {
      mode = 2;
    } else if (yapparov::isNumber(argv[1])) {
      throw std::invalid_argument("First parameter is out of range");
    } else {
      throw std::invalid_argument("First parameter is not a number");
    }
    std::ifstream input(argv[2]);
    if (!input) {
      throw std::runtime_error("Cannot open input file");
    }
    size_t str = 0;
    size_t stb = 0;
    yapparov::readDims(input, str, stb);
    const size_t n = str * stb;
    size_t result = 0;
    if (mode == 1) {
      if (n > yapparov::maxElements) {
        throw std::runtime_error("Matrix is too large for fixed array");
      }
      int data[yapparov::maxElements];
      yapparov::readElements(input, data, n);
      result = yapparov::numRow(data, str, stb);
    } else {
      dynamic = new int[n];
      yapparov::readElements(input, dynamic, n);
      result = yapparov::numRow(dynamic, str, stb);
      delete[] dynamic;
      dynamic = nullptr;
    }
    std::ofstream output(argv[3]);
    if (!output) {
      throw std::runtime_error("Cannot open output file");
    }
    output << result << '\n';
  } catch (const std::invalid_argument &e) {
    delete[] dynamic;
    std::cerr << e.what() << '\n';
    return 1;
  } catch (const std::bad_alloc &) {
    delete[] dynamic;
    std::cerr << "Not enough memory\n";
    return 2;
  } catch (const std::exception &e) {
    delete[] dynamic;
    std::cerr << e.what() << '\n';
    return 2;
  }
  return 0;
}

namespace yapparov {
bool isNumber(const char *s) {
  size_t i = 0;
  if (s[i] == '\0') {
    return false;
  }
  for (; s[i] != '\0'; ++i) {
    if (s[i] < '0' || s[i] > '9') {
      return false;
    }
  }
  return true;
}

void readDims(std::istream &in, size_t &str, size_t &stb) {
  long long r = 0;
  long long c = 0;
  if (!(in >> r >> c) || r < 0 || c < 0) {
    throw std::runtime_error("Invalid matrix dimensions");
  }
  str = r;
  stb = c;
  if (stb != 0 && str * stb / stb != str) {
    throw std::runtime_error("Matrix is too large");
  }
}

void readElements(std::istream &in, int *data, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    if (!(in >> data[i])) {
      throw std::runtime_error("Invalid matrix elements");
    }
  }
}

size_t numRow(const int *data, size_t str, size_t stb) {
  size_t best_row = 0;
  size_t best_len = 0;
  for (size_t i = 0; i < str; ++i) {
    size_t cur = 0;
    for (size_t j = 0; j < stb; ++j) {
      if (j > 0 && data[i * stb + j] == data[i * stb + j - 1]) {
        ++cur;
      } else {
        cur = 1;
      }

      if (cur > best_len) {
        best_len = cur;
        best_row = i + 1;
      }
    }
  }
  return best_row;
}
} // namespace yapparov
