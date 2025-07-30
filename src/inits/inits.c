#include "../../includes/minishell.h"

char	**ft_copy_envp(char **envp)
{
	int		i;
	int		size;
	char	**ret;

	size = 0;
	i = 0;
	while (envp[size])
		size++;
	ret = safe_calloc((size + 1), sizeof(char *));
	while (i < size && envp[i])
	{
		ret[i] = ft_strdup(envp[i]);
			if (!ret[i])
			{
				free_envp(ret);
				return (NULL);
			}
		i++;
	}
	return (ret);
}
