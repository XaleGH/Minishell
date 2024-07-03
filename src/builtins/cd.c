#include "../../inc/minishell.h"

/*
 * Retrieves the home directory path from the environment variables.
 *
 * This function searches the environment variables for the "HOME" entry and returns
 * the associated path. If the "HOME" variable is not set, it prints an error message
 * and returns NULL.
 *
 * @param data Pointer to a t_data structure containing the environment variables.
 *
 * @return char*. Returns a pointer to a string containing the home directory path,
 * or NULL if the "HOME" variable is not set.
 */
char	*get_home(t_data *data)
{
	int		i;
	int		j;
	char	*path;
	
	i = 0;
	j = 5;
	path = ft_strdup("");
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "HOME=", 5) == 0)
			break;
		i++;
	}
	if (!data->env[i])
	{
		printf("HOME not set in env");
		return (free(path), NULL);
	}
	path = ft_strjoin(path, &data->env[i][j]);
	return (path);
}

/*
 * Changes the current working directory to the specified path.
 *
 * This function attempts to change the current working directory to the directory
 * specified by the path argument. If the directory does not exist or cannot be accessed,
 * it prints an error message.
 *
 * @param path Pointer to a string containing the path to the directory.
 *
 * @return int. Returns 0 if successful, or 1 if the directory could not be accessed.
 */
int	switch_dir(char *path)
{
	if (chdir(path) == -1)
	{
		printf("cd : %s : no such file or directory\n", path);
		return (1);
	}
	return (0);
}

/*
 * Changes the current directory to the user's home directory.
 *
 * This function retrieves the home directory from the environment and changes the current 
 * directory to the home directory. It also updates the OLD_PWD environment variable with 
 * the previous directory path.
 *
 * @param data Pointer to a t_data structure containing global state, including environment variables.
 * @param old_dir Pointer to a string containing the previous directory path.
 *
 * @return int. Returns 0 if successful, or 1 if the home directory could not be found.
 */
int	go_home(t_data *data, char *old_dir)
{
	char *path;
	
	path = get_home(data);
	if (!path)
	{
		free (path);
		return (1);
	}
	switch_dir(path);
	free(path);
	return (0);
}

/*
 * Updates the specified environment variable with the given directory.
 *
 * This function updates the environment variable specified by var with the directory path
 * provided in dir. It modifies the environment array stored in the data structure.
 *
 * @param dir Pointer to a string containing the directory path.
 * @param var Pointer to a string containing the name of the environment variable to update.
 * @param data Pointer to a t_data structure containing the environment variables.
 *
 * @return void. The function does not return a value.
 */
void	actu_env(char *dir, char *var, t_data *data)
{
	int		i;
	char	*pwd;
	int		var_len;
	
	i = 0;
	var_len = (int)ft_strlen(var);
	pwd = ft_strjoin(var, dir);
	i = search_row(data, var);
	free(data->env[i]);
	data->env[i] = NULL;
	data->env[i] = ft_strdup(pwd);
	free(pwd);
}

/*
 * Executes the internal "cd" command.
 *
 * This function changes the current working directory to the directory specified
 * in the arguments. If no directory is specified, it changes to the home directory.
 * It also updates the OLD_PWD and PWD environment variables.
 *
 * @param args Pointer to an array of strings containing the command's arguments.
 * @param data Pointer to a t_data structure containing global state, including environment variables.
 *
 * @return void. The function does not return a value.
 */
void	cd_builtin(char **args, t_data *data)
{
	char	*old_dir;
	char	*cur_dir;

	old_dir = NULL;
	cur_dir = NULL;
	old_dir = getcwd(old_dir, 0);
	if (!args[1])
	{
		if (go_home(data, old_dir) == 1)
			return ;
	}
	else
	{
		if (switch_dir(args[1]) == 1)
		{
			free(old_dir);
			return ;
		}
	}
	cur_dir = getcwd(cur_dir, 0);
	actu_env(old_dir, "OLDPWD=", data);
	actu_env(cur_dir, "PWD=", data);
	free(old_dir);
	free(cur_dir);
}
