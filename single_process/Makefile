#####   COLORS   #####

END				= \033[0m

GREY			= \033[30m
RED				= \033[31m
GREEN			= \033[32m
YELLOW			= \033[33m
BLUE			= \033[34m
PURPLE			= \033[35m
CYAN			= \033[36m

HIGH_RED		= \033[91m

#####   INFO   #####

NAME			= column_formatter

#####   RESOURCES   #####

INCLUDE			= includes
SRC_DIR			= srcs
OBJ_DIR			= objs

SRC_SUB_DIRS	= $(shell find $(SRC_DIR) -type d)
OBJ_SUB_DIRS	= $(SRC_SUB_DIRS:$(SRC_DIR)%=$(OBJ_DIR)%)

SRCS_C			= $(foreach DIR, $(SRC_SUB_DIRS), $(wildcard $(DIR)/*.c))
OBJS			= $(SRCS_C:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#####   COMMANDS   #####

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
IFLAGS			= -I$(INCLUDE)

MD				= mkdir -p
RM				= rm -rf

#####   GIT   #####

ADD = git add .
COMMIT = git commit -m
PUSH = git push



#####   BASE RULES   #####

all: $(NAME)

$(NAME): $(OBJ_SUB_DIRS) $(OBJS)
	@ $(CC) $(CFLAGS) $(IFLAGS) $(OBJS) -o $@
	@ echo "$(GREEN)[+] $(NAME)$(END)"


$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@ $(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@ echo "$(BLUE)[+] $@$(END)"

$(OBJ_SUB_DIRS):
	@ $(MD) $(OBJ_SUB_DIRS)
	@ echo "$(PURPLE)[+] $(SRC_DIR) -> $(OBJ_DIR) $(END)"


clean:
	@ $(RM) $(OBJ_DIR)
	@ echo "$(YELLOW)[+] $(OBJ_DIR)$(END)"

fclean: clean
	@ $(RM) $(NAME)
	@ echo "$(YELLOW)[+] $(NAME)$(END)"

re: fclean all


#####   EXTRA RULES   #####

docs:
	@ doxygen > /dev/null
	@ echo "$(GREEN)[+] Docs Generated$(END)"
	@ echo "$(BLUE)[+] Open ./docs/html/index.html$(END)"

latex: docs
	@ make -s -C docs/latex > /dev/null 2> /dev/null
	@ echo "$(GREEN)[+] Latex Compiled$(END)"
	@ echo "$(BLUE)[+] Open ./docs/latex/refman.pdf$(END)"

test: all
	clear
	@ bash tester.sh $(NAME)

val: all
	clear
	@ valgrind --leak-check=full ./$(NAME) 3 40 20 5 tests/example.txt tmp.tmp

run: all
	clear
	@ ./$(NAME) 3 40 20 5 tests/example.txt tmp.tmp

rrun: fclean run

git:
	@ $(eval MESSAGE := $(or $(m), $(error Usage: make commit m="<commit message>")))
	@ $(ADD)
	@ $(COMMIT) $(MESSAGE)
	@ $(PUSH)


#####   PHONY   #####

.PHONY: all clean fclean re docs latex test val run rrun git
