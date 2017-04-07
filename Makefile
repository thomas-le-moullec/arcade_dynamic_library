NAME							=		arcade

MAKE							=		make -C

CLEAN							=		make clean -C

FCLEAN						=		make fclean -C

CC								=		g++

RM								=		rm -rf

CPPFLAGS					=		-I ./interfaces/ -I ./core/ -I ./scoreboard/ -I ./Errors/

CXXFLAGS					=		-W -Wall -Wextra -std=c++11 -ldl

SRCS							=		main.cpp										\
											core/Core.cpp								\
											scoreboard/ScoreBoard.cpp		\
											Errors/Errors.cpp						\
											scoreboard/Score.cpp				\

OBJS							=		$(SRCS:.cpp=.o)

all:
									$(MAKE) games/Snake
									$(MAKE) games/SolarFox
									$(MAKE) games/Centiped

full:
									$(NAME)
									$(MAKE) lib/Ncurses
									$(MAKE) lib/OpenGL
									$(MAKE) lib/SFml
									$(MAKE) games/Snake
									$(MAKE) games/SolarFox
									$(MAKE) games/Centiped

arcade:						$(NAME)

libs:
									$(MAKE) lib/Ncurses
									$(MAKE) lib/OpenGL
									$(MAKE) lib/SFml
									$(MAKE) games/Snake
									$(MAKE) games/SolarFox
									$(MAKE) games/Centiped

$(NAME): 					$(OBJS)
				 					@echo "Compiling with Position Independent Code..."
				 					@$(CC) -o  $(NAME) $(CXXFLAGS) $(CPPFLAGS) $(OBJS)

clean:
									@echo "Cleaning object files ..."
									$(RM) $(OBJS)
									@$(CLEAN) lib/Ncurses
									@$(CLEAN) lib/OpenGL
									@$(CLEAN) lib/SFml
									@$(CLEAN) games/Snake
									@$(CLEAN) games/SolarFox
									@$(CLEAN) games/Centiped
									@echo "Object files cleaned."

fclean: 					clean
									@echo "Cleaning files ..."
									$(RM) $(NAME)
									@$(FCLEAN) lib/Ncurses
									@$(FCLEAN) lib/OpenGL
									@$(FCLEAN) lib/SFml
									@$(FCLEAN) games/Snake
									@$(FCLEAN) games/SolarFox
									@$(FCLEAN) games/Centiped
									@echo "Files cleaned."

re: 							fclean all
