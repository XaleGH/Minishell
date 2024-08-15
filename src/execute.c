#include "../inc/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

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

/* void	exec_cmd(char **cmd, char **env)
{
	t_path	*path;
	char	*pathfind;

	path = malloc(sizeof(t_path));
	pathfind = get_path(cmd, env, path);
	if (!pathfind)
	{
		free(path);
		printf("%s: command not found\n", cmd[0]);
		return ;
	}
	if (execve(pathfind, cmd, env) == -1)
	{
		free(pathfind);
		free(path);
		printf("exec error\n");
		return ;
	}
	return;
} */

void	exec_cmd(char **cmd, char **env)
{
	t_path	*path;
	char	*pathfind;
	pid_t pid;
	int status;
	int	exit_status;

	path = malloc(sizeof(t_path));
	if (access(cmd[0], F_OK | X_OK) == 0)
		pathfind = ft_strdup(cmd[0]);
	else
	{
		pathfind = get_path(cmd, env, path);
		if (!pathfind)
		{
			free(path);
			printf("%s: command not found\n", cmd[0]);
			return ;
		}
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) 
	{
		if (execve(pathfind, cmd, env) == -1)
		{
		free(pathfind);
		free(path);
		printf("exec error\n");
		return ;
		}
	}
	else 
	{
		if (waitpid(pid, &status, 0) == -1) 
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status)) 
		{//a supprimer
			exit_status = WEXITSTATUS(status);
			printf("Le processus enfant s'est terminé avec le code de sortie %d\n", exit_status);//a supprimer
		}//a supprimer
		else 
		{//a supprimer
			printf("Le processus enfant ne s'est pas terminé normalement\n");//a supprimer
		}//a supprimer
	}
	return;
}

int	ft_strncmp_exact(char *s1, char *s2, int n)
{
	int	i;

	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	i = 0;
	while ((s1[i] && i < n) || (s2[i] && i < n))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

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
	return(1);
}

void	exec_builtin(char **str, t_data *data)
{
	if (ft_strncmp_exact(str[0], "cd", 2) == 0)
		cd_builtin(str, data);
	else if (ft_strncmp_exact(str[0], "echo", 4) == 0)
		echo_builtin(str);
	else if (ft_strncmp_exact(str[0], "env", 3) == 0)
		env_builtin(data);
	else if (ft_strncmp_exact(str[0], "export", 6) == 0)
		export_builtin(str, data);
	else if (ft_strncmp_exact(str[0], "pwd", 3) == 0)
		pwd_builtin();
	else if (ft_strncmp_exact(str[0], "unset", 5) == 0)
		unset_builtin(str, data);
	else if (ft_strncmp_exact(str[0], "exit", 4) == 0)
		exit_builtin(str, data);
}

void	execute_ms(char **str, t_data *data)
{
	if (!str[0])
		return;
	else if (is_builtin(str[0]) == 0)
		exec_builtin(str, data);
	else
		exec_cmd(str, data->env);
}
