#-------------------------------------------

BLACK       =   "\033[0;30m"
GRAY        =   "\033[1;30m"
RED         =   "\033[1;31m"
GREEN       =   "\033[0;32m"
YELLOW      =   "\033[1;33m"
PURPLE      =   "\033[0;35m"
CYAN        =   "\033[1;36m"
WHITE       =   "\033[1;37m"
EOC         =   "\033[0;0m"
LINE_CLEAR  =   "\x1b[1A\x1b[M"

#-------------------------------------------

NAME = test_RT
CC = cc
CFLAGS = -I./include -Wall -Wextra -Werror
SRCS = ./src/main.c \
		./src/print/print.c \
		./src/scene/canvas.c \
		./src/scene/scene.c \
		./src/trace/ray/ray.c \
		./src/utils/vec3_utils.c \
		./src/trace/hit/hit_objs.c \
		./src/trace/hit/hit.c \
		./src/scene/object_create.c \
		./src/trace/hit/normal.c \
		./src/utils/object_utils.c \
		./src/trace/ray/phong_lighting.c \

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $^
	@echo $(GREEN)"\n==========================================================\n"$(EOC)
	@echo $(YELLOW)"                    test_RT is ready"$(EOC)
	@echo $(GREEN)"\n==========================================================\n"$(EOC)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all bonus clean fclean re
