NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_DIR = srcs
SRCS = main.c error_handler.c parse_map.c parse_utils.c draw_map.c draw_line.c init.c adjust_z.c scale_shift.c hook.c free.c
SRCS_FILES = $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS = $(SRCS_FILES:.c=.o)

MLX_DIR = ./minilibx
MLX = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS = -L $(MLX_DIR) -lmlx_Linux -L/usr/lib -I $(MLX_DIR) -lX11 -lm -lz -lXext $(MLX)

LIBFT_DIR = ./libft
LIBFT_A = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) $(LIBFT_A)

$(NAME): $(OBJS)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME) -g

all: $(NAME)

%.o: %.c Makefile include/fdf.h
	$(CC) $(CFLAGS) -I . -I $(MLX_DIR) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
