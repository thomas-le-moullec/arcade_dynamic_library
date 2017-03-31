#include "ScoreBoard.hpp"

arcade::ScoreBoard::ScoreBoard(const std::string& filename)
{
  std::string	str;

  this->_filename = filename;
  this->_fileIn.open(this->_filename.c_str());
  if (this->_fileIn)
  {
    getline(this->_fileIn, str);
    while(!this->_fileIn.eof())
    {
      this->separateInfoScore(str);
      getline(this->_fileIn, str);
    }
  }
}

arcade::ScoreBoard::~ScoreBoard()
{
}

void											arcade::ScoreBoard::separateInfoScore(std::string str)
{
  std::string							nameGame;
  std::string							namePlayer;
  unsigned int						valueScore;
  int											pos;

  if ((pos = (int)str.find(":")) == -1)
    return ;
  nameGame = str.substr(0, pos);
  str = str.substr(pos + 1, str.length());
  if ((pos = (int)str.find(":")) == -1)
    return ;
  namePlayer = str.substr(0, pos);
  valueScore = (unsigned int)atoi(str.substr(pos + 1, str.length()).c_str());
  this->addScore(nameGame, namePlayer, valueScore);
}

void											arcade::ScoreBoard::addActualScore(std::string game, std::string name, unsigned int value)
{
  unsigned int						i = 0;

  if (this->_board.size() == 0)
    this->addScore("", "", 0);
  while (i < this->_board.size() - 1)
    i++;
  this->_board[i].nameGame = game;
  this->_board[i].namePlayer = name;
  this->_board[i].valueScore = value;
}

void											arcade::ScoreBoard::addScore(std::string game, std::string name, unsigned int value)
{
  arcade::Score						score;

  score.nameGame = game;
  score.namePlayer = name;
  score.valueScore = value;
  this->_board.insert(this->_board.end(), score);
}

void											arcade::ScoreBoard::writeScore()
{
  this->_fileOut.open(this->_filename.c_str());
  for (unsigned int i = 0; i < this->_board.size(); i++)
  {
    this->_fileOut << this->_board[i].nameGame << ":";
    this->_fileOut << this->_board[i].namePlayer << ":";
    this->_fileOut << this->_board[i].valueScore;
    this->_fileOut << std::endl;
  }
}

void												arcade::ScoreBoard::sort()
{
  std::cout << this->_new_score.size() << std::endl;
  for (int i = 0; i < (int)(this->_new_score.size() - 1); i++)
  {
    if (this->_new_score[i].valueScore < this->_new_score[i + 1].valueScore)
      {
        this->_new_score.insert(this->_new_score.begin(), this->_new_score[i + 1]);
        this->_new_score.erase(this->_new_score.begin() + i + 1);
        i = 0;
      }
  }
}

std::vector<arcade::Score>	&arcade::ScoreBoard::getBestScores(const std::string& game, int size)
{
  unsigned int												j = 0;

  this->_new_score.clear();
  for (unsigned int i = 0; i < this->_board.size(); i++)
    if (this->_board[i].nameGame == game)
    {
      while (j < this->_new_score.size() && this->_board[i].valueScore < this->_new_score[j].valueScore)
        j++;
      this->_new_score.insert(this->_new_score.begin() + j, this->_board[i]);
      j = 0;
    }
  while (size < (int)this->_new_score.size())
    this->_new_score.erase(this->_new_score.end());
  while (j < this->_board.size())
    j++;
  if (j > 0)
    this->_new_score.insert(this->_new_score.end(), this->_board[j - 1]);
  return this->_new_score;
}
