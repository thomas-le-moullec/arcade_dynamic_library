CC								= g++

RM								= rm -rf

NAME_LIB_SFML			= 	../lib_arcade_sfml.so

SRCS_LIB_SFML			=	./LSfml.cpp

CPPFLAGS   				=  -I ../Includes/ -I ../../interfaces/

CXXFLAGS					=		-W -Werror -Wextra -std=c++11

OBJS_LIB_SFML			= $(SRCS_LIB_SFML:.cpp=.o)

all:        			$(NAME_LIB_SFML)

$(NAME_LIB_SFML):
	@echo "Compiling with Position Independent Code..."
	@$(CC) -c $(CXXFLAGS) $(CPPFLAGS) -fpic $(SRCS_LIB_SFML)
	@echo "Creating a shared library from an object file..."
	@$(CC) -shared -o $(NAME_LIB_SFML) *.o

clean:
	@echo "Cleaning object files ..."
	@$(RM) $(OBJS_LIB_SFML)
	@echo "Object files cleaned."

fclean: clean
	@echo "Cleaning files ..."
	@$(RM) $(NAME_LIB_SFML)
	@echo "Files cleaned."

re: fclean all
