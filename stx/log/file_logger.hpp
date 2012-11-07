#ifndef STX_LOG_FILE_LOGGER_HPP
#define STX_LOG_FILE_LOGGER_HPP

#include <stx/log/basic_logger.hpp>
#include <fstream>

namespace stx {

class file_logger: public basic_logger
{
public:
    
    file_logger(
        const std::string& delimiter = "",
        int log_level = log_level_all):
            basic_logger(delimiter, log_level)
    {
    }
    
    file_logger(
        const std::string& file_name,
        const std::string& delimiter = "",
        int log_level = log_level_all)
    {
        create(file_name, delimiter, log_level);
    }
    
    void create(
        const std::string& file_name,
        const std::string& delimiter = "",
        int log_level = log_level_all)
    {
        file_.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
        file_.open(file_name.c_str(), std::ios_base::out | std::ios_base::binary);
        level_ = log_level;
        delimiter_ = delimiter;
    }
    
    virtual std::ostream& stream()
    {
        return file_;
    }
    
protected:
    
    std::ofstream file_;
};

} // namespace stx

#endif // STX_LOG_FILE_LOGGER_HPP
