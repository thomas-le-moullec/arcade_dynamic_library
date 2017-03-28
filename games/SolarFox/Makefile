DETAILS     = yes

CC					= g++

RM					= rm -rf

NAME				= ../lib_arcade_solarfox.so

SRCS				=	GSolarFox.cpp

CPPFLAGS   	=   -I ./../Includes/ -I ./../../interfaces

CXXFLAGS	=		-W -Wall -Werror -Wextra -std=c++11

OBJS				= $(SRCS:.cpp=.o)

all:        $(NAME)

$(NAME):

ifeq ($(DETAILS),yes)
		$(CC) -c $(CXXFLAGS) $(CPPFLAGS) -fpic $(SRCS)
		$(CC) -shared -o $(NAME) *.o

else
    	@echo "Compiling with Position Independent Code..."
        @$(CC) -c $(CXXFLAGS) $(CPPFLAGS) -fpic $(SRCS)
			@echo "Creating a shared library from an object file..."
        @$(CC) -shared -o $(NAME) *.o

endif

clean:
	@echo "Cleaning object files ..."
	@$(RM) *.o
	@echo "Object files cleaned."

fclean: clean
	@echo "Cleaning files ..."
	@$(RM) $(NAME)
	@echo "Files cleaned."

re: fclean all
