#ifndef SCOREBOARD_HPP_
#define SCOREBOARD_HPP_

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include "Score.hpp"

namespace arcade
{
  class ScoreBoard : public IScoreBoard
  {
  public:
    ScoreBoard(const std::string& filename = SB_FILENAME);
    virtual ~ScoreBoard();
    virtual void										PostScore(const std::string&, const std::string&, unsigned int);
    virtual void										PostScore(IScore *);
    virtual std::vector<IScore *>   &GetBestScores(const std::string&, size_t);
    virtual void										GetFileBestScores();

  private:
    std::vector<IScore *>					_board;
    std::vector<arcade::IScore *>	_new_score;
    std::fstream									_fileIn;
    std::ofstream									_fileOut;
    std::string										_filename;

    void												  separateInfoScore(std::string);
    void												  writeScore();

    static const std::string      SB_FILENAME;
  };
};

#endif
