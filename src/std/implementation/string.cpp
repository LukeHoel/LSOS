#include "../string.h"
namespace std {
void string::setToCString(const char *input) {
  innerCString = new char[strlen(input)];
  strncpy(innerCString, input, strlen(input));
}
bool string::isSame(const char *input) {
  return strcmp(innerCString, input) == 0;
}
// Constructor
string::string() { setToCString(""); }
string::string(const string &str) { setToCString(str.c_str()); }
string::string(const string &str, size_t pos, size_t len) {
  innerCString = new char[len];
  strncpy(innerCString, str.c_str() + pos, len);
}
string::string(const char *s) { setToCString(s); }
string::string(const char *s, size_t n) {}
string::string(size_t n, char c) {
  innerCString = new char[n];
  for (size_t i = 0; i < n; i++) {
    innerCString[i] = c;
  }
  innerCString[n] = '\0';
}
// Destructor
string::~string() { delete[] innerCString; }
// Assignment
string &string::operator=(const string &str) {
  setToCString(str.c_str());
  return *this;
}
string &string::operator=(const char *s) {
  setToCString(s);
  return *this;
}
string &string::operator=(char c) {
  innerCString = new char[2];
  innerCString[0] = c;
  innerCString[1] = '\0';
  return *this;
}
const char *string::c_str() const { return innerCString; }
bool string::operator==(const string &str) { return isSame(str.c_str()); }
bool string::operator==(const char *s) { return isSame(s); }
} // namespace std
