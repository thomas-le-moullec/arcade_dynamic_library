CC								= g++

RM								= rm -rf

NAME_LIB_OPENGL		= ../lib_arcade_opengl.so

SRCS_LIB_OPENGL		=	./OpenGL.cpp \
										../../Errors/Errors.cpp		\

CPPFLAGS   				=  -I ../Includes/ -I ../../interfaces/ -I ../../scoreboard/ -I ../../Errors/

CXXFLAGS					=		-W -Werror -Wextra -std=c++11

OBJS_LIB_OPENGL		= $(SRCS_LIB_OPENGL:.cpp=.o)

all:        			$(NAME_LIB_OPENGL)

$(NAME_LIB_OPENGL):
	@echo "Compiling with Position Independent Code..."
	@$(CC) -c $(CXXFLAGS) $(CPPFLAGS) -fpic $(SRCS_LIB_OPENGL)
	@echo "Creating a shared library from an object file..."
	@$(CC) -shared -o $(NAME_LIB_OPENGL) *.o -lGL -lSDL -lSDL_ttf -lGLU

clean:
	@echo "Cleaning object files ..."
	@$(RM) $(OBJS_LIB_OPENGL)
	@echo "Object files cleaned."

fclean: clean
	@echo "Cleaning files ..."
	@$(RM) $(NAME_LIB_OPENGL)
	@echo "Files cleaned."

re: fclean all
