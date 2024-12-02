#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "table.h"
#include "engine.h"

std::vector<std::string> split(std::string &target_string, const std::string delimiter)
{
    std::vector<std::string> result;

    if (delimiter.length() == 0)
    {
        for (std::string::size_type i = 0; i < target_string.length(); i++)
        {
            result.push_back(std::string(1, target_string[i]));
        }
    }
    else
    {
        char d = delimiter[0];
        std::string curr_string = "";

        for (std::string::size_type i = 0; i < target_string.length(); i++)
        {
            if (target_string[i] == d)
            {
                result.push_back(curr_string);
                curr_string = ""; // Reset for the next substring
            }
            else
            {
                curr_string += target_string[i];
            }
        }

        // Add the last substring if any
        if (!curr_string.empty())
        {
            result.push_back(curr_string);
        }
    }

    return result;
}

Engine::Engine(std::string db_name)
{
    database_name = db_name;
    create_if_not_exists();
    get_or_create_metadata();
}

bool Engine::create_if_not_exists()
{
    if (std::filesystem::exists(database_name) && std::filesystem::is_directory(database_name))
    {
        return true;
    }
    if (std::filesystem::create_directory(database_name))
    {
        return true;
    }
    return false;
}

void Engine::get_or_create_metadata()
{
    if (std::filesystem::exists(database_name + "/metadata.txt"))
    {
        std::string fileName = database_name + "/metadata.txt";
        std::ifstream file(fileName);

        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                if (line.substr(0, 6) == "tables")
                {
                    int i = 0;
                    while (i < line.length() && line.substr(i, 1) != "=")
                    {
                        i++;
                    }
                    std::string curr_table = "";
                    for (int j = i + 1; j < line.length(); j++)
                    {
                        if (line.substr(j, 1) == ",")
                        {
                            tables.emplace(curr_table, new Table(curr_table));
                            curr_table = "";
                        }
                        else
                        {
                            curr_table += line.substr(j, 1);
                        }
                    }
                    if (curr_table.length())
                    {
                        tables.emplace(curr_table, new Table(curr_table));
                    }
                }
                if (line.substr(0, 6) == "table_")
                {
                    const std::string table_name = line.substr(6, line.find("=") - 6);
                    if (tables.find(table_name) != tables.end())
                    {
                        std::vector<std::string> values = split(split(line, "=")[1], ",");
                        for (int i = 0; i < values.size(); i++)
                        {
                            std::vector<std::string> col_values = split(values[i], ";");
                            tables[table_name]->add_column(col_values[0], col_values[1], col_values[2] == "true");
                        }
                    }
                }
            }
            file.close();
        }
    }
    else
    {
        std::string fileName = database_name + "/metadata.txt";
        std::ofstream file(fileName);
        if (file.is_open())
        {
            file << "database_name=" << database_name << std::endl;
            file << "tables=" << std::endl;
            file.close();
        }
    }
}