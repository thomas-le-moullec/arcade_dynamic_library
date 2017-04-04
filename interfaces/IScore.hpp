#ifndef ISCOREBOARD_HPP
#define ISCOREBOARD_HPP

namespace arcade
{
  class IScore
  {
  public:
    virtual ~IScore() {};
    virtual const std::string&	getGame() const = 0;
    virtual const std::string&	getName() const = 0;
    virtual unsigned int				getScore() const = 0;
    virtual void	     					setGame(const std::string&) = 0;
    virtual void								setName(const std::string&) = 0;
    virtual void								setScore(unsigned int) = 0;
  };

  class IScoreBoard
  {
  public:
    virtual ~IScoreBoard() {};
    virtual void										PostScore(const std::string&, const std::string&, unsigned int) = 0;
    virtual void										PostScore(IScore *) = 0;
    virtual std::vector<IScore *>&	GetBestScores(const std::string&, size_t) = 0;
    virtual void										GetFileBestScores() = 0;
  };
}

#endif
