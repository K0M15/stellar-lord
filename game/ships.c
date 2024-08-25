/* ######################################## */
/* #                    25.08.2024        # */
/* #  ships.c                             # */
/* #                 written by           # */
/* #                Alain Felger          # */
/* ######################################## */

#include "stellar.h"

t_ship_cluster* send_ships(int ship_amount, t_star* origin, t_star* target, t_game* game)
{
	if (!check_target_range(origin, target))
		return NULL;
	t_ship_cluster *cluster = malloc(sizeof(t_ship_cluster));
	if (cluster == NULL)
		return NULL;
	cluster->amount = ship_amount;
	cluster->cycle_start = game->cycle;
	cluster->origin = origin;
	cluster->target = target;
	cluster->owner = origin->owner;
	return cluster;
}

int check_target_range(t_star* origin, t_star* target)
{
	return (Vector2Distance(origin->position, target->position) < MAX_SHIP_RANGE);
}

t_position get_cluster_pos(t_ship_cluster *cluster, int cycle)
{
	return Vector2Lerp(cluster->origin->position, cluster->target->position,
		SHIP_SPEED * (cycle - cluster->cycle_start)
		/ Vector2Distance(cluster->origin->position, cluster->target->position));
}

t_cluster_list* new_list()
{
	t_cluster_list *list = malloc(sizeof(t_cluster_list));
	if (list == NULL)
		return NULL;
	memset(&(list->data), 0, sizeof(t_ship_cluster));
	list->next = NULL;
}

t_cluster_list* append(t_cluster_list *list, t_ship_cluster data)
{
	t_cluster_list* element = new_list();
	if (element == NULL)
		return NULL;
	element->data = data;
	list->next = element;
	return element;
}

t_cluster_list* remove_if(t_cluster_list* beginn, t_ship_cluster* data ,int(*filter)(t_ship_cluster* cluster, t_ship_cluster* cmp))
{
	t_cluster_list *last = NULL;
	t_cluster_list *current = beginn;
	while (current != NULL)
	{
		if (filter(current, data) && last == NULL)
		{
			beginn= current->next;
			free(current);
			current = beginn;
			continue;
		}
		else if (filter(current, data))
		{
			last->next = current->next;
			free(current);
			current = last->next;
		}
		last = current;
		current = last->next;
	}
	return beginn;
}