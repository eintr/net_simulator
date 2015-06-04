/********************************************************
 *  Sorry, no garbage infomations here.
 *  Lisence: read the LISENCE file,
 *  Author(s): read the AUTHOR file and the git commit log,
 *  Code history: read the git commit log.
 *  That's all.
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "json_conf.h"
#include "server.h"
#include "client.h"

static char *config_file;

static void parse_args(int argc, char **argv)
{
	int c;

	do {
		c=getopt(argc, argv, "c:");
		switch (c) {
			case 'c':
				config_file = optarg;
				break;
			default:
				break;
		}
	} while (c!=-1);

	if (config_file==NULL) {
		fprintf(stderr, "Usage:!!\n");
		abort();
	}
}

#define	BUFSIZE	1024

int
main(int argc, char **argv)
{
	cJSON *conf;
	char *mode;

	parse_args(argc, argv);

	conf = conf_load(config_file);
	if (conf==NULL) {
		fprintf(stderr, "Load config failed.\n");
		exit(1);
	}

	mode = conf_get_str("Mode", conf);
	if (mode==NULL) {
		fprintf(stderr, "Must define Mode in config file!\n");
		exit(1);
	}
	if (strcmp(mode, "server")==0) {
		server(conf);
	} else if (strcmp(mode, "client")==0) {
		client(conf);
	} else {
		fprintf(stderr, "Mode is neither server nor client!\n");
		exit(1);
	}

	return 0;
}

