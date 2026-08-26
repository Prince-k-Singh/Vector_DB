#pragma once

#include <any>
#include <string>
#include <unordered_map>

struct Metadata {
    std::unordered_map<std::string, std::any> data;
};