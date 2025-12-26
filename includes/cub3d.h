/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:12:45 by erico-ke          #+#    #+#             */
/*   Updated: 2025/12/26 13:18:06 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <sys/time.h>
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libft/src/libft.h"

/* ************************************************************************** */
/*                                   MACROS                                   */
/* ************************************************************************** */

# define SCREEN_W 1200
# define SCREEN_H 600
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

/**
 * @struct s_player
 * @brief Stores player position, direction, and camera plane vectors
 * 
 * @param x Integer grid X coordinate
 * @param y Integer grid Y coordinate
 * @param x_uni Floating-point precise X position
 * @param y_uni Floating-point precise Y position
 * @param dir_x Direction vector X component
 * @param dir_y Direction vector Y component
 * @param plane_x Camera plane X component (perpendicular to direction)
 * @param plane_y Camera plane Y component (defines FOV)
 */
typedef struct s_player
{
	int				x;
	int				y;
	double			x_uni;
	double			y_uni;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}	t_player;

/**
 * @struct s_ray
 * @brief Contains all raycasting calculation data for a single ray
 * 
 * @param camerax Normalized camera X coordinate [-1, 1]
 * @param raydirx Ray direction X component
 * @param raydiry Ray direction Y component
 * @param mapx Current map grid X coordinate
 * @param mapy Current map grid Y coordinate
 * @param sidedistx Distance to next X grid line
 * @param sidedisty Distance to next Y grid line
 * @param deltadistx Distance between X grid lines along ray
 * @param deltadisty Distance between Y grid lines along ray
 * @param perpwalldist Perpendicular distance to wall (avoids fisheye)
 * @param stepx Step direction in X (-1 or +1)
 * @param stepy Step direction in Y (-1 or +1)
 * @param hit Wall collision flag (1 when wall hit)
 * @param side Wall orientation (0=vertical, 1=horizontal)
 * @param lineheight Height of wall line to draw on screen
 * @param drawstart Y coordinate to start drawing wall
 * @param drawend Y coordinate to stop drawing wall
 * @param wallx Exact X coordinate where ray hit wall [0, 1]
 * @param texx Texture X coordinate for current wall stripe
 */
typedef struct s_ray
{
	double			camerax;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				lineheight;
	int				drawstart;
	int				drawend;
	double			wallx;
	int				texx;
}	t_ray;

/**
 * @struct s_plane
 * @brief Stores all texture paths, loaded textures, and RGB color values
 * 
 * @param no_texture Path to north wall texture file
 * @param so_texture Path to south wall texture file
 * @param we_texture Path to west wall texture file
 * @param ea_texture Path to east wall texture file
 * @param tex_north Loaded north wall texture
 * @param tex_south Loaded south wall texture
 * @param tex_west Loaded west wall texture
 * @param tex_east Loaded east wall texture
 * @param f_red Floor color red component [0-255]
 * @param f_green Floor color green component [0-255]
 * @param f_blue Floor color blue component [0-255]
 * @param c_red Ceiling color red component [0-255]
 * @param c_green Ceiling color green component [0-255]
 * @param c_blue Ceiling color blue component [0-255]
 * @param ccolor Combined ceiling RGBA color value
 * @param fcolor Combined floor RGBA color value
 */
typedef struct s_plane
{
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	mlx_texture_t	*tex_north;
	mlx_texture_t	*tex_south;
	mlx_texture_t	*tex_west;
	mlx_texture_t	*tex_east;
	int				f_red;
	int				f_green;
	int				f_blue;
	int				c_red;
	int				c_green;
	int				c_blue;
	uint32_t		ccolor;
	uint32_t		fcolor;
}	t_plane;

/**
 * @struct s_data
 * @brief Main data structure containing all game state and resources
 * 
 * @param mlx MLX42 library instance
 * @param img Image buffer for rendering
 * @param map 2D array representing the game map
 * @param map_width Width of the map in tiles
 * @param map_height Height of the map in tiles
 * @param plane Texture and color configuration
 * @param ray Current raycasting calculations
 * @param player Player state and position
 */
typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	char			**map;
	int				map_width;
	int				map_height;
	t_plane			*plane;
	t_ray			*ray;
	t_player		*player;
}	t_data;

/* ************************************************************************** */
/*                               FUNCTION PROTOTYPES                          */
/* ************************************************************************** */

/* ========================================================================== */
/*                                 MLX FUNCTIONS                              */
/* ========================================================================== */

/**
 * @brief Initializes the MLX42 graphics library and sets up the game window
 * @param data Pointer to the main data structure containing all game information
 *
 * Sets up the MLX window, creates the image buffer, initializes player position,
 * creates test map, and starts the main game loop with event handling.
 */
void			init_mlx(t_data *data);

/**
 * @brief Main game loop callback function executed every frame
 * @param param Void pointer to t_data structure (cast internally)
 *
 * Called by MLX42 hook system each frame to update game state.
 * Handles player input, renders the current frame, and updates display.
 */
void			game_loop(void *param);

/**
 * @brief Handles keyboard press events for game control
 * @param keydata Structure containing key press information
 * @param param Void pointer to t_data structure (cast internally)
 *
 * Processes discrete key events (like ESC to exit game).
 * For continuous movement, see handle_movement() in game_loop.
 */
void			handle_keypress(mlx_key_data_t keydata, void *param);

/* ========================================================================== */
/*                             RAYCASTING FUNCTIONS                           */
/* ========================================================================== */

/**
 * @brief Renders a complete frame by casting rays for all screen columns
 * @param data Pointer to main data structure containing all game information
 *
 * First clears background with ceiling/floor colors.
 * Then iterates through all screen columns (x = 0 to SCREEN_W-1).
 * Calls cast_single_ray() for each column to build the complete 3D view.
 * This function creates the entire visible scene from the player's perspective.
 */
void			render_frame(t_data *data);

/**
 * @brief Executes complete raycasting process for a single screen column
 * @param data Pointer to main data structure containing all game information
 * @param x Screen column coordinate (0 to SCREEN_W-1)
 *
 * Orchestrates the full raycasting pipeline:
 * 1. Initialize ray parameters, 2. Calculate DDA setup, 3. Perform wall
 *  detection,
 * 4. Calculate distances and screen boundaries, 5. Draw the resulting wall line.
 */
void			cast_single_ray(t_data *data, int x);

/**
 * @brief Clears the screen by drawing ceiling and floor colors
 * @param data Pointer to main data structure containing image and color info
 *
 * Fills upper half of screen (y < SCREEN_H/2) with ceiling color.
 * Fills lower half of screen (y >= SCREEN_H/2) with floor color.
 * Creates the background before drawing walls on top.
 */
void			clear_background(t_data *data);

/**
 * @brief Draws a vertical line representing a wall column on screen
 * @param data Pointer to main data structure containing image buffer
 * @param x Screen column coordinate (0 to SCREEN_W-1)
 * @param ray Pointer to ray structure with drawing boundaries and wall info
 *
 * Uses textures to draw wall stripe with proper shading.
 * Iterates from drawstart to drawend, sampling texture colors.
 * Uses mlx_put_pixel() to draw individual pixels on the image buffer.
 */
void			draw_vertical_line(t_data *data, int x, t_ray *ray);

/**
 * @brief Determines wall color based on ray direction and applies shading
 * @param ray Pointer to ray structure containing direction and side information
 * @return uint32_t RGBA color value for the wall
 *
 * Assigns different colors based on wall orientation:
 * - North/South walls (side==1): Red (south) or Green (north)
 * - East/West walls (side==0): Blue (east) or Yellow (west)
 * Applies shading: horizontal walls are darker (color >> 1) for depth effect.
 */
uint32_t		get_wall_color(t_ray *ray);

/* ========================================================================== */
/*                           RAY CALCULATION FUNCTIONS                        */
/* ========================================================================== */

/**
 * @brief Initializes a ray for raycasting calculation for a specific screen
 * column
 * @param ray Pointer to ray structure to initialize
 * @param player Pointer to player structure containing position and direction
 * @param x Current screen column (0 to SCREEN_W-1)
 *
 * Calculates: camerax = 2*x/SCREEN_W - 1 (normalizes x to range [-1,1])
 * Calculates ray direction using: dir + plane * camerax (creates FOV effect)
 * Calculates deltadist = |1/raydir| (distance ray travels to cross
 * one grid line)
 */
void			init_ray(t_ray *ray, t_player *player, int x);

/**
 * @brief Calculates step direction and initial side distances for DDA algorithm
 * @param ray Pointer to ray structure to update
 * @param player Pointer to player structure with current position
 *
 * Determines step direction (-1 or +1) based on ray direction sign.
 * Calculates initial sidedist: distance from current position to next grid line.
 * Formula: sidedist = (next_grid_pos - current_pos) * deltadist
 */
void			calculate_step_and_side_dist(t_ray *ray, t_player *player);

/**
 * @brief Performs Digital Differential Analyzer (DDA) algorithm to find wall
 *  collision
 * @param ray Pointer to ray structure containing step and distance information
 * @param map 2D char array representing the game map ('1' = wall, '0' = empty)
 *
 * Iteratively steps through grid cells by choosing shortest sidedist.
 * Updates mapx/mapy coordinates and sidedist values each iteration.
 * Sets 'side' to indicate if wall hit was vertical (0) or horizontal (1).
 * Stops when hitting a wall character ('1').
 */
void			perform_dda(t_ray *ray, char **map);

/**
 * @brief Calculates perpendicular wall distance and screen drawing boundaries
 * @param ray Pointer to ray structure to update with distance calculations
 * @param player Pointer to player structure with current position
 *
 * Calculates perpendicular distance: (wall_pos - player_pos + offset) / raydir
 * This avoids fisheye effect by using perpendicular distance instead of actual
 *  distance.
 * Calculates wall height: SCREEN_H / perpendicular_distance
 * Determines drawstart/drawend: vertical pixel range to draw the wall on screen.
 */
void			calculate_wall_distance(t_ray *ray, t_player *player);

/**
 * @brief Calculates texture X coordinate for the current wall hit
 * @param ray Pointer to ray structure with wall intersection data
 * @param player Pointer to player structure with position information
 * @param texture Pointer to the texture being used for the wall
 *
 * Determines exact horizontal position on texture based on where ray hit wall.
 * Calculates wallx (fractional part of wall position) and maps it to texture.
 */
void			calculate_texture_x(t_ray *ray, t_player *player,
					mlx_texture_t *texture);

/* ========================================================================== */
/*                             PLAYER FUNCTIONS                               */
/* ========================================================================== */

/**
 * @brief Initializes player structure and sets default values
 * @param data Pointer to main data structure containing player information
 *
 * Allocates memory for player structure and initializes position coordinates.
 * Sets initial direction vector and camera plane for proper FOV.
 * Called during game initialization before map parsing.
 */
void			init_player(t_data *data);

/**
 * @brief Sets player direction vector based on map orientation character
 * @param player Pointer to player structure to update
 * @param orientation Character from map ('N', 'S', 'E', 'W')
 *
 * Configures initial direction vector (dir_x, dir_y) based on orientation.
 * Also sets perpendicular camera plane vector for correct field of view.
 * N: faces north (0, -1), S: south (0, 1), E: east (1, 0), W: west (-1, 0)
 */
void			set_player_direction(t_player *player, char orientation);

/**
 * @brief Moves player position with collision detection
 * @param data Pointer to main data structure containing player and map
 * @param move_x X-axis movement delta (can be positive or negative)
 * @param move_y Y-axis movement delta (can be positive or negative)
 *
 * Calculates new position: new_pos = current_pos + move_delta
 * Checks collision by testing if map[new_y][new_x] != '1' (not a wall)
 * Only updates position if the new position is not inside a wall.
 * Updates both floating-point (x_uni/y_uni) and integer (x/y) coordinates.
 */
void			move_player(t_data *data, double move_x, double move_y);

/**
 * @brief Rotates player direction and camera plane by specified angle
 * @param data Pointer to main data structure containing player information
 * @param rot Rotation angle in radians (positive = clockwise)
 *
 * Applies 2D rotation matrix transformation:
 * new_dir_x = old_dir_x * cos(rot) - old_dir_y * sin(rot)
 * new_dir_y = old_dir_x * sin(rot) + old_dir_y * cos(rot)
 * Also rotates the camera plane vector to maintain proper FOV orientation.
 * This creates smooth camera rotation for looking left/right.
 */
void			rotate_player(t_data *data, double rot);

/**
 * @brief Processes continuous keyboard input for player movement and
 *  camera rotation
 * @param data Pointer to main data structure containing MLX and player info
 *
 * Checks key states using mlx_is_key_down() for smooth movement:
 * W/S: Forward/backward movement along direction vector * MOVE_SPEED
 * A/D: Strafe left/right movement along plane vector * MOVE_SPEED
 * LEFT/RIGHT arrows: Camera rotation by ±ROT_SPEED radians
 * All movements include collision detection via move_player().
 */
void			handle_movement(t_data *data);

/* ========================================================================== */
/*                             TEXTURE FUNCTIONS                              */
/* ========================================================================== */

/**
 * @brief Loads all wall textures from files specified in configuration
 * @param data Pointer to main data structure containing texture paths
 *
 * Uses MLX42's mlx_load_png() to load texture images for all four directions.
 * Validates that all textures are successfully loaded.
 * Stores loaded textures in t_plane structure for use during rendering.
 */
void			load_textures(t_data *data);

/**
 * @brief Selects appropriate wall texture based on ray hit direction
 * @param data Pointer to main data structure containing texture pointers
 * @param ray Pointer to ray structure with wall hit information
 * @return mlx_texture_t* Pointer to the appropriate texture for this wall
 *
 * Determines which texture to use based on side and ray direction:
 * Returns north/south/east/west texture depending on which wall face was hit.
 */
mlx_texture_t	*select_texture(t_data *data, t_ray *ray);

/**
 * @brief Retrieves RGBA color value from texture at specified coordinates
 * @param texture Pointer to texture to sample from
 * @param x X coordinate in texture space (0 to texture->width-1)
 * @param y Y coordinate in texture space (0 to texture->height-1)
 * @return uint32_t RGBA color value at the specified texture position
 *
 * Calculates byte offset in texture data: (y * width + x) * bytes_per_pixel
 * Extracts RGBA components from texture's pixel array.
 */
uint32_t		get_texture_color(mlx_texture_t *texture, int x, int y);

/* ========================================================================== */
/*                          PARSER & MAP FUNCTIONS                            */
/* ========================================================================== */

/**
 * @brief Main parser function that reads and validates .cub configuration file
 * @param filecub Path to the .cub file to parse
 * @param data Pointer to main data structure to populate with parsed data
 * @return int 0 on success, 1 on error
 *
 * Opens and reads .cub file line by line.
 * Parses texture paths, RGB colors, and map layout.
 * Validates all configuration elements and map integrity.
 */
int				read_cub(const char *filecub, t_data *data, int fd);

/**
 * @brief Parses texture and color configuration lines from .cub file
 * @param line Current line from file being processed
 * @param data Pointer to main data structure to update
 * @return int 0 on success, 1 on error
 *
 * Identifies line type (NO, SO, WE, EA for textures, F/C for colors).
 * Validates format and stores configuration values in t_plane structure.
 */
int				textures_n_colors(char *line, t_data *data);

/**
 * @brief Parses and validates RGB color values from configuration
 * @param plane Pointer to plane structure containing color strings to parse
 *
 * Converts comma-separated RGB strings to integer values (0-255).
 * Creates uint32_t color values from individual R,G,B components.
 * Stores final colors in fcolor (floor) and ccolor (ceiling) fields.
 */
void			parse_color(t_plane *plane);

/**
 * @brief Reads map section from .cub file and stores as 2D array
 * @param fd File descriptor of open .cub file
 * @param data Pointer to main data structure to store map
 * @return char* Pointer to first line after configuration section
 *
 * Reads all map lines until EOF, allocating memory for each row.
 * Handles variable line lengths and trailing spaces.
 * Returns pointer to first map line for further processing.
 */
char			*read_map_lines(int fd, t_data *data);

/**
 * @brief Calculates map width and height dimensions
 * @param data Pointer to main data structure containing map array
 *
 * Iterates through map array to count rows (height).
 * Finds longest line to determine width.
 * Stores dimensions in map_width and map_height fields.
 */
void			calculate_map_dimensions(t_data *data);

/**
 * @brief Prints map to stdout for debugging purposes
 * @param map 2D char array containing the map
 *
 * Iterates through map rows and prints each line.
 * Used for debugging map parsing and validation issues.
 */
void			print_map_debug(char **map);

/**
 * @brief Validates texture path and assigns to appropriate texture pointer
 * @param texture_ptr Pointer to texture path string to update
 * @param path Texture file path to validate and assign
 * @param name Texture identifier name for error messages
 * @return int 0 on success, 1 on error or duplicate
 *
 * Checks if texture was already defined (prevents duplicates).
 * Validates file path format and accessibility.
 * Assigns path to texture pointer if validation passes.
 */
int				validate_texture(char **texture_ptr, char *path, char *name);

/**
 * @brief Parses and validates single color configuration line
 * @param line Configuration line containing RGB values
 * @param plane Pointer to plane structure to update with colors
 * @param name Color identifier ('F' for floor, 'C' for ceiling)
 * @return int 0 on success, 1 on error or duplicate
 *
 * Validates RGB format (three comma-separated values 0-255).
 * Checks for duplicate color definitions.
 * Stores parsed RGB string in appropriate plane field.
 */
int				parse_color_line(char *line, t_plane *plane, char *name);

/**
 * @brief Validates RGB number string format and range
 * @param str String containing potential RGB value
 * @return int 1 if valid RGB number (0-255), 0 otherwise
 *
 * Checks if string contains only digits.
 * Validates value is in range 0-255.
 */
int				is_valid_rgb_number(char *str);

/**
 * @brief Validates complete RGB line format (R,G,B)
 * @param line String containing RGB values to validate
 * @return int 1 if valid format, 0 otherwise
 *
 * Checks for exactly three comma-separated numeric values.
 * Validates each value is in range 0-255.
 * Ensures no extra characters or spaces.
 */
int				validate_rgb_format(char *line);

/* ========================================================================== */
/*                          MAP VALIDATION FUNCTIONS                          */
/* ========================================================================== */

/**
 * @brief Checks if a map line has walls at both ends (proper closure)
 * @param line String representing a row of the map
 * @return int 1 if properly closed with '1' or ' ', 0 otherwise
 *
 * Verifies first and last non-space characters are walls ('1').
 * Ensures horizontal boundaries of map are solid.
 */
int				closed_line(char *line);

/**
 * @brief Gets first non-space character from a string
 * @param line String to search
 * @return char First non-space character found
 */
char			get_first(char *line);

/**
 * @brief Gets last non-space character from a string
 * @param line String to search
 * @return char Last non-space character found
 */
char			get_last(char *line);

/**
 * @brief Validates that entire map perimeter is properly walled
 * @param map 2D char array representing the game map
 * @return int 0 if valid perimeter, 1 if open edges detected
 *
 * Checks first and last rows are solid walls or spaces.
 * Verifies each row has wall characters at both ends.
 * Ensures no playable area is exposed at map boundaries.
 */
int				check_perimeter(char **map);

/**
 * @brief Checks if character is a player spawn position indicator
 * @param c Character to test
 * @return int 1 if player character ('N','S','E','W'), 0 otherwise
 */
int				is_player(char c);

/**
 * @brief Saves player spawn position to player structure
 * @param player Pointer to player structure to update
 * @param x X coordinate of spawn position
 * @param y Y coordinate of spawn position
 */
void			save_player(t_player *player, int x, int y);

/**
 * @brief Validates player position in map and saves coordinates
 * @param map 2D char array representing the game map
 * @param player Pointer to player structure to update
 * @param i Current Y coordinate in map
 * @param j Current X coordinate in map
 * @return int 0 if valid position, 1 on error
 *
 * Checks that player is in a valid playable area.
 * Ensures player is surrounded by valid tiles (no holes).
 */
int				check_player(char **map, t_player *player, int i, int j);

/**
 * @brief Checks if character is a playable map tile
 * @param c Character to test
 * @return int 1 if playable ('0' or player char), 0 otherwise
 */
int				is_playable(char c);

/**
 * @brief Checks if character is a valid map zone tile
 * @param c Character to test
 * @return int 1 if valid ('0','1',' ', or player), 0 otherwise
 */
int				valid_zone(char c);

/**
 * @brief Validates that a specific map tile is properly enclosed
 * @param map 2D char array representing the game map
 * @param i Y coordinate of tile to check
 * @param j X coordinate of tile to check
 * @return int 0 if valid enclosure, 1 if exposed to void
 *
 * Checks all adjacent tiles (up, down, left, right).
 * Ensures playable tiles are not adjacent to spaces or out-of-bounds.
 */
int				check_zone(char **map, int i, int j);

/**
 * @brief Validates entire map has no holes or improperly enclosed areas
 * @param map 2D char array representing the game map
 * @return int 0 if map is valid, 1 if holes detected
 *
 * Iterates through all playable tiles.
 * Calls check_zone() for each to verify proper enclosure.
 */
int				check_hole(char **map);

/**
 * @brief Validates map has exactly one player and checks all required elements
 * @param map 2D char array representing the game map
 * @param player Pointer to player structure to populate
 * @param plane Pointer to plane structure for validation
 * @return int 0 if valid configuration, 1 on error
 *
 * Ensures exactly one player spawn point exists.
 * Validates player position is in valid playable area.
 * Confirms all required textures and colors are defined.
 */
int				check_instances(char **map, t_player *player, t_plane *plane);

/**
 * @brief Validates all four wall textures are defined
 * @param plane Pointer to plane structure containing texture paths
 * @return int 0 if all textures defined, 1 if any missing
 */
int				check_textures(t_plane *plane);

/**
 * @brief Validates floor and ceiling colors are properly defined
 * @param plane Pointer to plane structure containing color data
 * @return int 0 if colors valid, 1 if any issues
 */
int				check_colors(t_plane *plane);

/**
 * @brief Validates complete configuration (textures + colors)
 * @param plane Pointer to plane structure to validate
 * @return int 0 if all configuration valid, 1 on any error
 *
 * Checks all textures are defined and accessible.
 * Validates floor and ceiling colors are properly set.
 * Comprehensive validation before starting game.
 */
int				check_config(t_plane *plane);

/* ========================================================================== */
/*                            CLEANUP FUNCTIONS                               */
/* ========================================================================== */

/**
 * @brief Frees all allocated memory in data structure
 * @param data Pointer to main data structure to clean up
 *
 * Frees map array, textures, player, plane, and ray structures.
 * Closes MLX window and cleans up graphics resources.
 * Should be called before program exit or on error.
 */
void			cleanup_data(t_data *data);

/**
 * @brief Frees dynamically allocated 2D map array
 * @param map 2D char array to free
 *
 * Iterates through all rows and frees each string.
 * Then frees the array of pointers itself.
 */
void			free_map(char **map);

#endif
