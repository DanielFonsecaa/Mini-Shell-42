#==============================================================================#
#                                RESOURCES URLS                                #
#==============================================================================#

LIBFT_URL 	= git@github.com:DanielFonsecaa/libft_gnl_printf.git

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
LIBS_PATH		= lib

FILES	= main.c free.c utils.c

SRC						= $(addprefix $(SRC_PATH)/, $(FILES))
OBJS					= $(SRC:$(SRC_PATH)/%.c=$(BUILD_PATH)/%.o)

HEADERS				= $(INC_PATH)/pipex.h

LIBFT_PATH		= $(LIBS_PATH)/libft
LIBFT_ARC			= $(LIBFT_PATH)/libft.a

#==============================================================================#
#                              COMPILER & FLAGS                                #
#==============================================================================#

MAKE = make --no-print-directory -C

CC						= cc

CFLAGS				= -Wall -Wextra -Werror -g

INC						= -I $(INC_PATH)

RM		= rm -rf
AR		= ar rcs
MKDIR_P	= mkdir -p


#==============================================================================#
#                                  RULES                                       #
#==============================================================================#


all: deps $(BUILD_PATH) $(NAME)	## Compile

$(NAME): $(BUILD_PATH) $(LIBFT_ARC) $(OBJS)	## Compile
	@$(CC) $(CFLAGS) $(OBJS) $(INC) $(LIBFT_ARC) -o $(NAME)

deps:		## Download/Update deps
	@if test -d "$(LIBFT_PATH)"; then \
		echo "   $(B)$(RED)$(D) [$(GRN)Nothing to be done!$(D)]"; fi
	@if test ! -d "$(LIBFT_PATH)"; then make get_libft; \
		else echo "   $(B)$(GOLD)[libft]$(D) folder found ✔︎ 📂"; fi
	
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(BUILD_PATH):
	@$(MKDIR_P) $(BUILD_PATH)
	@echo "  $(B)$(GOLD)Creating$(SILV)$(BUILD_PATH)$(GOLD)folder :$(D)$(_SUCCESS) ✔︎ 📂"


$(LIBFT_ARC):
	@$(MAKE) $(LIBFT_PATH) extra

get_libft:
	@echo " $(B)$(AQUA)Getting Libft$(D)"
	@$(MKDIR_P) $(LIBS_PATH)
	@git clone $(LIBFT_URL) $(LIBFT_PATH);
	@echo "    $(B)$(GRN)Libft submodule download$(D): $(_SUCCESS) ✔︎ 💾"

clean:				## Remove object files
	@echo "  $(B)$(GOLD)Cleaning object files $(D)"
	@$(RM) $(BUILD_PATH); 
	@$(RM) $(BONUS_BUILD_PATH); 
	@echo "  $(B)$(GOLD)Removing $(SILV)$(BUILD_PATH)$(GOLD) folder & files$(D): $(_SUCCESS) 🧹"; \

fclean: clean			## Remove executable
	@echo "  $(B)$(GOLD)Cleaning executables $(D)"
	@$(RM) $(NAME);
	@$(RM) tester
	@echo "  $(B)$(GOLD)Removing $(SILV)$(NAME)$(GOLD) file: $(D) $(_SUCCESS) 🧹"; \

libclean: fclean	## Remove libs
	@echo "  $(B)$(GOLD)Cleaning libraries $(D)"
	@$(RM) $(LIBS_PATH)
	@echo "  $(B)$(GOLD)Removing $(SILV)lib & checker$(D) : $(_SUCCESS) 🧹"

re: libclean all	## Purge & Recompile


.PHONY: all deps clean fclean libclean re get_libft

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

# Reset and special
D       = $(shell tput sgr0)
BEL     = $(shell tput bel)
CLR     = $(shell tput el 1)
