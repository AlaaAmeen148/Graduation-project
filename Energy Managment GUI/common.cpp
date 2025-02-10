/**
 * @file common.cpp
 * @author Ahmed Mahdy (mahdyyxv@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "common.hpp"
#include <array>
#include <cstdlib>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <netdb.h>

std::string common::execCommand(const char *cmd) {
  std::array<char, 128> buffer;
  std::string result;

  // Open pipe to the command
  std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }

  // Read output into result
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  system("clear");
  return result;
}

std::vector<std::string> common::filterDevices(const std::string& deviceList, const std::regex& filter) {
    std::vector<std::string> filteredDevices;
    std::istringstream stream(deviceList);
    std::string line;
    while (std::getline(stream, line)) {
        if (std::regex_search(line, filter)) {
            filteredDevices.push_back(line);
        }
    }
    return filteredDevices;
}

bool common::isInternetAvailable() {
    struct hostent* host = gethostbyname("www.google.com");
    return host != nullptr;
}
