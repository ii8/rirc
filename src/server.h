#ifndef SERVER_H
#define SERVER_H

#include <time.h>

#include "rirc.h"

#include "buffer.h"
#include "channel.h"
#include "mode.h"

//TODO: replaced by mode.c
/* [a-zA-Z] */
#define MODE_LEN 26 * 2

struct server
{
	//TODO: strdup this. Remove arbitrary NICKSIZE
	char nick[NICKSIZE + 1];
	//TODO: can be grouped together, autonick
	char *nicks;
	char *nptr;
	char *host;
	char *port;
	//TODO: this shouldn't persist with the server,
	// its only relevant on successful connection
	char *join;
	//TODO: reaplced by mode.c -> struct usermode
	char usermodes[MODE_SIZE]; /* TODO: replacing with struct mode, struct mode_str */
	struct user_list ignore;
	//TODO channel_list
	struct channel *channel;
	//TODO:
	struct server *next;
	struct server *prev;
	//TODO: connection stuff
	char input[BUFFSIZE];
	char *iptr;
	int pinging;
	int soc;
	time_t latency_delta;
	time_t latency_time;
	time_t reconnect_delta;
	time_t reconnect_time;
	void *connecting;
	//TODO: WIP
	struct channel_list clist;
	struct mode_config mode_config;
};

struct server_list
{
	struct server *head;
};

void server_set_004(struct server*, char*);
void server_set_005(struct server*, char*);

struct server* server(char*, char*, char*);

struct server* server_add(struct server_list*, struct server*);
struct server* server_get(struct server_list*, struct server*);
struct server* server_del(struct server_list*, struct server*);

//TODO
void server_free(struct server*);

#endif
