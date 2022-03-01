NAME = minishell

CC = gcc

LIBFTP = libraries/libft
PATHB = build/
PATHO = build/objs/
PATHS = src/
PATHSL = src/lexor/
PATHSP = src/parser/
PATHSB = src/builtins/
PATHSU = src/utils/
PATHP = src/pipex/


BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHR)

src	=	$(wildcard $(PATHS)*.c) \
		$(wildcard $(PATHSL)*.c) \
		$(wildcard $(PATHSP)*.c) \
		$(wildcard $(PATHSB)*.c) \
		$(wildcard $(PATHSU)*.c) 

OBJS	=	$(addprefix $(PATHO), $(notdir $(patsubst %.c, %.o, $(src))))

FLAGS	=	-Wall -Werror -Wextra -g

LIBFT	=	./libraries/libft/libft.a

HEADER	=	$(wildcard ./includes/*.h) 
	
INCLUDES =-Iincludes -I$(PATHP) -I$(LIBFTP)


all: $(BUILD_PATHS) $(NAME)

$(PATHO)%.o:: $(PATHS)%.c
	@echo "Compiling ${notdir $<}			in	$(PATHS)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSL)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}			in	$(PATHSL)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSP)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}			in	$(PATHSP)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSB)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}			in	$(PATHSB)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSU)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}			in	$(PATHSU)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(NAME): $(LIBFT) $(OBJS) $(HEADERS)
	@$(CC) $(FLAGS) $(LIBFT) $(OBJS) -lreadline -o $(NAME)
	@echo "Success"

$(LIBFT):
	$(MAKE) -C ./libraries/libft

$(PATHB):
	$(MKDIR) $(PATHB)

$(PATHO):
	$(MKDIR) $(PATHO)

clean:
	@echo "Cleaning"
	@rm -f $(OBJS)
	@make fclean -C libraries/libft

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re: fclean all

# .PRECIOUS: $(PATHO)%.o