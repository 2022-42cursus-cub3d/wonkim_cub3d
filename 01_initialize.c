#include "cub3d.h"

void	ft_initialisation(t_recup *recup)
{
	recup->no = NULL;
	recup->so = NULL;
	recup->we = NULL;
	recup->ea = NULL;
	recup->sp = NULL;
	recup->f = -1;
	recup->c = -1;
	recup->rx = 0;
	recup->ry = 0;
	recup->nblines = 0;
	recup->sizeline = 0;
	recup->map = NULL;
	recup->dx = 0;
	recup->dy = 0;
	recup->multijoueurs = 0;
	recup->lignevide = 0;
	recup->insidemap = 0;
	recup->count = 0;
	recup->sum = 0;
	recup->wrongcharmap = 0;
	ft_init_more(recup);
}
