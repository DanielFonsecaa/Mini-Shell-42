NAME =	libft.a

BUILD_PATH	= .build
LIBFT_PATH	= ./libft
SRC =	$(addprefix $(LIBFT_PATH)/, ft_isalpha.c ft_isprint.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_strlen.c ft_strcmp.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_toupper.c ft_foreach.c ft_tolower.c ft_atoi.c ft_atol.c ft_strdup.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strjoin_arr.c ft_strtrim.c ft_strtrim_char.c ft_split.c ft_split_charset.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_isspace.c ft_iswhite_space.c ft_atoll.c)

BONUS = $(addprefix $(LIBFT_PATH)/, ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c)

PRINTF_PATH	= ./printf
PRINTF_SRC 	= $(addprefix $(PRINTF_PATH)/, ft_printf.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_putunsint.c ft_puthex_small.c ft_puthex_big.c ft_putpoint.c)

PRINTFD_PATH	= ./printf_fd
PRINTFD_SRC 	= $(addprefix $(PRINTFD_PATH)/, ft_printf_fd.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putunsint_fd.c ft_puthex_small_fd.c ft_puthex_big_fd.c ft_putpoint_fd.c)

GNL_PATH 	= ./gnl
GNL_SRC		= $(addprefix $(GNL_PATH)/, get_next_line.c get_next_line_utils.c)

OBJS		= $(addprefix $(BUILD_PATH)/, $(notdir $(SRC:.c=.o)))
BONUS_OBJS	= $(addprefix $(BUILD_PATH)/, $(notdir $(BONUS:.c=.o)))
PRINTF_OBJS	= $(addprefix $(BUILD_PATH)/, $(notdir $(PRINTF_SRC:.c=.o)))
PRINTFD_OBJS	= $(addprefix $(BUILD_PATH)/, $(notdir $(PRINTFD_SRC:.c=.o)))
GNL_OBJS	= $(addprefix $(BUILD_PATH)/, $(notdir $(GNL_SRC:.c=.o)))

### Message Vars
_SUCCESS 		= [$(B)$(GRN)SUCCESS$(D)]
#==============================================================================#
CFLAGS		= -Wall -Wextra -Werror -g

CC 			= cc
RM 			= rm -rf
AR 			= ar rcs
MKDIR_P		= mkdir -p
#==============================================================================#

all: $(NAME)

$(BUILD_PATH):
	@$(MKDIR_P) $(BUILD_PATH)

$(BUILD_PATH)/%.o: $(LIBFT_PATH)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_PATH)/%.o: $(PRINTF_PATH)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_PATH)/%.o: $(PRINTFD_PATH)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_PATH)/%.o: $(GNL_PATH)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(BUILD_PATH) $(OBJS)
	@echo " $(GOLD)Archiving libft archive$(D)"
	@$(AR) $(NAME) $(OBJS)
	@echo " $(B)libft archived: $(_SUCCESS)$(D)"

bonus: $(BUILD_PATH) $(OBJS) $(BONUS_OBJS)
	@echo " $(GOLD)Archiving libft w/ bonus$(D)"
	@$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo " libft archived w/ bonus: $(_SUCCESS)$(D)"

extra: $(BUILD_PATH) $(OBJS) $(BONUS_OBJS) $(GNL_OBJS) $(PRINTF_OBJS) $(PRINTFD_OBJS)
	@$(AR) $(NAME) $(OBJS) $(BONUS_OBJS) $(GNL_OBJS) $(PRINTF_OBJS) $(PRINTFD_OBJS)
	@echo " $(B)libft archived: $(_SUCCESS)$(D)"

clean:
	@echo "* $(RED)Removing libft binaries$(D)"
	@$(RM) $(OBJS) $(BONUS_OBJS) $(GNL_OBJS) $(PRINTF_OBJS) $(PRINTFD_OBJS)
	@echo "* $(GOLD)Cleaning libft binaries: $(_SUCCESS)$(D)"

fclean: clean
	@echo " $(RED)Removing $(NAME) archive and .build directory$(D)"
	@$(RM) $(NAME)
	@$(RM) $(BUILD_PATH)
	@echo " $(GOLD)Cleaning $(NAME) archive and .build directory: $(_SUCCESS)$(D)"

re: fclean extra

.PHONY: all bonus extra clean fclean re
#==============================================================================#
# Basic colors
B  		= $(shell tput bold)
RED		= $(shell tput setaf 1)
GRN		= $(shell tput setaf 2)

# Extended colors
GOLD    = $(shell tput setaf 220)

# Reset
D       = $(shell tput sgr0)