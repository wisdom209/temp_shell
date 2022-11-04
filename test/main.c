#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char **split_lines(char *cmd, char *delimiters);

int main(int argc, char **argv, char **env)
{
	int i = 0, size = 0;
	char *s;
	while (env[size])
		size++;

	while (env[i])
	{
		s = strtok(env[i], "=");
		if (strcmp("PATH", s) == 0)
			break;
		i++;
	}
	s = strtok(NULL, "=");

	char **paths = split_lines(s, ":");
	
	i = 0;
	while (paths[i])
	{
		char *s = strcat(paths[i], "/code");
		if (access(s, F_OK) != -1 && access(s, X_OK) != -1)
		{
			printf("%s\n", paths[i]);
			break;
		}

		i++;
	}

	return (0);
}

char **split_lines(char *cmd, char *delimiters)
{

	char **tokens = malloc(sizeof(cmd) * 2048);
	char *token = strtok(cmd, delimiters);
	int pos = 0;

	if (!tokens)
		exit(1);

	while (token != NULL)
	{
		tokens[pos] = token;
		pos++;
		token = strtok(NULL, delimiters);
	}
	tokens[pos] = NULL;

	return (tokens);
}
