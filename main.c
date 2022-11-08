#include "main.h"

char *old_dir;
char *curr_dir;
char *home;
char *shell_name;
/**
 * main - main function
 * @argc: argument count
 * @argv: array of argument strings
 * @env: environment variables
 * Return: 0 on success
 */
int main(int argc __attribute_maybe_unused__, char **argv __attribute_maybe_unused__, char **env __attribute_maybe_unused__)
{
	/* home = _getenv("HOME", env); */

	char *cmd;
	char **args;

	home = _getenv("HOME");
	shell_name = argv[0];
	while (1)
	{
		write(STDOUT_FILENO, "$ ", 3);
		cmd = read_cmd();
		if (!cmd)
			continue;
		args = split_lines(cmd, " \t\r\n");
		exec_cmd(args, env);
		free(args);
		free(cmd);
	}

	return (0);
}

/* TODO - incorrect commands more than two letters gives malloc error */

char *_getenv(char *search_path)
{
	int i = 0;
	char *s = NULL;
	char *a = NULL;
	char **stri = NULL;
	int found = 0;

	while (environ[i])
	{
		a = strdup(environ[i]);
		stri = split_lines(a, "=");
		s = stri[0];

		if (strcmp(search_path, s) == 0)
		{
			found = 1;
			break;
		}
		i++;
	}

	if (found == 1)
	{
		char **str = split_lines(a, "=");

		s = str[1];
	}
	else
		return (NULL);

	return (s);
}
