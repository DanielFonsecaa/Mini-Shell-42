#==============================================================================#
#                                     NAMES                                    #
#==============================================================================#

NAME 			= minishell

### Message Vars
_SUCCESS 		= [$(B)$(GRN)SUCCESS$(D)]

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

SRC_PATH		= src
INC_PATH		= includes
BUILD_PATH		= .build
READLINE_PATH	= vendor/readline/

FILES			=	main.c \
					lexing/lexing.c \
					lexing/utils_lex.c \
					lexing/utils_list_lex.c \
					safe/safe_functions.c \
					free_data/free_data.c \
					parsing/parsing.c \
					parsing/utils_parse.c \
					parsing/syntax.c \
					built_ins/built_ins.c \
					built_ins/cd.c \
					built_ins/echo.c \
					built_ins/env.c \
					built_ins/exit.c \
					built_ins/pwd.c \
					built_ins/unset.c \
					built_ins/export/export.c \
					built_ins/export/utils_list_export.c \
					built_ins/export/utils_export.c \
					execute/execute.c \
					execute/path.c \
					execute/regular.c \
					inits/inits.c \
					utils/comand_utils.c

SRC				= $(addprefix $(SRC_PATH)/, $(FILES))
OBJS			= $(SRC:$(SRC_PATH)/%.c=$(BUILD_PATH)/%.o)

HEADERS			= $(INC_PATH)/minishell.h

LIBFT_PATH		= libft
LIBFT_ARC		= $(LIBFT_PATH)/libft.a

#==============================================================================#
#                              COMPILER & FLAGS                               #
#==============================================================================#

MAKE 			= make --no-print-directory -C

CC				= cc

CFLAGS			= -Wall -Wextra -Werror -g
RLFLAG 			= -L$(READLINE_PATH)/lib -lreadline

INC				= -I $(INC_PATH)

RM				= rm -rf
MKDIR_P			= mkdir -p

#==============================================================================#
#                                  RULES                                       #
#==============================================================================#

all: $(BUILD_PATH) $(NAME)

$(NAME): $(BUILD_PATH) $(LIBFT_ARC) $(OBJS)
	@echo "  $(B)$(GOLD)Compiling$(SILV) $(NAME)$(D)"
	@$(CC) $(CFLAGS) $(OBJS) $(RLFLAG) $(LIBFT_ARC) $(INC) -o $(NAME)
	@clear
	@printf "\n"
	@printf "$(GOLD)\n"
	@printf "	███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗\n"
	@printf "	████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║\n"
	@printf "	██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║\n"
	@printf "	██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║\n"
	@printf "	██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n"
	@printf "	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n"
	@printf "$(D)\n"
	@printf "$(B)$(SILV)                           Made by dda-fons & Michel-kun $(D)\n"
	@printf "\n"

$(BUILD_PATH):
	@$(MKDIR_P) $(BUILD_PATH)
	@echo "  $(B)$(GOLD)Creating $(SILV)$(BUILD_PATH)$(GOLD) folder: $(D)$(_SUCCESS)"

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT_ARC):
	@$(MAKE) $(LIBFT_PATH) extra >/dev/null

clean:
	@echo "  $(B)$(GOLD)Cleaning object files$(D)"
	@$(RM) $(BUILD_PATH)
	@$(MAKE) $(LIBFT_PATH) clean >/dev/null
	@echo "  $(B)$(GOLD)Removing $(SILV)$(BUILD_PATH)$(GOLD) folder: $(D)$(_SUCCESS)"

fclean: clean
	@echo "  $(B)$(GOLD)Cleaning executables$(D)"
	@$(RM) $(NAME)
	@$(RM) readline.supp
	@$(MAKE) $(LIBFT_PATH) fclean >/dev/null
	@echo "  $(B)$(GOLD)Removing $(SILV)$(NAME)$(GOLD) file: $(D)$(_SUCCESS)"

re: fclean all

run: re
	./$(NAME)

gdb: re
	gdb --tui ./minishell

val:
	@echo "{\n   leak readline\n   Memcheck:Leak\n...\n   fun:readline\n}\n{\n   leak add_history\n   Memcheck:Leak\n...\n   fun:add_history\n}" > readline.supp
	@valgrind --suppressions=readline.supp --leak-check=full -s --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re run gdb val

#==============================================================================#
#                                  COLORS                                      #
#==============================================================================#

# Basic colors
B  		= $(shell tput bold)
RED		= $(shell tput setaf 1)
GRN		= $(shell tput setaf 2)
BLU		= $(shell tput setaf 4)

# Extended colors used in your makefile
GOLD    = $(shell tput setaf 220)
SILV    = $(shell tput setaf 250)

# Reset
D       = $(shell tput sgr0)