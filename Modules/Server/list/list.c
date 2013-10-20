#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "../../server.h"
#include "../../../Common/bool.h"
#include "../../../Common/unix_socket.h"

#define OS_NAME		0
#define OS_VERSION	1
#define OS_ARCH		2


bool 		print_info(char **type, t_server *server, t_socket *cm)
{
	int 	i = 0;
  	t_clist *c = server->clist->next;
  	bool 	is_client = true;
  	char 	buffer[64];

  	bzero(buffer, 64);
  	//printf("Starting loop\n");
  	while (c)
	{
		//printf("Reloop\n");
	   	is_client = true;
	   	//printf("Checking os_name (%s)\n", c->os_name);
	   	if (/*type[OS_NAME] && */strlen(type[OS_NAME]) > 0)  
	   	{
		   	if (!c->os_name || (c->os_name && strcmp(type[OS_NAME], c->os_name) != 0))
				is_client = false;
			/*else
				printf("not null\n");*/
	   	}
	   	//printf("Checking os_version (%s)\n", c->os_version); 
	   	if (/*type[OS_VERSION] && */strlen(type[OS_VERSION]) > 0)  
	   	{
	   		if (!c->os_version || (c->os_version && strcmp(type[OS_VERSION], c->os_version) != 0))
				is_client = false;
			/*else
				printf("not null\n");*/
	   	}      
	   	//printf("Checking os_arch (%s)\n", c->os_arch);
	   	if (/*type[OS_ARCH] && */strlen(type[OS_ARCH]) > 0)  
	   	{
		   if (!c->os_arch || (c->os_arch && strcmp(type[OS_ARCH], c->os_arch) != 0))
				is_client = false;
			/*else
				printf("not null\n");*/
	   	}
	   	//printf("Checking is_client\n");
	   	if (is_client == true)
	   	{
	   		//printf("Generating return string\n");
			snprintf(buffer, 64, "%d\n", c->ID);
			//printf("Send return string\n");
			if (socket_write(cm, buffer, strlen(buffer)) < 0) {return(false);}
	   	}
	   	c = c->next;
	}
	//printf("Done\n");
  	return (true);
}

bool    parse_info(char *data, t_server *server, t_socket *cm)
{
  	char  *tmp;
  	char  **type = NULL;
  	int   i = 0;

  	type = malloc(3 * sizeof(*type));
  	if (!type || !data || !server || !cm) {return (false);}
  	type[0] = malloc(strlen(data) * sizeof(**type));
  	type[1] = malloc(strlen(data) * sizeof(**type));
  	type[2] = malloc(strlen(data) * sizeof(**type));
  	if (!type[0]) {return (false);}
  	if (!type[1]) {return (false);}
  	if (!type[2]) {return (false);}

	tmp = strtok(data, " \t");
	while (tmp)
	{
		//printf("I'm in a loop !\n");
		tmp = strtok(NULL, " +:\t");
		if (tmp)
		{
			//printf("Main check loop\n");
			if (tmp && strcmp("os_name", tmp) == 0)
		  	{
		  		//printf("  >os_name\n");
				tmp = strtok(NULL, " +:\t");
				if (tmp) {type[OS_NAME] = strdup(tmp);}
			}

			else if (tmp && strcmp("os_version", tmp) == 0)
			{
				//printf("  >os_version\n");
		  		tmp = strtok(NULL, " +:\t");
		  		if (tmp) {type[OS_VERSION] = strdup(tmp);}
			}

	   		else if (tmp && strcmp("os_arch", tmp) == 0)
			{
				//printf("  >os_arch\n");
		  		tmp = strtok(NULL, " +:\t");
		  		if (tmp) {type[OS_ARCH] = strdup(tmp);}
			}

	  		/*else
				return (false);*/
		}
	}
	//printf("Go to print_info\n");
	return(print_info(type, server, cm));
}

bool		list(t_server *server, t_socket *cm, char *data)
{
	t_clist	*tmp = server->clist->next;
	char	*buffer = malloc(sizeof(char) * 64);
	int		nbc = 0;

	//printf("Data: [%s]\n", data);

	// If there is no clients
	if (!tmp)
	{
		if (socket_write(cm, "No clients\n", 11) < 0) {return(false);}
		return(true);
	}

	// Print clients number
	for (nbc = 0; tmp; nbc++)
		tmp = tmp->next;
	snprintf(buffer, 64, "Clients: %d\n", nbc);
	if (socket_write(cm , buffer, strlen(buffer)) < 0) {return(false);}

	// Fetch and print clients listing (if needed)
	//printf("Data: %s\n", data);
	return(parse_info(data, server, cm));
}
