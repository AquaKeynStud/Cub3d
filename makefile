.PHONY : all clean fclean re libft lmlx norminette valgrind

.DELETE_ON_ERROR:

NAME := cub3d

# ╭━━━━━━━━━━━━══════════╕出 ❖ BASICS VARIABLES ❖ 力╒═══════════━━━━━━━━━━━━╮ #

CC				:=	cc

CFLAGS			:=	-Wall -Wextra -Werror -MMD

RM				:=	rm -rf

SHOW_MSG_CLEAN	=	true

MAKEFLAGS		+=	--no-print-directory

# ╰━━━━━━━━━━━━━━━━════════════════╛出 ❖ 力╘════════════════━━━━━━━━━━━━━━━━╯ #

# ╭━━━━━━━━━━━━══════════╕出 ❖ FILE TREE ❖ 力╒═══════════━━━━━━━━━━━━╮ #

# directories
D_INC	=	inc/
D_OBJ	=	.obj/
D_DEP	=	.dep/
D_SRC	=	srcs/
D_LIB	=	libs/
D_LFT	=	libft/
D_MLX	=	.minilibx/

D_GNL	=	$(D_LFT)gnl/
D_PTF	=	$(D_LFT)printf/

D_LFTS	=	$(D_LFT) $(D_GNL) $(D_PTF)

D_SRCS	=	$(D_SRC)

# file lists
LST_SRC	=	main.c

LST_SRCS	=	$(LST_SRC) $(LST_EXE) $(LST_TOK) $(LST_EXP) $(LST_BLT) $(LST_PAR) $(LST_SIG) $(LST_UTL)

INC			=	$(addprefix $(D_INC), $(LST_INC))

OBJ			=	$(addprefix $(D_OBJ), $(notdir $(LST_SRCS:.c=.o)))

DEPS		=	$(addprefix $(D_DEP), $(notdir $(LST_SRCS:.c=.d)))

LIBS		:=	-L$(D_LFT) -lft -lreadline -lncurses

INCS		:=	-I$(D_INC) -I$(D_LFT)

LIBFT		:=	$(D_LFT)libft.a

LFT_DEP		=	$(foreach dir, $(D_LFTS), $(wildcard $(dir)*.c $(dir)*.h $(dir)Makefile))

# ╭━━━━━━━━━━━━══════════╕出 ❖ RULES ❖ 力╒═══════════━━━━━━━━━━━━╮ #

all:	$(NAME)

$(NAME): $(LIBFT) lmlx $(OBJ) $(INC) makefile | $(D_OBJ) $(D_DEP) makefile
	@echo "\033[35mCompilation de $(NAME)...\033[0m"
	$(info ⏱️  Rebuild check: $?)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "\e[0;32m$(NAME) program created successfully ! 🧬\e[0m"

$(D_OBJ):
	@mkdir -p $@

$(D_DEP):
	@mkdir -p $@

vpath %.c $(D_SRCS)

$(D_OBJ)%.o: %.c $(INC) makefile | $(D_OBJ) $(D_DEP) makefile
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@ -MF $(D_DEP)$(notdir $*.d)
	@echo "\033[34m$(NAME): $@ created\033[0m"

$(LIBFT): $(LFT_DEP)
	@$(MAKE) -C $(D_LFT)
	@mv $(D_LFT)libft.a $(D_LIB)libft.a

lmlx:	$(D_MLX)
	@$(MAKE) -s -w -C $(D_MLX) 2>/dev/null
	@mv $(D_MLX)libmlx.a $(D_LIB)libmlx.a
	@echo "\e[0;36mArchive Minilibx créée avec succès ! 🌅\e[0m"

-include $(DEPS)

clean:
ifeq ($(SHOW_MSG_CLEAN), true)
	@echo "\e[0;36mAll $(NAME) objects have been removed 🧹\e[0m"
endif
	@$(RM) $(D_OBJ) $(D_DEP)
	@$(MAKE) -s -C $(D_LFT) clean
	@$(MAKE) -s -w -C $(D_MLX) clean

fclean:
	@$(MAKE) -s -C $(D_LFT) fclean
	@$(MAKE) -s SHOW_MSG_CLEAN=false clean
	@$(RM) $(D_LIB)/%.a
	@$(RM) $(NAME)
	@echo "\e[0;34m$(NAME) executable deleted ! 🧼\e[0m"

re:
	@$(MAKE) fclean
	@$(MAKE) all
	@echo "\e[0;32m$(NAME) program recreated successfully ! 🫡\e[0m"

norminette:
	norminette $(D_SRC) $(D_LFT) $(D_INC)

valgrind: supp_file
	@$(MAKE)
	@clear
	valgrind				\
		--leak-check=full		\
		--show-leak-kinds=all	\
		--track-origins=yes		\
		--track-fds=yes			\
		./$(NAME)
