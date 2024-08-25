/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:52:01 by asaux             #+#    #+#             */
/*   Updated: 2024/08/25 11:21:34 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * Extracts the PATH environment variable from the given environment list.
 *
 * This function searches through the environment variables provided in `env` to
 * find the PATH variable. It returns the value of the PATH variable, which is
 * the path to directories where executable files might be located. If the PATH
 * variable is not found, the function returns NULL.
 *
 * @param env A pointer to an array of environment variable strings. Each string
 * is expected to be in the format "KEY=VALUE".
 * @return A pointer to the value of the PATH variable, or NULL if the PATH
 * variable is not found in the environment list.
 */
char	*extract_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

/*
 * Constructs and returns the full path of a command by searching through the
 * directories listed in the PATH environment variable.
 *
 * This function takes a command and a list of environment variables, extracts
 * the PATH variable, and then searches for the command in each directory listed
 * in PATH. It constructs the full path to the command by appending the command
 * name to each directory in PATH and checks if the file exists and is
 * executable. If a valid path is found, it returns the full path; otherwise,
 * it returns NULL.
 *
 * @param cmd A pointer to an array of command arguments, where the first
 * element is the name of the command to find.
 * @param env A pointer to an array of environment variable strings. Each
 * string is expected to be in the format "KEY=VALUE".
 * @param path A pointer to a `t_path` structure where intermediate results such
 * as paths and full paths will be stored.
 * @return A pointer to the full path of the command if found and executable, or
 * NULL if no valid path is found.
 */
char	*get_path(char **cmd, char **env, t_path *path)
{
	int	i;

	i = -1;
	path->cmds = cmd;
	path->allpaths = ft_split(extract_path(env), ':');
	while (path->allpaths[++i])
	{
		path->subpath = ft_strjoin(path->allpaths[i], "/");
		path->goodpath = ft_strjoin(path->subpath, path->cmds[0]);
		free(path->subpath);
		if (access(path->goodpath, F_OK | X_OK) == 0)
		{
			free_array(path->allpaths);
			return (path->goodpath);
		}
		free(path->goodpath);
	}
	free_array(path->allpaths);
	return (NULL);
}

/*
 * Finds the full path to a command by checking if it exists in the current
 * directory or by searching through directories listed in the PATH environment
 * variable.
 *
 * This function first checks if the command (cmd[0]) is accessible and
 * executable in the current directory. If so, it returns the path to the
 * command. If not, it searches through the directories listed in the PATH
 * environment variable to find the command. 
 * If the command is found, it returns the full path; otherwise, it prints an
 * error message and returns NULL.
 *
 * @param cmd A pointer to an array of command arguments. The first element
 * (cmd[0]) is the name of the command to find.
 * @param env A pointer to an array of environment variable strings.
 * Each string is expected to be in the format "KEY=VALUE".
 * @param pathfind A pointer to a string that will be set to the full path of
 * the command.
 * It can be NULL on input, and the function will allocate and set it if
 * necessary.
 * @return A pointer to the full path of the command if found and executable,
 * or NULL if the command is not found. If the command is found, `pathfind` is
 * allocated and set to the full path.
 */
char	*real_pathfind(char **cmd, char **env, char *pathfind)
{
	t_path	*path;

	path = malloc(sizeof(t_path));
	if (access(cmd[0], F_OK | X_OK) == 0)
		pathfind = ft_strdup(cmd[0]);
	else
	{
		pathfind = get_path(cmd, env, path);
		if (!pathfind)
			return (free(path), printf("%s: command not found\n", cmd[0]),
				NULL);
	}
	return (free(path), pathfind);
}

/*
 * Checks if a given command string is a built-in shell command.
 *
 * This function compares the input command string with a predefined list of
 * built-in commands (e.g., `cd`, `echo`, `env`, `export`, `pwd`, `unset`,
 * `exit`). If the command matches any of these built-in commands, the function
 * returns 0. If the command does not match any of these built-ins, it returns
 * 1.
 *
 * @param str The command string to check against the list of built-in commands.
 * @return 0 if the command is a built-in shell command, 1 otherwise.
 */
int	is_builtin(char *str)
{
	if (ft_strncmp_exact(str, "cd", 2) == 0)
		return (0);
	else if (ft_strncmp_exact(str, "echo", 4) == 0)
		return (0);
	else if (ft_strncmp_exact(str, "env", 3) == 0)
		return (0);
	else if (ft_strncmp_exact(str, "export", 6) == 0)
		return (0);
	else if (ft_strncmp_exact(str, "pwd", 3) == 0)
		return (0);
	else if (ft_strncmp_exact(str, "unset", 5) == 0)
		return (0);
	else if (ft_strncmp_exact(str, "exit", 4) == 0)
		return (0);
	return (1);
}

/*
 * Executes a built-in shell command based on the provided command string.
 *
 * This function takes a command string and a data structure as input and
 * determines which built-in shell command to execute based on the command
 * string. It then calls the corresponding built-in function to perform the
 * command's operation.
 *
 * Supported built-in commands:
 * - `cd`: Change directory.
 * - `echo`: Print arguments to the standard output.
 * - `env`: Print the environment variables.
 * - `export`: Set or export environment variables.
 * - `pwd`: Print the current working directory.
 * - `unset`: Remove environment variables.
 * - `exit`: Exit the shell.
 *
 * @param str A pointer to an array of strings where the first element is the
 * command string and the subsequent elements are arguments for the command.
 * @param data A pointer to a data structure containing environment variables
 * and other relevant data needed for the built-in commands.
 */
void	exec_builtin(char **str, t_data *data)
{
	if (ft_strncmp_exact(str[0], "cd", 2) == 0)
		cd_builtin(str, data);
	else if (ft_strncmp_exact(str[0], "echo", 4) == 0)
		echo_builtin(str, data);
	else if (ft_strncmp_exact(str[0], "env", 3) == 0)
		env_builtin(data);
	else if (ft_strncmp_exact(str[0], "export", 6) == 0)
		export_builtin(str, data);
	else if (ft_strncmp_exact(str[0], "pwd", 3) == 0)
		pwd_builtin(data);
	else if (ft_strncmp_exact(str[0], "unset", 5) == 0)
		unset_builtin(str, data);
	else if (ft_strncmp_exact(str[0], "exit", 4) == 0)
		exit_builtin(str, data);
}
