# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/17 18:13:19 by rde-mour          #+#    #+#              #
#    Updated: 2024/01/22 19:10:32 by rde-mour         ###   ########.org.br    #
#                                                                              #
# **************************************************************************** #

RED					= $(shell tput setaf 1)
GREEN				= $(shell tput setaf 2)
YELLOW				= $(shell tput setaf 3)
BLUE				= $(shell tput setaf 4)
MAGENT				= $(shell tput setaf 5)
RESET				= $(shell tput sgr0)

NAME				= pipex

FILES				= pipex.c \
					  pipex_utils.c \
					  string.c

LIBS				= $(LIBFTXDIR)/libftx.a

SRCSDIR				= srcs
OBJSDIR				= objs
LIBFTXDIR			= libs/libftx

SRCS				= $(FILES:%.c=$(SRCSDIR)/%.c)
OBJS				= $(FILES:%.c=$(OBJSDIR)/%.o)
SRCS_BONUS			= $(FILES:%.c=$(SRCSDIR)/bonus/%_bonus.c)
OBJS_BONUS			= $(FILES:%.c=$(OBJSDIR)/bonus/%_bonus.o)

INCLUDES			= -I ./includes -I ./libs/libftx/includes

COMPILER			= cc
CFLAGS				= -Wall -Wextra -Werror -g3
MESSAGE				= mandatory

ifdef				WITH_BONUS
					DELETE := $(OBJS)
					SRCS := $(SRCS_BONUS)
					OBJS := $(OBJS_BONUS)
					MESSAGE := bonus
endif

all:				$(NAME)

$(NAME):			$(LIBS) $(OBJS)
					@$(COMPILER) $(CFLAGS) $(OBJS) $(LIBS) $(INCLUDES) -o $(NAME)
					@echo "$(BLUE)Compiled $(NAME) successfully$(RESET)"

$(OBJSDIR)/%.o:		$(SRCSDIR)/%.c
					@mkdir -p $(@D)
					@$(COMPILER) $(CFLAGS) -c $< -o $@ $(INCLUDES)
					@echo "$(GREEN)Compiled $(RESET)$(notdir $<)"

$(LIBS):
					@git submodule sync $(LIBFTXDIR)
					@git submodule update --init --force --remote $(LIBFTXDIR)
					@make -sC $(LIBFTXDIR)

bonus:
					@make WITH_BONUS=TRUE --no-print-directory

clean:
					@echo "$(RED)Removing $(RESET)$(NAME) objects"
					@rm -Rf $(OBJSDIR)

fclean:				clean
					@make fclean -sC $(LIBFTXDIR)
					@echo "$(RED)Removing $(RESET)$(NAME)"
					@rm -rf $(NAME)

re:					fclean all

.PHONY:				all bonus clean fclean re
