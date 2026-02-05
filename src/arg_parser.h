#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <string>
#include <vector>

class ArgParser {
 public:
  static std::string Parse(int argc, char* argv[]);
  static void PrintUsage(const char* progname);
  static void PrintHelp(const char* progname);

 private:
  ArgParser() = delete;
};

#endif // ARG_PARSER_H
