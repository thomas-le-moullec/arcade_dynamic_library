#include "Errors.hpp"

RunTimeErrorGame::RunTimeErrorGame(std::string const &message) : std::runtime_error::runtime_error(message), _message(message)
{
}

RunTimeErrorGame::RunTimeErrorGame(const char *message) : std::runtime_error::runtime_error(message), _message(message)
{
}

RunTimeErrorCore::RunTimeErrorCore(std::string const &message) : std::runtime_error::runtime_error(message), _message(message)
{
}

RunTimeErrorCore::RunTimeErrorCore(const char *message) : std::runtime_error::runtime_error(message), _message(message)
{
}

RunTimeErrorGraphic::RunTimeErrorGraphic(std::string const &message) : std::runtime_error::runtime_error(message), _message(message)
{
}

RunTimeErrorGraphic::RunTimeErrorGraphic(const char *message) : std::runtime_error::runtime_error(message), _message(message)
{
}
