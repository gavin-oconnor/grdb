#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <string>
#include <vector>
#include <string>

struct Column
{
    std::string name;
    std::string type;
    int size;
    bool primary_key;
};

class Table
{
public:
    std::string name;
    std::vector<Column> columns;
    Table(std::string &table_name);
    void add_column(std::string &column_name, std::string &column_type, bool is_primary_key);
};

#endif