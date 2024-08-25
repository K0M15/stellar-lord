/* ######################################## */
/* #                    23.08.2024        # */
/* #  stellar.h                           # */
/* #                 written by           # */
/* #                Alain Felger          # */
/* ######################################## */

#ifndef STELLAR_H
# define STELLAR_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <assert.h>
# include <raylib.h>
# include <raymath.h>

# define MAX_SHIP_RANGE         10.0
# define SHIP_SPEED             2.0
# define POPULATION_FACTOR      0.003
# define MAX_POPULATION_START   150
# define USE_STD_SEED           0xAFFEAFFE
# define GAME_NAME              "Stellar Lord"

# define SCREEN_WIDTH            800*2
# define SCREEN_HEIGHT           600*2

struct s_player;

typedef Vector2 t_position;

typedef struct s_star
{
    t_position      position;
    float           population;
    unsigned int    ships;
    struct s_player* owner;
}   t_star;


typedef struct s_action_item
{
    struct s_action_item* next;
    t_star* from;
    t_star* to;
    int* amount;
}   t_action;

// Linked list 
typedef struct s_action_log
{
    struct s_action_item* first;
    struct s_action_item* last;
}   t_action_log;

enum e_player_type
{
    AI,
    HUMAN
};

typedef struct s_player
{
    t_star              *home;
    char                *name;
    Color               color;
    enum e_player_type  type;
}   t_player;

typedef struct s_game
{
    t_player* players;
    int             players_filled;
    int             players_alloc;
    t_star*         stars;
    int             stars_filled;
    int             stars_alloc;
    int             seed;
    unsigned long   cycle;
}   t_game;

typedef struct s_ship_cluster
{
    int             amount;
    t_player        *owner;
    t_star          *origin;
    t_star          *target;
    unsigned long   cycle_start;
}   t_ship_cluster;

t_star*     generate_star(t_star* star, t_position pos, float population);
void        cycle_star(t_star* star);
void        destruct_star(t_star* star);
void        log_star(t_star* star);
void        set_owner(t_star* star, t_player* player);


int         create_game(t_game* game, int amount_players, int amount_stars);
void        cycle_game(t_game* game);
void        game_create_stars(t_game* game, float max_width, float max_height);
t_player*   game_request_player(t_game* game, char* player_name);
void        destroy_game(t_game* game);
void        game_display_all_stats(t_game* game);

t_ship_cluster* send_ships(t_star* origin, t_star* target, t_game* game);
int             check_cluster_target_range(t_star* origin, t_star* target);

void    draw_star(t_star *star);
int     calc_star_size(t_star* star);

void        handle_click(t_game *game);
t_star*     get_star_by_pos(t_game* game, Vector2 click);

#endif /* STELLAR_H */
