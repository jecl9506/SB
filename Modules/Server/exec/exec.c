#include <stdio.h>
#include <stdlib.h>

#include "../../server.h"
#include "../../cqueue.h"
#include "../../../Common/bool.h"
#include "../../../Common/unix_socket.h"

bool			exec(t_server *server, t_socket *cm, char *data)
{
	char		*c_name  = NULL;
	char		*c_data  = NULL;
	char		*c_group = NULL;

	//t_cqueue 	*cmd;

	if (!server || !server->cqueue || !data) {return(false);}

	// Init table
	c_name  = malloc(sizeof(char) * strlen(data));
	c_data  = malloc(sizeof(char) * strlen(data));
	c_group = malloc(sizeof(char) * strlen(data));
	bzero(c_name, strlen(data));
	bzero(c_data, strlen(data));
	bzero(c_group, strlen(data));

	// Get datas
	sscanf(data, "%s \"%[^\"]\" %s", c_name, c_data, c_group);

	// Building cqueue command - queue version
	/*if (c_data[0] == '\0') {return(true);}
	cmd = cqueue_new();
	if (c_data)
		cmd->command = strdup(c_data);
	if (c_group)
		cmd->group = strdup(c_group);
	cqueue_push(server->cqueue, cmd);*/

	// Building cqueue command - single version
	if (c_data[0] == '\0') {strcpy(c_data, "0");}
	server->cqueue = cqueue_new();
	server->cqueue->command = strdup("exec");
	if (c_data)
		server->cqueue->data = strdup(c_data);
	if (c_group)
		server->cqueue->group = strdup(c_group);

	//printf("server cqueue dump: %s, %s, %s\n", server->cqueue->command, server->cqueue->data, server->cqueue->group);

	// Alert clients threads
	t_clist *tmp;
	for (tmp = server->clist->next; tmp; tmp = tmp->next)
		pthread_kill(tmp->thread, SIGUSR1);

	return(true);
}