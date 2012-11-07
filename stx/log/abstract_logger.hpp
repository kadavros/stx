#ifndef STX_LOG_ABSTRACT_LOGGER_HPP
#define STX_LOG_ABSTRACT_LOGGER_HPP

#include <iostream>
#include <string>

namespace stx {

template<class Formatter>
class abstract_logger
{
public:
    
    typedef abstract_logger<Formatter> this_type;
    
    virtual Formatter log(int message_level) = 0;
    
    virtual Formatter trace() = 0;
    
    virtual Formatter debug() = 0;
    
    virtual Formatter info() = 0;
    
    virtual Formatter warn() = 0;
    
    virtual Formatter error() = 0;
    
    virtual Formatter fatal() = 0;
    
    virtual int level() const = 0;
    
    virtual this_type& set_level(int new_level) = 0;
    
    virtual std::string delimiter() const = 0;
    
    virtual this_type& set_delimiter(const std::string& s) = 0;
    
    virtual const char* level_to_string(int message_level) const = 0;
    
    virtual bool enabled(int message_level) const = 0;
    
    virtual void print_delimiter() = 0;
    
    virtual std::ostream& stream() = 0;
    
    virtual void start_formatting(int message_level) = 0;
    
    virtual void finish_formatting(Formatter& fmt) = 0;
    
    virtual ~abstract_logger()
    {
    }
};

} // namespace stx

#endif // STX_LOG_ABSTRACT_LOGGER_HPP
