/**
 * @file common.hpp
 * @author Ahmed Mahdy (mahdyyxv@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <string>
#include <cstdint>
#include <vector>
#include <regex>
namespace common {
/**
 * @brief Enum class for Error codes
 * 
 */

enum class ErrorCodes : uint8_t
{
    ERROR = 0, /*!< Sys Error*/
    NORMAL, /*!< No Sys Error*/
    WARNING, /*!< Warning for unintended beahviour*/
    NOT_DEFINED, /*!< Not Defined sys Param*/
};
/**
 * @brief Executing system Command 
 * 
 * @param cmd command to be executed
 * @return std::string  command result
 */
std::string execCommand(const char *cmd);
std::vector<std::string> filterDevices(const std::string& deviceList, const std::regex& filter);
bool isInternetAvailable();
}
