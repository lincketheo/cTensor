//
// Created by Theo Lincke on 1/16/24.
//

#ifndef CTENSOR_COMMON_H
#define CTENSOR_COMMON_H

#include <string>
#include <utility>

class CTensorException : public std::exception {
public:
    std::string what;
    explicit CTensorException(std::string what) : what(std::move(what)) {}
};

#endif //CTENSOR_COMMON_H
