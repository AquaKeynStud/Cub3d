.PHONY : all clean fclean re libft norminette

.DELETE_ON_ERROR:

NAME := cub3d

# ╭━━━━━━━━━━━━══════════╕出 ❖ BASICS VARIABLES ❖ 力╒═══════════━━━━━━━━━━━━╮ #

CC				:=	cc

CFLAGS			:=	-Wall -Wextra -Werror -MMD

RM				:=	rm -rf

MKDIR			:=	mkdir -p

SHOW_MSG_CLEAN	=	true

MAKEFLAGS		+=	--no-print-directory

# ╰━━━━━━━━━━━━━━━━════════════════╛出 ❖ 力╘════════════════━━━━━━━━━━━━━━━━╯ #

# ╭━━━━━━━━━━━━══════════╕出 ❖ FILE TREE ❖ 力╒═══════════━━━━━━━━━━━━╮ #

# directories
D_INC	=	inc/
D_BLD	=	.build/
D_SRC	=	srcs/
D_LFT	=	libft/
D_MLX	=	.minilibx/

D_OBJ	=	$(D_BLD)bin/
D_DEP	=	$(D_BLD)dep/
D_LIB	=	$(D_BLD)libs/

D_PAR	=	$(D_SRC)parsing/

D_BLDS	=	$(D_OBJ) $(D_DEP) $(D_LIB)

# file lists
LST_SRC	=	main.c		\
			logs.c

LST_PAR	=	images.c	\
			file_manager.c

LST_INC	=	cub.h

LST_SRCS	=	$(LST_SRC)

INC			=	$(addprefix $(D_INC), $(LST_INC))

OBJ			=	$(addprefix $(D_OBJ), $(notdir $(LST_SRCS:.c=.o)))

DEPS		=	$(addprefix $(D_DEP), $(notdir $(LST_SRCS:.c=.d)))

LIBS		:=	-L$(D_LFT) -lft -lreadline -lncurses

INCS		:=	-I$(D_INC) -I$(D_LFT)inc/ -I$(D_MLX)

LIBS		:=	-L$(D_LIB) -lft -lmlx -lX11 -lXext

LIBFT		:=	$(D_LIB)libft.a

LIBMLX		:=	$(D_LIB)libmlx.a

LFT_DEP		=	$(foreach dir, $(D_LFT), $(wildcard $(dir)*.c $(dir)*.h $(dir)Makefile))
MLX_DEP		=	$(foreach dir, $(D_MLX), $(wildcard $(dir)*.c $(dir)*.h $(dir)Makefile))

START_TIME	:=	$(shell date +%s%3N)

# ╭━━━━━━━━━━━━══════════╕出 ❖ RULES ❖ 力╒═══════════━━━━━━━━━━━━╮ #

all:	$(NAME)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJ) $(INC) makefile | $(D_BLDS) makefile
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@END_TIME=$$(date +%s%3N);						\
	ELAPSED=$$(expr $$END_TIME - $(START_TIME));	\
	ELAPSED_SEC=$$(echo "scale=2; $$ELAPSED / 1000" | bc);	\
	echo "\n\e[1;31m🍣 $(NAME) program created successfully in $${ELAPSED_SEC}ms ! 🍣\e[0m"

$(D_BLD):
	@$(MKDIR) $@

$(D_BLDS): | $(D_BLD)
	@$(MKDIR) $@

vpath %.c $(D_SRC)

check_newer:
	@if [ ! -f $(NAME) ] || [ makefile -nt $(NAME) ] || find $(D_SRC) -name '*.c' -newer $(NAME) | grep -q .; then \
		echo "\e[1m🍚 Starting $(NAME) compilation : 🍚\e[0m"; \
	else \
		echo "make: Nothing to be done for 'all'."; \
	fi

$(D_OBJ)%.o: %.c $(INC) makefile | $(D_BLDS) makefile check_newer
	@$(CC) $(CFLAGS) -g3 $(INCS) -c $< -o $@ -MF $(D_DEP)$(notdir $*.d)
	@echo "\e[1;38;5;210m   🦐 $(NAME): $@ created 🦐\e[0m"

$(LIBFT): $(LFT_DEP) | $(D_BLDS) makefile
	@$(MAKE) -C $(D_LFT)
	@mv $(D_LFT)libft.a $(D_LIB)libft.a

$(LIBMLX): $(LFT_DEP) | $(D_BLDS) makefile
	@echo "\e[1;38;5;94m\n🌱 Starting minilibx compilation... 🌱\e[0m"
	@$(MAKE) -s -C $(D_MLX) 2> /dev/null
	@mv $(D_MLX)libmlx.a $(D_LIB)libmlx.a
	@echo "\e[1;38;5;42m🌳 Minilibx compilated successfully ! 🌳\e[0m\n"

-include $(DEPS)

clean:
	@$(MAKE) -s -w -C $(D_MLX) clean
	@$(MAKE) -s -C $(D_LFT) clean
	@$(RM) $(D_BLD)
ifeq ($(SHOW_MSG_CLEAN), true)
	@echo "\e[1;36m🎋 All $(NAME) build files have been deleted 🎋\e[0m"
endif

fclean:
	@$(MAKE) -s SHOW_MSG_CLEAN=false clean
	@$(MAKE) -s -C $(D_LFT) fclean
	@$(RM) $(D_LIB)/%.a
	@$(RM) $(NAME)
	@echo "\e[1;34m⛲️ All items relative to $(NAME) deleted, repertory cleaned ⛲️\e[0m"

re:
	@$(MAKE) fclean
	@$(MAKE) all
	@echo "\e[0;32m$(NAME) program recreated successfully ! 🫡\e[0m"

norminette:
	norminette $(D_SRC) $(D_LFT) $(D_INC)

valgrind:
	@$(MAKE)
	@clear
	valgrind										\
		--leak-check=full								\
		--show-leak-kinds=all							\
		--track-origins=yes 							\
		--track-fds=yes									\
		./$(NAME) $(word 2,$(MAKECMDGOALS))