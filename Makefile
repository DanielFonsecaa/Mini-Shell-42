#==============================================================================#
#                                     NAMES                                    #
#==============================================================================#

NAME 			= minishell

### Message Vars
_SUCCESS 		= [$(B)$(GRN)SUCCESS$(D)]

#==============================================================================#
#                                    PATHS     
#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

SRC_PATH		= src
INC_PATH		= includes
BUILD_PATH		= .build
LIBS_PATH		= lib
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
#                              COMPILER & FLAGS                                #
#==============================================================================#

MAKE 			= make --no-print-directory -C

CC				= cc

CFLAGS			= -Wall -Wextra -Werror -g
RLFLAG 			= -L$(READLINE_PATH)/lib -lreadline

INC				= -I $(INC_PATH)

RM				= rm -rf
AR				= ar rcs
MKDIR_P			= mkdir -p


#==============================================================================#
#                                  RULES                                       #
#==============================================================================#


all: $(BUILD_PATH) $(NAME)	## Compile

$(NAME): $(BUILD_PATH) $(LIBFT_ARC) $(OBJS)	## Compile
	@echo "  $(B)$(GOLD)Compiling$(SILV)$(NAME)$(D)"
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
	@echo "  $(B)$(GOLD)Creating$(SILV)$(BUILD_PATH)$(GOLD)folder :$(D)$(_SUCCESS) ✔︎ 📂"
	
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT_ARC):
	@$(MAKE) $(LIBFT_PATH) extra >/dev/null

clean:				## Remove object files
	@echo "  $(B)$(GOLD)Cleaning object files $(D)"
	@$(RM) $(BUILD_PATH); 
	@$(RM) $(BONUS_BUILD_PATH);
	@$(MAKE) $(LIBFT_PATH) clean >/dev/null
	@echo "  $(B)$(GOLD)Removing $(SILV)$(BUILD_PATH)$(GOLD) folder & files$(D): $(_SUCCESS) 🧹"; \

fclean: clean			## Remove executable
	@echo "  $(B)$(GOLD)Cleaning executables $(D)"
	@$(RM) $(NAME);
	@$(RM) tester
	@$(RM) readline.supp
	@$(MAKE) $(LIBFT_PATH) fclean >/dev/null
	@echo "  $(B)$(GOLD)Removing $(SILV)$(NAME)$(GOLD) file: $(D) $(_SUCCESS) 🧹"; \

re: fclean all	## Purge & Recompile

nn:	## Check Norminette
	norminette -R CheckForbiddenSourceHeader

run: re
	./$(NAME)

gdb: re
	gdb --tui ./minishell

val: 
	@echo "{\n   leak readline\n   Memcheck:Leak\n...\n   fun:readline\n}\n{\n   leak add_history\n   Memcheck:Leak\n...\n   fun:add_history\n}" > readline.supp
	@valgrind --suppressions=readline.supp --leak-check=full -s --show-leak-kinds=all ./$(NAME)
	
forbidden:	## Show forbidden functions
	nm -g ./$(NAME) | grep "U"


.PHONY: all deps clean fclean libclean re get_libft forbidden start nn val gdb run

#==============================================================================#
#                                  UTILS                                       #
#==============================================================================#

# Colors
B  		= $(shell tput bold)
BLA		= $(shell tput setaf 0)
RED		= $(shell tput setaf 1)
GRN		= $(shell tput setaf 2)
YEL		= $(shell tput setaf 3)
BLU		= $(shell tput setaf 4)
MAG		= $(shell tput setaf 5)
CYA		= $(shell tput setaf 6)
WHI		= $(shell tput setaf 7)
GRE		= $(shell tput setaf 8)
BRED 	= $(shell tput setaf 9)
BGRN	= $(shell tput setaf 10)
BYEL	= $(shell tput setaf 11)
BBLU	= $(shell tput setaf 12)
BMAG	= $(shell tput setaf 13)
BCYA	= $(shell tput setaf 14)
BWHI	= $(shell tput setaf 15)

# Extended colors
ORG     = $(shell tput setaf 208)  # Orange
PINK    = $(shell tput setaf 205)  # Pink
PURP    = $(shell tput setaf 93)   # Purple
LIME    = $(shell tput setaf 154)  # Lime
AQUA    = $(shell tput setaf 87)   # Aqua
GOLD    = $(shell tput setaf 220)  # Gold
SILV    = $(shell tput setaf 250)  # Silver
NAVY    = $(shell tput setaf 17)   # Navy Blue
TEAL    = $(shell tput setaf 23)   # Teal
WINE    = $(shell tput setaf 52)   # Wine Red

# Text effects
BLINK   = $(shell tput blink)    # Blinking text
DIM     = $(shell tput dim)      # Dim/faint text
UNDER   = $(shell tput smul)     # Underline
NOUNDER = $(shell tput rmul)     # Remove underline
REV     = $(shell tput rev)      # Reverse colors (swap fg/bg)
STANDOUT= $(shell tput smso)     # Standout mode
NOSTAND = $(shell tput rmso)     # Remove standout
ITALIC  = $(shell tput sitm)     # Italic text (if supported)
NOITAL  = $(shell tput ritm)     # Remove italic

# Reset and special
D       = $(shell tput sgr0)
BEL     = $(shell tput bel)
CLR     = $(shell tput el 1)

start:
	@# Frame 1 - gold
	@clear
	@printf "\n"
	@printf "\n"
	@printf "$(GOLD)	███╗   ███╗██╗███╗   ██╗██╗███████╗$(RED)██╗  ██╗███████╗██╗     ██╗$(D)\n"
	@printf "$(GOLD)	████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║$(D)\n"
	@printf "$(GOLD)	██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║$(D)\n"
	@printf "$(GOLD)	██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║$(D)\n"
	@printf "$(GOLD)	██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗$(D)\n"
	@printf "$(GOLD)	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝$(D)\n"
	@printf "$(D)\n"
	@printf "\n"
	@sleep 0.3

	@# Frame 2
	@clear
	@printf "\n"
	@printf "\n"
	@printf "$(GOLD)	███╗   ███╗██╗███╗   ██╗██╗███████╗$(RED)██╗  ██╗███████╗██╗     ██╗$(D)\n"
	@printf "$(GOLD)	████╗ ████║██║████╗  ██║██║██╔════╝$(RED)██║  ██║██╔════╝██║     ██║$(D)\n"
	@printf "$(GOLD)	██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║$(D)\n"
	@printf "$(GOLD)	██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║$(D)\n"
	@printf "$(GOLD)	██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗$(D)\n"
	@printf "$(GOLD)	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝$(D)\n"
	@printf "$(D)\n"
	@printf "\n"
	@sleep 0.3

	@# Frame 3 - with more red
	@clear
	@printf "\n"
	@printf "\n"
	@printf "$(GOLD)	███╗   ███╗██╗███╗   ██╗██╗███████╗$(RED)██╗  ██╗███████╗██╗     ██╗$(D)\n"
	@printf "$(GOLD)	████╗ ████║██║████╗  ██║██║██╔════╝$(RED)██║  ██║██╔════╝██║     ██║$(D)\n"
	@printf "$(GOLD)	██╔████╔██║██║██╔██╗ ██║██║███████╗$(RED)███████║█████╗  ██║     ██║$(D)\n"
	@printf "$(GOLD)	██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║$(D)\n"
	@printf "$(GOLD)	██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗$(D)\n"
	@printf "$(GOLD)	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝$(D)\n"
	@printf "$(D)\n"
	@printf "\n"
	@sleep 0.3

	@# Frame 4 - more red
	@clear
	@printf "\n"
	@printf "\n"
	@printf "$(GOLD)	███╗   ███╗██╗███╗   ██╗██╗███████╗$(RED)██╗  ██╗███████╗██╗     ██╗$(D)\n"
	@printf "$(GOLD)	████╗ ████║██║████╗  ██║██║██╔════╝$(RED)██║  ██║██╔════╝██║     ██║$(D)\n"
	@printf "$(GOLD)	██╔████╔██║██║██╔██╗ ██║██║███████╗$(RED)███████║█████╗  ██║     ██║$(D)\n"
	@printf "$(GOLD)	██║╚██╔╝██║██║██║╚██╗██║██║╚════██║$(RED)██╔══██║██╔══╝  ██║     ██║$(D)\n"
	@printf "$(GOLD)	██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗$(D)\n"
	@printf "$(GOLD)	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝$(D)\n"
	@printf "$(D)\n"
	@printf "\n"
	@sleep 0.3

		@# Frame 5 - moreeeeee
	@clear
	@printf "\n"
	@printf "\n"
	@printf "$(GOLD)	███╗   ███╗██╗███╗   ██╗██╗███████╗$(RED)██╗  ██╗███████╗██╗     ██╗$(D)\n"
	@printf "$(GOLD)	████╗ ████║██║████╗  ██║██║██╔════╝$(RED)██║  ██║██╔════╝██║     ██║$(D)\n"
	@printf "$(GOLD)	██╔████╔██║██║██╔██╗ ██║██║███████╗$(RED)███████║█████╗  ██║     ██║$(D)\n"
	@printf "$(GOLD)	██║╚██╔╝██║██║██║╚██╗██║██║╚════██║$(RED)██╔══██║██╔══╝  ██║     ██║$(D)\n"
	@printf "$(GOLD)	██║ ╚═╝ ██║██║██║ ╚████║██║███████║$(RED)██║  ██║███████╗███████╗███████╗$(D)\n"
	@printf "$(GOLD)	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝$(D)\n"
	@printf "$(D)\n"
	@printf "\n"
	@sleep 0.3

	@# Frame 6 - I said moreeeeeeeeee
	@clear
	@printf "\n"
	@printf "\n"
	@printf "$(GOLD)	███╗   ███╗██╗███╗   ██╗██╗███████╗$(RED)██╗  ██╗███████╗██╗     ██╗$(D)\n"
	@printf "$(GOLD)	████╗ ████║██║████╗  ██║██║██╔════╝$(RED)██║  ██║██╔════╝██║     ██║$(D)\n"
	@printf "$(GOLD)	██╔████╔██║██║██╔██╗ ██║██║███████╗$(RED)███████║█████╗  ██║     ██║$(D)\n"
	@printf "$(GOLD)	██║╚██╔╝██║██║██║╚██╗██║██║╚════██║$(RED)██╔══██║██╔══╝  ██║     ██║$(D)\n"
	@printf "$(GOLD)	██║ ╚═╝ ██║██║██║ ╚████║██║███████║$(RED)██║  ██║███████╗███████╗███████╗$(D)\n"
	@printf "$(GOLD)	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝$(RED)╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝$(D)\n"
	@printf "					   $(RED)⣿⣿⣿⣿⣿⣿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⢿⣿⣿⣿⣿⣿\n"
	@printf "					   $(RED)⣿⡟⠉⡏⣿⡇⠀⠀⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠀⠈⣿⣿⠛⢻⣿\n"
	@printf "					   $(RED)⣿⣧⠀⠤⡿⠇⠀⠀⡷⣿⡇⠀⢹⡿⢿⡏⠀⠈⣿⡇⠀⠀⢰⢿⣿⠀⠈⣿\n"
	@printf "					   $(RED)⣿⣿⡇⠀⠀⠀⠀⠀⡇⣿⡇⠀⠀⠉⠉⠀⠀⠀⣿⡇⠀⠀⠘⠒⠚⠀⢀⢹\n"
	@printf "					   $(RED)⠉⠉⠀⠀⠀⠀⠀⢸⢰⣿⣿⡀⠀⠀⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⡌⣾\n"
	@printf "					   $(RED)⠀⠀⠀⠀⠀⠀⠀⠘⢮⣿⠟⠀⠀⠀⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠐⠀⣿\n"
	@printf "					   $(RED)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢸⣿⠀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "					   $(RED)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣽⣿⡇⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "					   $(RED)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "					   $(RED)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠧⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "$(D)\n"
	@printf "\n"
	@sleep 0.3
	@./$(NAME)
