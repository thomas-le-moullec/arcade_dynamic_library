#ifndef   ERRORS_HPP_
# define  ERRORS_HPP_

#include <iostream>
#include <stdexcept>

class RunTimeErrorGame : public std::runtime_error
{
  private:
    std::string     _message;
  public:
    RunTimeErrorGame(std::string const &message = "Error Game");
    RunTimeErrorGame(const char * message= "Error Game");
    ~RunTimeErrorGame() throw() {};
    const char* what() const throw() { return _message.c_str(); };
};

class RunTimeErrorGraphic : public std::runtime_error
{
  private:
    std::string     _message;
  public:
    RunTimeErrorGraphic(std::string const &message = "Error Graphic");
    RunTimeErrorGraphic(const char * message= "Error Graphic");
    ~RunTimeErrorGraphic() throw() {};
    const char* what() const throw() { return _message.c_str(); };
};

class RunTimeErrorCore : public std::runtime_error
{
  private:
    std::string     _message;
  public:
    RunTimeErrorCore(std::string const &message = "Error Core");
    RunTimeErrorCore(const char * message= "Error Core");
    ~RunTimeErrorCore() throw() {};
    const char* what() const throw() { return _message.c_str(); };
};

# endif
