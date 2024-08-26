/* ######################################## */
/* #                    24.08.2024        # */
/* #  stellar.h                           # */
/* #                 written by           # */
/* #                Alain Felger          # */
/* ######################################## */

#include "stellar.h"

int create_game(t_game* game, int amount_players, int amount_stars)
{
    game->players = malloc(sizeof(t_player) * amount_players);
    if (game->players == NULL)
        return 0;
    game->players_alloc = amount_players;
    game->players_filled = 0;
    game->stars = malloc(sizeof(t_star) * amount_stars);
    if (game->stars == NULL)
        return 0;
    game->stars_alloc = amount_stars;
    game->stars_filled = 0;
    game->cycle = 0;
#ifdef USE_STD_SEED
    game->seed = USE_STD_SEED;
#else
    game->seed = time(0);
#endif // USE_STD_SEED
    game_create_stars(game, SCREEN_WIDTH, SCREEN_HEIGHT);
    return 1;
}

void cycle_game(t_game* game)
{
    // do ship stuff
    for (int i = game->stars_filled; i; --i)
    {
        cycle_star(&game->stars[i]);
    }
    game->cycle++;
}

void game_create_stars(t_game* game, float max_width, float max_height)
{

    int stars_created = 0;
    t_position pos;
    srand(game->seed);

    while (stars_created < game->stars_alloc)
    {
        pos.x = (float)fmod((float)rand(), max_width);
        pos.y = (float)fmod((float)rand(), max_height);
        generate_star(&game->stars[stars_created], pos, (float)(rand() % 1500));
        stars_created++;
    }
    //TODO: Decide what to do with to close stars.
    //Posible replacement would be a galaxy creation tool
    game->stars_filled = stars_created;
}

t_player* game_request_player(t_game* game, char* player_name)
{
    // check if a new player is possible
    if (game->players_filled >= game->players_alloc)
        return NULL;
    t_player* player = &game->players[game->players_filled];
    player->name = strdup(player_name);
    // get a possible star, far away from other people
    t_star* star;
    get_new_homestar(game, &star);
    // set the population to HOMESTAR_START_POPULATION
    star->owner = player;
    star->population = HOMESTAR_START_POPULATION;
    star->ships = 1;
    // pick a color, return player handle.
    player->color = player_colors[game->players_filled % PLAYER_COLOR_AMOUNT];
    game->players_filled++;
}

void game_remove_player(t_game* game, t_player* player)
{ 
    assert(0);
}

void destroy_game(t_game* game)
{
    free(game->players);
    free(game->stars);
}

void game_display_game_stats(t_game* game)
{
    printf("Players:            %d\n", game->players_filled);
    printf("Stars:              %d\n", game->stars_filled);
    printf("Seed:               %d\n", game->seed);
}

void game_display_star_stats(t_game* game)
{
    for (int i = game->stars_filled; i + 1; --i)
    {
        log_star(&game->stars[i]);
    }
}

void game_display_all_stats(t_game* game)
{
    printf("# # # # # GAME  # # # # #\n");
    game_display_game_stats(game);
    printf("# # # # # STARS # # # # #\n");
    game_display_star_stats(game);
    printf("# # # # # PLAYR # # # # #\n");
}