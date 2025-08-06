#include "../../includes/minishell.h"

/**
 * @brief Creates a deep copy of an environment variables array
 * 
 * @param envp Array of environment variable strings to copy (NULL-terminated)
 * @return char** Pointer to the newly allocated copy of the environment array,
 *                or NULL if memory allocation fails
 */
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
//			free_envp(ret);
			return (NULL);
		}
		i++;
	}
	return (ret);
}
