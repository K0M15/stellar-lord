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
# include <ui.h>

# define MAX_SHIP_RANGE         100.0
# define SHIP_SPEED             2.0

# define POPULATION_FACTOR          0.00003
# define MAX_POPULATION_START       150
# define HOMESTAR_START_POPULATION  20
# define MAX_POPULATION             1000

# define USE_STD_SEED           0xAFFEAFFE
# define GAME_NAME              "Stellar Lord"
# define MIN_PLAYER_HOME_DIST   250

# define SCREEN_WIDTH            800*2
# define SCREEN_HEIGHT           600*2

struct s_player;

typedef Vector2 t_position;


# define PLAYER_COLOR_AMOUNT    7
static const Color player_colors[PLAYER_COLOR_AMOUNT] = {
    { 230, 41, 55, 255 },
    { 0, 158, 147, 255 },
    { 0, 141, 241, 255 },
    { 255, 203, 0, 255 },
    { 135, 60, 190, 255 },
    { 255, 109, 194, 255 },
    { 127, 106, 79, 255 },
};

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

typedef struct s_ship_cluster
{
    int             amount;
    t_player        *owner;
    t_star          *origin;
    t_star          *target;
    unsigned long   cycle_start;
}   t_ship_cluster;

typedef struct s_cluster_list
{
    t_ship_cluster         data;
    struct s_cluster_list*  next;
}   t_cluster_list;

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
    t_cluster_list* clusters;
    t_ui*           ui;
    t_star*         selected_star;
}   t_game;


t_star*     generate_star(t_star* star, t_position pos, float population);
void        cycle_star(t_star* star);
void        destruct_star(t_star* star);
void        log_star(t_star* star);
void        set_owner(t_star* star, t_player* player);
void        get_new_homestar(t_game* game, t_star** star);

int         create_game(t_game* game, int amount_players, int amount_stars);
void        cycle_game(t_game* game);
void        game_create_stars(t_game* game, float max_width, float max_height);
t_player*   game_request_player(t_game* game, char* player_name);
void        destroy_game(t_game* game);
void        game_display_all_stats(t_game* game);

t_ship_cluster* send_ships(int ship_amount, t_star* origin, t_star* target, t_game* game);
int             check_target_range(t_star* origin, t_star* target);
t_cluster_list* new_list();
t_cluster_list* append(t_cluster_list** list, t_ship_cluster data);
t_cluster_list* remove_if(t_cluster_list* beginn, t_ship_cluster* data, int(*filter)(t_ship_cluster* cluster, t_ship_cluster* cmp));
t_position      get_cluster_pos(t_ship_cluster* cluster, int cycle);

void    draw_star(t_star *star);
int     calc_star_size(t_star* star);
void    draw_button(t_button* button);
void    draw_ship_cluster(t_ship_cluster* cluster);

void    execute_war(t_ship_cluster *cluster);

void        handle_click(t_game *game);
t_star*     get_star_by_pos(t_game* game, Vector2 click);

char*   strdup(const char* src);
void    memset(void* data, char elem, unsigned int size);

t_game* get_game();
#endif /* STELLAR_H */
