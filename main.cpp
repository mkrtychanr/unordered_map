#include <iostream>
#include <cstdio>
#include <string>
#include "unordered_map.hpp"
#include <unordered_map>

int main() {
    unordered_map<std::string, int> map;
    map.insert(std::pair<std::string, int>("Log", 5));
    map.insert(std::pair<std::string, int>("Loh", 5));
    map.insert(std::pair<std::string, int>("Loj", 5));
    return 0;
}