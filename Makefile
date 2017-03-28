DETAILS     			=		yes

NAME							=		arcade

MAKE							=		make -C

CLEAN							=		make clean -C

FCLEAN						=		make fclean -C

CC								=		g++

RM								=		rm -rf

CPPFLAGS					=		-I ./interfaces/ -I ./core/

CXXFLAGS					=		-W -Wall -Wextra -std=c11 -lsfml-graphics -lsfml-window -lsfml-system -lncurses -ldl

SRCS							=		main.cpp				\
											core/Core.cpp		\

OBJS							=		$(SRCS:.cpp=.o)

all:							$(NAME)
									$(MAKE) lib/LNcurses
									$(MAKE) lib/LSfml
									$(MAKE) games/GSnake

$(NAME):
	@echo "Compiling with Position Independent Code..."
	@$(CC) -c $(CXXFLAGS) $(CPPFLAGS) -fpic $(SRCS_GAME)
	@echo "Creating a shared library from an object file..."
	@$(CC) -shared -o $(NAME_GAME) $(OBJS)


clean:
	@echo "Cleaning object files ..."
	@$(RM) $(OBJS)
	@echo "Object files cleaned."

fclean: clean
	@echo "Cleaning files ..."
	@$(RM) $(NAME)
	@echo "Files cleaned."

re: fclean all
