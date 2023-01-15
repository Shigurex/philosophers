CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS_NAME = main_bonus.c \
	execute_bonus.c \
	setup_bonus.c \
	utils_bonus.c \
	philo_bonus.c \
	monitor_bonus.c \
	ft_itoa_bonus.c
SRCDIR = srcs
OBJDIR = objs
SRCS = $(addprefix $(SRCDIR)/, $(SRCS_NAME))
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
NAME = philo_bonus

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(shell find $(SRCDIR) -type d | sed 's/^$(SRCDIR)/$(OBJDIR)/g')

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS)
	rm -rf $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
