/** \cond 0 */
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include "cJSON.h"
#include <stdlib.h>
/** \endcond */

#include "json_conf.h"

static cJSON *process_json(cJSON *conf, int level);

static cJSON *conf_load_simple(const char *filename)
{
	FILE *fp;
	cJSON *conf;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		//log error
		fprintf(stderr, "fopen(): %m");
		return NULL;
	} 
	conf = cJSON_fParse(fp);
	fclose(fp);

	return conf;
}

static cJSON *process_array(cJSON *conf, int level)
{
	cJSON *after, *curr;

	for (curr=conf->child; curr!=NULL; curr=curr->next) {
		after = process_json(curr, level);
		if (after!=curr) {
			if (curr->prev==NULL) {
				conf->child = after;
			}
			curr = after;
		}
	}
	return conf;
}

static cJSON *process_json(cJSON *conf, int level)
{
	cJSON *load, *fname, *result;

	if (conf==NULL) {
		return NULL;
	}

	if (level>=MAX_LOAD_DEPTH) {
		fprintf(stderr, "Followed \""LOAD_KEYWORD"\" more than %d levels, there might be a loop.\n", MAX_LOAD_DEPTH);
		return conf;
	}
	switch (conf->type) {
		case cJSON_Array:
			return process_array(conf, level);
			break;
		case cJSON_Object:
			fname = cJSON_GetObjectItem(conf, LOAD_KEYWORD);
			if (fname==NULL || fname->type != cJSON_String) {
				return process_array(conf, level);
			}
			load = conf_load_simple(fname->valuestring);
			if (load==NULL) {
				fprintf(stderr, "Load %s failed.\n", fname->valuestring);
				abort();
			}
			load->next = conf->next;
			if (conf->next) {
				conf->next->prev = load;
			}
			load->prev = conf->prev;
			if (conf->prev) {
				conf->prev->next = load;
			}
			if (conf->string) {
				load->string = strdup(conf->string); // FIXME: Should alloc memory by cJSON_malloc().
			} else {
				load->string = NULL;
			}
			result = process_json(load, level+1);
			//cJSON_Delete(conf);
			return result;
			break;
		case cJSON_String:
		case cJSON_Number:
		case cJSON_NULL:
		case cJSON_True:
		case cJSON_False:
			return conf;
			break;
		default:
			fprintf(stderr, "Unknown type: %d\n", conf->type);
			abort();
			return NULL;
			break;
	}
}

cJSON *conf_load(const char *filename)
{
	cJSON *conf ;

	conf = conf_load_simple(filename);
	if (conf==NULL) {
		return NULL;
	}

	return process_json(conf, 1);
}

cJSON *conf_get(const char *name, cJSON *c)
{
	return cJSON_GetObjectItem(c, name);
}

int conf_get_int(const char *name, cJSON *c)
{
	cJSON *tmp;
	if (c==NULL) {
		return -1;
	}
	tmp = cJSON_GetObjectItem(c, name);
	if (tmp) {
		return tmp->valueint;
	}
	return -1;
}
int conf_get_bool(const char *name, cJSON *c)
{
	cJSON *tmp;
	tmp = cJSON_GetObjectItem(c, name);
	if (tmp && tmp->type == cJSON_True) {
		return 1;
	}
	return 0;
}
char *conf_get_str(const char *name, cJSON *c)
{
	cJSON *tmp;
	tmp = cJSON_GetObjectItem(c, name);
	if (tmp) {
		return tmp->valuestring;
	}
	return NULL;
}

int conf_delete(cJSON *conf)
{
	cJSON_Delete(conf);
	return 0;
}

#if UTEST
int main(int argc, char **argv) 
{
	cJSON *conf;

	conf = conf_load(argv[1]);
	printf("Conf Loaded:\n");
	cJSON_fPrint(stderr, conf);
	conf_delete(conf);
	return 0;
}
#endif

