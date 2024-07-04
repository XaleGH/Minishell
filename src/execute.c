#include "../inc/minishell.h"

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
	printf("TEST010\n");
	path->cmds = cmd;
	printf("path1 : %s\n", path->cmds[0]);
	printf("path2 : %s\n", path->cmds[1]);
	printf("TEST020\n");
	path->allpaths = ft_split(extract_path(env), ':');
	printf("TEST030\n");
	while (path->allpaths[++i])
	{
		printf("TEST040\n");
		path->subpath = ft_strjoin(path->allpaths[i], "/");
		printf("TEST050\n");
		path->goodpath = ft_strjoin(path->subpath, path->cmds[0]);
		printf("TEST060\n");
		free(path->subpath);
		printf("TEST070\n");
		if (access(path->goodpath, F_OK | X_OK) == 0)
		{
			printf("TEST080\n");
			free_array(path->allpaths);
			free_array(path->cmds);
			return (path->goodpath);
		}
		printf("TEST090\n");
		free(path->goodpath);
	}
	printf("TEST100\n");
	free_array(path->allpaths);
	free_array(path->cmds);
	return (NULL);
}

void	exec_cmd(char **cmd, char **env)
{
	t_path	*path;
	char	*pathfind;
	//char	**cmd;

	printf("TEST000\n");
	path = malloc(sizeof(t_path));
	printf("TEST001\n");
	pathfind = get_path(cmd, env, path);
	printf("TEST002\n");
	printf("pathfind : %s\n", pathfind);
	//cmd = ft_split(av, ' ');
	if (!pathfind)
	{
		printf("TEST003\n");
		free_array(cmd);
		free(path);
		perror("error. path to command not found");
		//exit(1);
	}
	printf("TEST004\n");
	if (execve(pathfind, cmd, env) == -1)
	{
		printf("TEST015\n");
		free(pathfind);
		printf("TEST025\n");
		//free_array(cmd);
		printf("TEST035\n");
		free(path);
		printf("TEST045\n");
		perror("exec error");
		printf("TEST055\n");
		//exit(1);
	}
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

void	execute_ms(char **str, t_data *data)
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
	//else if (ft_strncmp_exact(str[1], "exit", 4) == 0)
	//	exit_builtin(str, data);
	else
		exec_cmd(str, data->env);
}
