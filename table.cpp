#include "table.h"

Table::Table(std::string &table_name)
{
    name = table_name;
}

void Table::add_column(std::string &column_name, std::string &column_type, bool is_primary_key)
{
    Column new_col;
    new_col.name = column_name;
    new_col.primary_key = is_primary_key;
    if (column_type == "INT")
    {
        new_col.type = "INT";
        int size = 4;
    }
    else if (column_name.length() > 7 && column_name.substr(0, 7) == "VARCHAR")
    {
        new_col.type = "VARCHAR";
        int open_paren_index = column_type.find("(");
        int close_paren_index = column_type.find(")");
        new_col.size = std::stoi(column_name.substr(open_paren_index + 1, close_paren_index - open_paren_index));
    }
    columns.push_back(new_col);
}