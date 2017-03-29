NAME							=		arcade

MAKE							=		make -C

CLEAN							=		make clean -C

FCLEAN						=		make fclean -C

CC								=		g++

RM								=		rm -rf

CPPFLAGS					=		-I ./interfaces/ -I ./core/

CXXFLAGS					=		-W -Wall -Wextra -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system -lncurses -ldl

SRCS							=		main.cpp				\
											core/Core.cpp		\

OBJS							=		$(SRCS:.cpp=.o)

all:						  $(NAME)
									$(MAKE) lib/Ncurses
									$(MAKE) lib/SFml
									$(MAKE) games/Snake
									$(MAKE) games/SolarFox

arcade:						$(NAME)

libs:
									$(MAKE) lib/Ncurses
									$(MAKE) lib/SFml
									$(MAKE) games/Snake
									$(MAKE) games/SolarFox

$(NAME): 					$(OBJS)
				 					@echo "Compiling with Position Independent Code..."
				 					@$(CC) -o  $(NAME) $(CXXFLAGS) $(CPPFLAGS) $(OBJS)

clean:
									@echo "Cleaning object files ..."
									$(RM) $(OBJS)
									@$(CLEAN) lib/Ncurses
									@$(CLEAN) lib/SFml
									@$(CLEAN) games/Snake
									@$(CLEAN) games/SolarFox
									@echo "Object files cleaned."

fclean: 					clean
									@echo "Cleaning files ..."
									$(RM) $(NAME)
									@$(FCLEAN) lib/Ncurses
									@$(FCLEAN) lib/SFml
									@$(FCLEAN) games/Snake
									@$(FCLEAN) games/SolarFox
									@echo "Files cleaned."

re: 							fclean all
