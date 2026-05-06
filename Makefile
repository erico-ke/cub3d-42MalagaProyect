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
SRCS =	src/main.c src/mlx/mlx_cleanup.c src/mlx/mlx_init.c \
		src/mlx/mlx_movement.c src/mlx/mlx_player.c src/mlx/mlx.c \
		src/parser/parser_aux.c src/parser/parser_aux2.c src/parser/parser_aux3.c \
		src/parser/parser_aux4.c src/parser/parser_player.c src/parser/parser_utils.c \
		src/parser/parser.c src/raycasting/raycast_render.c src/raycasting/raycast_utils.c \
		src/raycasting/raycast.c src/textures/texture_color.c src/textures/texture.c src/debug.c

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