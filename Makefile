DETAILS     = yes

CC					= g++

RM					= rm -rf

NAME_GAME		= ./games/lib_arcade_snake.so

NAME_LIB		= ./lib/lib_arcade_ncurses.so

SRCS_GAME		=	./games/Snake/GSnake.cpp

SRCS_LIB		=	./lib/Ncurses/LNcurses.cpp

CPPFLAGS   	=   -I ./games/Includes/ -I ./interfaces -I ./lib/Includes

CXXFLAGS		=		-W -Wall -Werror -Wextra -std=c++11

OBJS_GAME		= $(SRCS_GAME:.cpp=.o)

OBJS_LIB		= $(SRCS_LIB:.cpp=.o)

all:        $(NAME_GAME) $(NAME_LIB)

$(NAME_GAME):

ifeq ($(DETAILS),yes)
		$(CC) -c $(CXXFLAGS) $(CPPFLAGS) -fpic $(SRCS_GAME)
		$(CC) -shared -o $(NAME_GAME) *.o

else
    	@echo "Compiling with Position Independent Code..."
        @$(CC) -c $(CXXFLAGS) $(CPPFLAGS) -fpic $(SRCS_GAME)
			@echo "Creating a shared library from an object file..."
        @$(CC) -shared -o $(NAME_GAME) *.o

endif

$(NAME_LIB):

ifeq ($(DETAILS),yes)
		$(CC) -c $(CXXFLAGS) $(CPPFLAGS) -fpic $(SRCS_LIB)
		$(CC) -shared -o $(NAME_LIB) *.o

else
    	@echo "Compiling with Position Independent Code..."
        @$(CC) -c $(CXXFLAGS) $(CPPFLAGS) -fpic $(SRCS_LIB)
			@echo "Creating a shared library from an object file..."
        @$(CC) -shared -o $(NAME_LIB) *.o

endif

clean:
	@echo "Cleaning object files ..."
	@$(RM) *.o
	@echo "Object files cleaned."

fclean: clean
	@echo "Cleaning files ..."
	@$(RM) $(NAME_GAME) $(NAME_LIB)
	@echo "Files cleaned."

re: fclean all