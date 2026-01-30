#include "built_in.h"

int env(struct data *data)
{
	int i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	return (0);
}
