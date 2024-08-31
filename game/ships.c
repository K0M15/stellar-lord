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
	origin->ships -= ship_amount;
	cluster->cycle_start = game->cycle;
	cluster->origin = origin;
	cluster->target = target;
	cluster->owner = origin->owner;
	append(&game->clusters, *cluster); //rename this!
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
	return list;
}

t_cluster_list* append(t_cluster_list **list, t_ship_cluster data)
{
	t_cluster_list* element = new_list();
	t_cluster_list* buffer = *list;
	if (element == NULL)
		return NULL;
	element->data = data;
	if (*list == NULL)
	{
		*list = element;
		return element;
	}
	while (buffer->next)
		buffer = buffer->next;
	buffer->next = element;
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

void game_handle_clusters(t_game* game)
{
	t_cluster_list* list = game->clusters;
	t_cluster_list* last = NULL;
	while (list != NULL)
	{
		if (list->data.cycle_start +
			Vector2Distance(list->data.origin->position,
				list->data.target->position) / SHIP_SPEED < game->cycle)
		{
			if (list->data.target->owner != NULL)
				if (list->data.target->owner == list->data.owner)
					list->data.target->ships += list->data.amount;
				else
					execute_war(&list->data);
			else
				list->data.target->owner = list->data.owner;
			if (last != NULL)
			{
				last->next = list->next;
				free(list);
				list = last->next;
				continue;
			}
			else
			{
				game->clusters = list->next;
				free(list);
				if (game->clusters == NULL)
					list = NULL;
				else
					list = game->clusters->next;
				continue;
			}
		}
		last = list;
		list = list->next;
	}
}
