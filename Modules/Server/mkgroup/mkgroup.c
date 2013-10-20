#include <stdio.h>
#include <stdlib.h>

#include "../../server.h"
#include "../../cqueue.h"
#include "../../group.h"
#include "../../../Common/bool.h"
#include "../../../Common/unix_socket.h"

#define OS_NAME		0
#define OS_VERSION	1
#define OS_ARCH		2

bool    	parse_info(char *data, t_server *server, t_socket *cm, t_group* new)
{
  	char  	*tmp;
  	char 	**type = NULL;
  	int 	i = 0;

	/*	type = malloc(3 * sizeof(*type));
  	if (!type) {return (1);}
  	type[0] = malloc(126 * sizeof(**type));
  	type[1] = malloc(126 * sizeof(**type));
  	type[2] = malloc(126 * sizeof(**type));
  	if (!type[0]) {return (1);}
  	if (!type[1]) {return (1);}
  	if (!type[2]) {return (1);}*/

	tmp = strtok(data, " \t");
	while (tmp)
	{
		tmp = strtok(NULL, " +:\t");
		if (tmp)
		{
			if (tmp && strcmp("os_name", tmp) == 0)
		  	{
				tmp = strtok(NULL, " +:\t");
				if (tmp) {new->os_name = strdup(tmp);}
			}

			/*else*/ if (tmp && strcmp("os_version", tmp) == 0)
			{
		  		tmp = strtok(NULL, " +:\t");
		  		if (tmp) {new->os_version = strdup(tmp);}
			}

	   		/*else*/ if (tmp && strcmp("os_arch", tmp) == 0)
			{
		  		tmp = strtok(NULL, " +:\t");
		  		if (tmp) {new->os_arch = strdup(tmp);}
			}

	  		/*else
	  		{
	  			printf("ERRRRRRROR\n");
				return (false);
	  		}*/
		}
	}
	//printf("\tos_name = %s\n", new->os_name);
	//printf("Go to print_info\n");
	return (true);
}

/*void			parse_data_attr(char* attr)
{
  char*			os_name = NULL;
  char*			os_arch = NULL;
  char*			os_version = NULL;

  os_name = malloc(sizeof(char) * strlen(attr));
  os_arch = malloc(sizeof(char) * strlen(attr));
  os_version = malloc(sizeof(char) * strlen(attr));
  }*/

bool			mkgroup(t_server *server, t_socket *cm, char *data)
{
	char		*c_name  = NULL;
	char		*c_grp_name  = NULL;
	char		*c_grp_attr = NULL;
	t_group 	*new = NULL;

	//t_cqueue 	*cmd;

	if (!server || !server->groups || !data) {return(true);}

	// Init table
	c_name  = malloc(sizeof(char) * strlen(data));
	c_grp_name  = malloc(sizeof(char) * strlen(data));
	c_grp_attr = malloc(sizeof(char) * strlen(data));
	bzero(c_name, strlen(data));
	bzero(c_grp_name, strlen(data));
	bzero(c_grp_attr, strlen(data));

	// Get datas
	sscanf(data, "%s \"%[^\"]\" %s", c_name, c_grp_name, c_grp_attr);

	//printf("New group: %s\n", c_grp_name);
	//printf("Attributs: %s\n", c_grp_attr);

	//	parse_data_attr(c_grp_attr);

	new = group_new();

	parse_info(data, server, cm, new);

	if (!server->groups)
	  {
	    server->groups = group_new();
	  }
	if (server->groups && new)
	  {
	    new->name=strdup(c_grp_name);
	    group_push(server->groups, new);
	  }
	return(true);
}
