#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>

#define SB_FILENAME "score.txt"

namespace arcade
{
  struct Score
  {
    std::string		nameGame;
    std::string		namePlayer;
    unsigned int	valueScore;
  };

  class ScoreBoard
  {
  public:
    ScoreBoard(const std::string& filename = SB_FILENAME);
    ~ScoreBoard();
    void												addScore(std::string, std::string, unsigned int);
    void												writeScore();
    std::vector<arcade::Score>	&getBestScores(const std::string&, int size = 10);
    void												addActualScore(std::string, std::string, unsigned int);
  private:
    std::vector<Score>					_board;
    std::vector<arcade::Score> 	_new_score;
    std::fstream								_fileIn;
    std::ofstream								_fileOut;
    std::string									_filename;

    void												sort();
    void												separateInfoScore(std::string);
  };
};

#endif
