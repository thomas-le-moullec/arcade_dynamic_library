DETAILS     			= yes

CC								= g++

RM								= rm -rf

NAME_GAME					= ./games/lib_arcade_snake.so

NAME_LIB_SFML			= ./lib/lib_arcade_sfml.so

NAME_LIB_NCURSES	= ./lib/lib_arcade_ncurses.so

SRCS_GAME					=	./games/Snake/GSnake.cpp

SRCS_LIB_SFML			=	./lib/SFml/LSfml.cpp

SRCS_LIB_NCURSES	=	./lib/Ncurses/LNcurses.cpp

CPPFLAGS   				=  -I lib/Includes/ -I games/Includes/ -I core/ -I interfaces/

CXXFLAGS					=		-W -Werror -Wextra -std=c++11

OBJS_GAME					= $(SRCS_GAME:.cpp=.o)

OBJS_LIB_SFML			= $(SRCS_LIB_SFML:.cpp=.o)

OBJS_LIB_NCURSES	= $(SRCS_LIB_NCURSES:.cpp=.o)

all:        			$(NAME_GAME) #$(NAME_LIB_SFML) $(NAME_LIB_NCURSES)

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

$(NAME_LIB_SFML):
ifeq ($(DETAILS),yes)
		$(CC) -c $(CXXFLAGS) $(CPPFLAGS) -fpic $(SRCS_LIB_SFML)
		$(CC) -shared -o $(NAME_LIB_SFML) *.o
else
    	@echo "Compiling with Position Independent Code..."
        @$(CC) -c $(CXXFLAGS) $(CPPFLAGS) -fpic $(SRCS_LIB_SFML)
			@echo "Creating a shared library from an object file..."
        @$(CC) -shared -o $(NAME_LIB_SFML) *.o
endif

$(NAME_LIB_NCURSES):
ifeq ($(DETAILS),yes)
		$(CC) -c $(CXXFLAGS) $(CPPFLAGS) -fpic $(SRCS_LIB_NCURSES)
		$(CC) -shared -o $(NAME_LIB_NCURSES) *.o
else
    	@echo "Compiling with Position Independent Code..."
        @$(CC) -c $(CXXFLAGS) $(CPPFLAGS) -fpic $(SRCS_LIB_NCURSES)
			@echo "Creating a shared library from an object file..."
        @$(CC) -shared -o $(NAME_LIB_NCURSES) *.o
endif

clean:
	@echo "Cleaning object files ..."
	@$(RM) *.o
	@echo "Object files cleaned."

fclean: clean
	@echo "Cleaning files ..."
	@$(RM) $(NAME_GAME) $(NAME_LIB_SFML) $(NAME_LIB_NCURSES)
	@echo "Files cleaned."

re: fclean all
