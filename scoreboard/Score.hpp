#ifndef SCORE_HPP_
#define SCORE_HPP_

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include "IScore.hpp"

namespace arcade
{
  class	Score : public IScore
  {
  public:
    Score(const std::string &, const std::string &, unsigned int);
    virtual ~Score() {};
    virtual const std::string&	getGame() const;
    virtual const std::string&	getName() const;
    virtual unsigned int				getScore() const;
    virtual void	     					setGame(const std::string&);
    virtual void								setName(const std::string&);
    virtual void								setScore(unsigned int);

  private:
    std::string		_nameGame;
    std::string		_namePlayer;
    unsigned int	_valueScore;

    static const std::string    SB_FILENAME;
  };
};

#endif
