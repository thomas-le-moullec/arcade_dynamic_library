#include "Score.hpp"

arcade::Score::Score(const std::string &nameGame, const std::string &namePlayer, unsigned int valueScore)
{
  this->_nameGame = nameGame;
  this->_namePlayer = namePlayer;
  this->_valueScore = valueScore;
}

const std::string&	arcade::Score::getGame() const
{
  return this->_nameGame;
}

const std::string&	arcade::Score::getName() const
{
  return this->_namePlayer;
}

unsigned int				arcade::Score::getScore() const
{
  return this->_valueScore;
}

void	     					arcade::Score::setGame(const std::string &nameGame)
{
  this->_nameGame = nameGame;
}

void								arcade::Score::setName(const std::string &namePlayer)
{
  this->_namePlayer = namePlayer;
}

void								arcade::Score::setScore(unsigned int valueScore)
{
  this->_valueScore = valueScore;
}
