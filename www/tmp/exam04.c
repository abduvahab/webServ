
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void	putstr(int fd, char *s)
{
	write(fd, s, strlen(s));
}

void fatal_e()
{
	putstr(2, "fatal error!");
}


void exec_cmd(char **av, char **env, int *fd, int *p)
{
	pid_t pd;

	if (av && av[0] && env && fd && p)
	{
		if (strcmp(av[0], "cd") == 0)
		{
			if (av[1] == NULL || av[2] != NULL)
			{
				putstr(2, "cd: bad arguments");
				putstr(2, "\n");
			}

			if (chdir(av[1]) != 0)
			{
				putstr(2, "cd: cant change the address");
				putstr(2, av[1]);
				putstr(2, "\n");
			}
		}
	else
	{
	pd = fork();
	if (pd < -1)
		fatal_e();
	if (pd == 0)
	{
		if (*p != -1 )
			dup2(*p, 0);
		if (fd[1] != -1)
			dup2(fd[1], 1);
	//	printf("test 2: %s\n", (av[0]));
		if (execve(av[0], av, env) == -1)
		{
			putstr(2, "error: cant execute the command");
			//printf("test : %s\n", av[0]);
			putstr(2, av[0]);
			putstr(2, "\n");
		}
		exit(0);
	}
	else
	{
		waitpid(pd, 0, 0);
		if (*p != -1 )
		{
			close (*p);
			*p = -1;
		}
		if (fd[1] != -1)
		{
			close(fd[1]);
			fd[1] = -1;
		}
		if (fd[0] != -1)
		{
			*p = fd[0];
			fd[0] = -1;
		}
	}

	}
	}
}

int main(int ac, char **av, char **env)
{
	if (ac > 1)
	{
		int	st = 1;	
		int fd[2] = {-1, -1};
		int p = -1;

		for (int i = 1; av[i]; i++)
		{
			if (strcmp(av[i], "|") == 0 || strcmp(av[i], ";") == 0)
			{
				if (strcmp(av[i], "|") == 0)
				{
					if (pipe(fd) == -1)
						fatal_e();
				}
				av[i] = NULL;
				exec_cmd(av + st, env, fd, &p);
				st = i + 1;
			}
		}
		//printf("test 1: %s\n", *(av + st));
		exec_cmd(av + st, env, fd, &p);
	}
}

/*
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

enum {
	READ,
	WRITE
};
enum {
	CHILD,
};

void	ft_putstr_fd(char *str, int fd) {
	int	len = 0;

	while (str[len])
		len++;
	write(fd, str, len);
}

void	fatal_err() {
	ft_putstr_fd("error: fatal\n", 2);
	exit(1);
}

void	exec_cmd(char **cmd, char **env, int *pipe_fd, int *prev_pipe_read) {
	if (cmd && cmd[0] && env && pipe_fd && prev_pipe_read) {
		if (strcmp(cmd[0], "cd") == 0) {
			if (cmd[1] == NULL || cmd[2] != NULL)
				ft_putstr_fd("error: cd: bad arguments\n", 2);
			else if (chdir(cmd[1]) != 0) {
				ft_putstr_fd("error: cd: cannot change directory to ", 2);
				ft_putstr_fd(cmd[1], 2);
				ft_putstr_fd("\n", 2);
			}
		} else {
			pid_t	pid = fork();
			if (pid == -1)
				fatal_err();
			if (pid == CHILD) {
				if (*prev_pipe_read != -1)
					dup2(*prev_pipe_read, STDIN_FILENO);
				if (pipe_fd[WRITE] != -1)
					dup2(pipe_fd[WRITE], STDOUT_FILENO);
				if (execve(cmd[0], cmd, env) == -1) {
					ft_putstr_fd("error: cannot execute ", 2);
					ft_putstr_fd(cmd[0], 2);
					ft_putstr_fd("\n", 2);
				}
				exit(0);
			} else {
				waitpid(pid, NULL, 0);
				if (*prev_pipe_read != -1) {
					close(*prev_pipe_read);
					*prev_pipe_read = -1;
				}
				if (pipe_fd[WRITE] != -1) {
					close(pipe_fd[WRITE]);
					pipe_fd[WRITE] = -1;
				}
				if (pipe_fd[READ] != -1) {
					*prev_pipe_read = pipe_fd[READ];
					pipe_fd[READ] = -1;
				}
			}
		}
	}
}

int	main(int argc, char **argv, char **env) {
	if (argc > 1) {
		int	start = 1;
		int	pipe_fd[2] = {-1, -1};
		int	prev_pipe_read = -1;

		for (int i = 1; argv[i]; i++) {
			if (strcmp(argv[i], "|") == 0 || strcmp(argv[i], ";") == 0) {
				if (strcmp(argv[i], "|") == 0) {
					if (pipe(pipe_fd) == -1)
						fatal_err();
				}
				argv[i] = NULL;
				exec_cmd(&(argv[start]), env, pipe_fd, &prev_pipe_read);
				start = i + 1;
			}
		}
		exec_cmd(&(argv[start]), env, pipe_fd, &prev_pipe_read);
	}
}*/