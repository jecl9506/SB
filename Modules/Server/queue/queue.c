#include <stdio.h>
#include <stdlib.h>

#include "../../server.h"
#include "../../cqueue.h"
#include "../../../Common/bool.h"
#include "../../../Common/unix_socket.h"

bool			queue(t_server *server, t_socket *cm, char *data)
{
	t_cqueue	*tmp;
	char		*buffer = malloc(sizeof(char) * 126);

	if (!server || !server->cqueue) {return(false);}
	tmp = server->cqueue->next;

	// Print the number of action (?)
	// Print the list
	if (!tmp)
	{
		if (socket_write(cm, "Queue empty\n", 12) < 0)
			return(false);
	}
	while (tmp)
	{
		bzero(buffer, 126);
		snprintf(buffer, 126, "ID: %d\nCommand: %s\nGroup: %s\n---\n", tmp->ID, tmp->command, tmp->group);
		if (socket_write(cm, buffer, strlen(buffer)) < 0)
			return(false);
		tmp = tmp->next;
	}
	return(true);
}