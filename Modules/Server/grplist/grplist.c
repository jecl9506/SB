#include <stdio.h>

#include "../../server.h"
#include "../../group.h"
#include "../../../Common/bool.h"
#include "../../../Common/unix_socket.h"

bool		grplist(t_server *server, t_socket *cm, char *data)
{
	t_group	*tmp = server->groups->next;
	char	*buffer = malloc(sizeof(char) * 64);
	int		nbc = 0;

	//printf("Data: [%s]\n", data);
	tmp = server->groups;
	if (!server->groups)
	{
		if (socket_write(cm, "No groups\n", 10) < 0) {return(false);}
		return(true);
	}
	tmp = server->groups->next;
	if (!tmp)
	{
		if (socket_write(cm, "No groups\n", 10) < 0) {return(false);}
		return(true);
	}

	while (tmp)
	{
		if (tmp->name)
		{
			// Print group name
			if (socket_write(cm, tmp->name, strlen(tmp->name)) < 0) {return(false);}

			// Print separator
			if (socket_write(cm, " (", 2) < 0) {return(false);}

			// Print group os_name
			if (tmp->os_name)
				if (socket_write(cm, tmp->os_name, strlen(tmp->os_name)) < 0) {return(false);}

			// Print separator
			if (socket_write(cm, ", ", 2) < 0) {return(false);}

			// Print group os_version
			if (tmp->os_version)
				if (socket_write(cm, tmp->os_version, strlen(tmp->os_version)) < 0) {return(false);}

			// Print separator
			if (socket_write(cm, ", ", 2) < 0) {return(false);}

			// Print group os_arch
			if (tmp->os_arch)
				if (socket_write(cm, tmp->os_arch, strlen(tmp->os_arch)) < 0) {return(false);}

			// Print end line
			if (socket_write(cm, ")\n", 2) < 0) {return(false);}
		}
		tmp = tmp->next;
	}
	return(true);
}