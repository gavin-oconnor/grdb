#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <map>
#include <filesystem>
#include "table.h"

class Engine
{
public:
    std::string database_name;
    std::unordered_map<std::string, Table *> tables;
    Engine(std::string db_name);

private:
    bool create_if_not_exists();
    void get_or_create_metadata();
};

#endif