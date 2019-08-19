#ifndef STRING_H
#define STRING_H
#include "common.h"
#include "cstring.h"
namespace std {
class string {
  char *innerCString;
  void setToCString(const char *input);
  bool isSame(const char *input);

public:
  static const size_t npos = -1;
  // Constructor
  string();
  string(const string &str);
  string(const string &str, size_t pos, size_t len = npos);
  string(const char *s);
  string(const char *s, size_t n);
  string(size_t n, char c);
  // Destructor
  ~string();
  // Assignment=
  string &operator=(const string &str);
  string &operator=(const char *s);
  string &operator=(char c);
  const char *c_str() const;
  bool operator==(const string &str);
  bool operator==(const char *s);
};
} // namespace std
#endif
