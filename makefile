.PHONY : all clean fclean re libft norminette supp valgrind rmv rmsupp

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

D_UIS	=	$(D_SRC)ui/
D_INT	=	$(D_SRC)init/
D_LOG	=	$(D_SRC)logs/
D_PAR	=	$(D_SRC)config/

D_BLDS	=	$(D_OBJ) $(D_DEP) $(D_LIB)

D_SRCS	=	$(D_SRC) $(D_INT) $(D_UIS) $(D_LOG) $(D_INT) $(D_PAR)

# file lists
LST_SRC	=	main.c

LST_INT	=	file_init.c		\
			data_store.c

LST_UIS	=	window.c

LST_LOG	=	logs.c		\
			errors.c	\
			data_logs.c

LST_PAR	=	bfs.c		\
			parser.c

LST_INC	=	cub.h	\
			data.h

LST_SRCS	=	$(LST_SRC) $(LST_INT) $(LST_UIS) $(LST_LOG) $(LST_PAR)

INC			=	$(addprefix $(D_INC), $(LST_INC))

OBJ			=	$(addprefix $(D_OBJ), $(notdir $(LST_SRCS:.c=.o)))

DEPS		=	$(addprefix $(D_DEP), $(notdir $(LST_SRCS:.c=.d)))

LIBS		:=	-L$(D_LFT) -lft -lreadline -lncurses

INCS		:=	-I$(D_INC) -I$(D_LFT)inc/ -I$(D_MLX)

LIBS		:=	-L$(D_LIB) -lft -lmlx -lX11 -lXext

LIBFT		:=	$(D_LIB)libft.a

LIBMLX		:=	$(D_LIB)libmlx.a

LFT_DEP		=	$(foreach dir, $(D_LFT), $(wildcard $(dir)*.c $(dir)*.h $(dir)*akefile))
MLX_DEP		=	$(foreach dir, $(D_MLX), $(wildcard $(dir)*.c $(dir)*.h $(dir)*akefile))

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

vpath %.c $(D_SRCS)

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
	@$(MAKE) -C $(D_LFT) bonus
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

# ╭━━━━━━━━━━━━══════════╕出 ❖ DEBUGGING ❖ 力╒═══════════━━━━━━━━━━━━╮ #

norminette:
	norminette $(D_SRC) $(D_LFT) $(D_INC)

D_DBG		=	$(D_BLD)debug/

SUPP		=	x11_writev.supp

SUPP_FILE	=	$(addprefix $(D_DBG), $(SUPP))

$(D_DBG): | $(D_BLD)
	@$(MKDIR) $@

rmv:
	@$(RM) $(D_DBG)
	@echo "\e[1;33m🍤 Debug files suppressed successfully 🍤\e[0m"

rmsupp:
	@$(RM) $(wildcard $(D_DBG)*.supp)
	@echo "\e[1;38;5;217m🐙 All suppression files deleted successfully 🐙\e[0m"

supp:
	@$(MAKE) $(SUPP_FILE)

$(SUPP_FILE): | $(D_DBG)
	@echo "{" > $(SUPP_FILE)
	@echo "   writev_x11_libxcb" >> $(SUPP_FILE)
	@echo "   Memcheck:Param" >> $(SUPP_FILE)
	@echo "   writev(vector[0])" >> $(SUPP_FILE)
	@echo "   ..." >> $(SUPP_FILE)
	@echo "   obj:/usr/lib/x86_64-linux-gnu/libxcb.so.*" >> $(SUPP_FILE)
	@echo "}" >> $(SUPP_FILE)
	@echo "\e[1;38;5;216m🦀 Suppression file generated: $(SUPP_FILE) 🦀\e[0m"

valgrind: $(SUPP_FILE)
	@$(MAKE)
	@clear
	@valgrind										\
		--leak-check=full								\
		--show-leak-kinds=all							\
		--track-origins=yes 							\
		--track-fds=yes									\
		--suppressions=$(CURDIR)/$(SUPP_FILE)			\
		./$(NAME) $(word 2,$(MAKECMDGOALS))