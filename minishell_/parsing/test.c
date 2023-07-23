// bash-3.2$ e'cho hello
// > 
// bash-3.2$ e'ch'o hello
// hello
// bash-3.2$ e'''ch'o hello
// hello
// bash-3.2$ e""cho hello
// hello
// bash-3.2$ echo "hello"
// hello
// bash-3.2$ echo '"hello"'
// "hello"
// bash-3.2$ echo "'"hello"'"
// 'hello'
// bash-3.2$ echo '"'"hello"'"'
// "hello"
// bash-3.2$ echo ''"'"hello"'"''
// 'hello'
// bash-3.2$ echo '''"'"hello"'"'''
// "hello"
// bash-3.2$ echo ''"'"hello"'"''
// 'hello'



void pipe_search(t_command_d	*t)
{
	int				pos;
	int				ppos;
	t_command_d		*tmp;
	t_command_d		*head;
	int				i;
	int				b;

	b = 0;
	pos = 1;
	tmp = t;
	
	while (tmp)
	{
		
		if (tmp->token == PIPE)
		{
			printf("lbts");
			// ppos = 1;
			// head = t;
			// while (head)
			// {
			// 	printf("lbts");
			// 	if(ppos < pos && head->token == WORD)
			// 	{
			// 		printf("lbts");
			// 		b++;
			// 		break;
			// 	}
			// 	ppos++;
			// 	head = head->next;
			// }
			// while (head)
			// {
			// 	if (ppos > pos && head->token == WORD)
			// 	{
			// 		printf("lbts");
			// 		b++;
			// 		break;
			// 	}
			// 	ppos++;
			// }
			// head = head->next;
			break;
		}
		// if(b < 2)
		// {
		// 	write(1, "ERROR",5);
		// 	exit(1);
		// }
		tmp = tmp->next;
		pos++;	
	}
}