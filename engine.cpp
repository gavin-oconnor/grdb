#include <string>
#include <filesystem>
#include <iostream>

class Engine
{
public:
    Engine(std::string db_name)
    {
        create_if_not_exists(db_name);
    }

private:
    bool create_if_not_exists(std::string db_name)
    {
        if (std::filesystem::exists(db_name) && std::filesystem::is_directory(db_name))
        {
            return true;
        }
        if (std::filesystem::create_directory(db_name))
        {
            return true;
        }
        return false;
    }
};