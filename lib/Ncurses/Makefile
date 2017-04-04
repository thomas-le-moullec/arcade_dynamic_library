CC								= g++

RM								= rm -rf

NAME_LIB_NCURSES	= ../lib_arcade_ncurses.so

SRCS_LIB_NCURSES	=	./LNcurses.cpp

CPPFLAGS   				=  -I ../Includes/ -I ../../interfaces/ -I ../../scoreboard/ -I ../../Errors/

CXXFLAGS					=		-W -Werror -Wextra -std=c++11

OBJS_LIB_NCURSES	= $(SRCS_LIB_NCURSES:.cpp=.o)

all:        			$(NAME_LIB_NCURSES)

$(NAME_LIB_NCURSES):
	@echo "Compiling with Position Independent Code..."
	@$(CC) -c $(CXXFLAGS) $(CPPFLAGS) -fpic $(SRCS_LIB_NCURSES)
	@echo "Creating a shared library from an object file..."
	@$(CC) -shared -o $(NAME_LIB_NCURSES) *.o

clean:
	@echo "Cleaning object files ..."
	@$(RM) $(OBJS_LIB_NCURSES)
	@echo "Object files cleaned."

fclean: clean
	@echo "Cleaning files ..."
	@$(RM) $(NAME_LIB_NCURSES)
	@echo "Files cleaned."

re: fclean all
