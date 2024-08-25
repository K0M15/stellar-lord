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

# define POPULATION_FACTOR      0.003
# define MAX_POPULATION_START   1500
# define USE_STD_SEED           0xAFFEAFFE
# define GAME_NAME              "Stellar Lord"

#define SCREEN_WIDTH            800
#define SCREEN_HEIGHT           600

struct s_player;

typedef struct s_position
{
    float   x;
    float   y;
}   t_position;


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

typedef struct s_player
{
    t_star* home;
    char* name;
    int         color;
}   t_player;

typedef struct s_game {
    t_player* players;
    int         players_filled;
    int         players_alloc;
    t_star* stars;
    int         stars_filled;
    int         stars_alloc;
    int         seed;
}   t_game;

typedef struct s_ship_cluster {
    int         amount;
    t_player    owner;
    t_star      origin;
    t_star      target;
}   s_ship_cluster;

t_star* generate_star(t_star* star, t_position pos, float population);
void cycle_star(t_star* star);
void destruct_star(t_star* star);
void display_star(t_star* star);
void set_owner(t_star* star, t_player* player);


void create_game(t_game* game, int amount_players, int amount_stars);
void cycle_game(t_game* game);
void game_create_stars(t_game* game, float max_width, float max_height);
t_player* game_request_player(t_game* game, char* player_name);
void destroy_game(t_game* game);
void game_display_all_stats(t_game* game);

#endif /* STELLAR_H */
