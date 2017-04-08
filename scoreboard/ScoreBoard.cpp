#include "ScoreBoard.hpp"

const std::string      arcade::ScoreBoard::SB_FILENAME = "score.txt";

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
  this->writeScore();
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
  this->PostScore(nameGame, namePlayer, valueScore);
}

void											arcade::ScoreBoard::PostScore(const std::string &game, const std::string &name, unsigned int value)
{
  arcade::IScore					*score = new arcade::Score(game, name, value);

  this->_board.insert(this->_board.end(), score);
}

void											arcade::ScoreBoard::PostScore(IScore *score)
{
  this->_board.insert(this->_board.end(), score);
}

void											arcade::ScoreBoard::writeScore()
{
  this->_fileOut.open(this->_filename.c_str());
  for (unsigned int i = 0; i < this->_board.size(); i++)
  {
    this->_fileOut << this->_board[i]->getGame() << ":";
    this->_fileOut << this->_board[i]->getName() << ":";
    this->_fileOut << this->_board[i]->getScore();
    this->_fileOut << std::endl;
  }
}

std::vector<arcade::IScore *>	&arcade::ScoreBoard::GetBestScores(const std::string& game, size_t size)
{
  unsigned int												j = 0;

  this->_new_score.clear();
  for (unsigned int i = 0; i < this->_board.size(); i++)
    if (this->_board[i]->getGame() == game)
    {
      while (j < this->_new_score.size() && this->_board[i]->getScore() < this->_new_score[j]->getScore())
        j++;
      this->_new_score.insert(this->_new_score.begin() + j, this->_board[i]);
      j = 0;
    }
  while (size < (size_t)this->_new_score.size())
    this->_new_score.erase(this->_new_score.end() - 1);
  return this->_new_score;
}

void								arcade::ScoreBoard::GetFileBestScores()
{
}
