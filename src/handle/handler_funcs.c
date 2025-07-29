#include "../../includes/minishell.h"

void	*safe_malloc(size_t size)
{
	void	*ret;
	ret = malloc(size);
	if (!ret)
		return (NULL);
	return (ret);
}

void	set_bool(bool *val, bool change)
{
	*val = change;
}
