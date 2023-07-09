#include "minishell.h"

void	__env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->variable, env->value);
		env = env->next;
	}
}
