#include <iostream>
#include "log.h"

void log(const std::stringstream &msg) {
  log(msg.str());
}

void log(const std::string msg) {
  std::cout << msg << std::endl;
}
