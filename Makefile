NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

MLX42_PATH = libs/MLX42
MLX42 = $(MLX42_PATH)/build/libmlx42.a

LIBFT_PATH = libs/libft
LIBFT = $(LIBFT_PATH)/libft.a

HEADERS = -I ./libs -I $(MLX42_PATH)/include/MLX42 -I $(LIBFT_PATH)

SRCDIR = ./src/
SRCS =	src/main.c src/mlx_cleanup.c src/mlx_init.c \
		src/mlx_movement.c src/mlx_player.c src/mlx.c \
		src/parser_aux.c src/parser_aux2.c src/parser_aux3.c \
		src/parser_aux4.c src/parser_player.c src/parser_utils.c \
		src/parser.c src/raycast_render.c src/raycast_utils.c \
		src/raycast.c src/texture_color.c src/texture.c src/debug.c

OBJDIR = ./obj/
OBJS = $(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)

all : $(NAME)

$(NAME) : $(OBJS) $(MLX42) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX42) $(LIBFT) $(HEADERS) -lglfw -o $(NAME) -lm >/dev/null
	@echo "$(GREEN)$(EYE) $(NAME) compiled successfully! $(DEF_COLOR)"

$(LIBFT) :
	@make -C $(LIBFT_PATH) >/dev/null
	@echo "$(GREEN)$(EYE) libft compiled successfully! $(DEF_COLOR)"

$(MLX42) :
	@cmake $(MLX42_PATH) -B $(MLX42_PATH)/build >/dev/null && make -C $(MLX42_PATH)/build -j4 >/dev/null
	@echo "$(GREEN)$(EYE) MLX42 compiled successfully! $(DEF_COLOR)"

$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@ >/dev/null
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"

clean :
	@$(RM) $(OBJDIR)
	@make -C $(LIBFT_PATH) clean >/dev/null
	@make -C $(MLX42_PATH)/build clean >/dev/null
	@echo "$(WHITE)$(EYE) Cleaned object files and MLX42 build files! $(DEF_COLOR)"

fclean :
	@$(RM) $(OBJDIR)
	@$(RM) $(NAME)
	@make -C $(LIBFT_PATH) fclean >/dev/null
	@$(RM) $(MLX42_PATH)/build/*
	@echo "$(WHITE)$(EYE) Fully cleaned project! $(DEF_COLOR)"

re : fclean all

.PHONY : all clean fclean re

DEF_COLOR = \033[0;39m
GREEN = \033[1;92m
YELLOW = \033[1;93m
EYE = \033[1;95m
WHITE = \033[5;97m