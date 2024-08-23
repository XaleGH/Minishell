#include "../../inc/minishell.h"

/*
 * Sorts the environment variables alphabetically.
 *
 * This function sorts the given array of environment variables in 
 * alphabetical order
 * using a simple bubble sort algorithm.
 *
 * @param env Pointer to an array of strings containing the 
 * environment variables.
 *
 * @return char**. Returns a pointer to the sorted array of 
 * environment variables.
 */
char	**sort_env(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strncmp(env[i], env[j], 100) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (env);
}

/*
 * Sorts and prints the environment variables in export format.
 *
 * This function creates a copy of the current environment variables, 
 * sorts them,
 * and prints each variable in the format "declare -x var=value".
 *
 * @param data Pointer to a t_data structure containing the environment
 * variables.
 *
 * @return void. The function does not return a value.
 */
void	sort_and_print_export(t_data *data)
{
	char	**env_cpy;
	int		i;

	i = 0;
	env_cpy = dupenv(data->env);
	env_cpy = sort_env(env_cpy);
	while (env_cpy[i])
	{
		printf("declare -x %s\n", env_cpy[i]);
		i++;
	}
}
