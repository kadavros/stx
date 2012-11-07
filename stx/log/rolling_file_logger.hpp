#ifndef STX_LOG_ROLLING_FILE_LOGGER_HPP
#define STX_LOG_ROLLING_FILE_LOGGER_HPP

#include <stx/log/basic_logger.hpp>
#include <fstream>
#include <sstream>
#include <cstddef>
#include <limits>

namespace stx {

class rolling_file_logger: public basic_logger
{
public:
    
    rolling_file_logger(
        const std::string& delimiter = "",
        int log_level = log_level_all):
            basic_logger(delimiter, log_level)
    {
    }
    
    rolling_file_logger(
        const std::string& file_name,
        std::size_t max_file_size = std::numeric_limits<int>::max(),
        const std::string& delimiter = "",
        int log_level = log_level_all)
    {
        create(file_name, max_file_size, delimiter, log_level);
    }
    
    void create(
        const std::string& file_name,
        std::size_t max_file_size = std::numeric_limits<int>::max(),
        const std::string& delimiter = "",
        int log_level = log_level_all)
    {
        file_.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
        file_.open(file_name.c_str(), std::ios_base::out | std::ios_base::binary);
        level_ = log_level;
        delimiter_ = delimiter;
        max_file_size_ = max_file_size;
    }
    
    virtual std::ostream& stream()
    {
        return ss_;
    }
    
    void start_formatting(int message_level)
    {
        ss_.str("");
        basic_logger::start_formatting(message_level);
    }
    
    void finish_formatting(log_formatter& fmt)
    {
        if (fmt.enabled()) {
            stream() << std::endl;
            std::size_t max_size = max_file_size(),
                current_size = current_file_size(),
                remaining_size = max_size - current_size,
                message_size = stream_str_size(ss_);
            if (message_size <= remaining_size) {
                file_ << ss_.str();
            } else if (message_size > max_size) {
                file_.seekp(0, std::ios_base::beg);
                file_.write(ss_.str().c_str(), max_size);
            } else {
                std::string buf_str = ss_.str();
                file_.write(buf_str.c_str(), remaining_size);
                file_.seekp(0, std::ios_base::beg);
                file_.write(buf_str.c_str() + remaining_size, message_size - remaining_size);
            }
            //file_.flush();
        }
    }
    
    std::size_t max_file_size() const
    {
        return max_file_size_;
    }
    
    rolling_file_logger& set_max_file_size(std::size_t size)
    {
        max_file_size_ = size;
        return *this;
    }
    
    std::size_t current_file_size()
    {
        std::streampos p = file_.tellp();
        if (p == std::streampos(-1)) {
            file_.seekp(0, std::ios_base::beg);
            p = std::streampos(0);
        }
        return std::size_t(p);
    }
    
protected:
    
    std::size_t stream_str_size(std::ostringstream& ss)
    {
        return ss.str().size();
    }
    
    std::ofstream file_;
    std::size_t max_file_size_;
    std::ostringstream ss_;
};

} // namespace stx

#endif // STX_LOG_ROLLING_FILE_LOGGER_HPP
