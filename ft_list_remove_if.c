typedef	struct s_list {
	struct s_list *next;
	void	*data;
}	t_list;

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list *cur = *begin_list;
	t_list *remove;

	while(cur && cur->next)
	{
		if ((*cmp)(cur->data, data_ref) == 0)
		{
			remove = cur->next;
			cur->next = cur->next->next;
			free(remove);
		}
		cur = cur->next;
	}
	cur = *begin_list;
	if(cur && (*cmp)(cur->data, data_ref) == 0)
	{
		*begin_list = cur->next;
		free(cur);
	}
}
