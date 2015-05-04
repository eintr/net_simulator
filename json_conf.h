#ifndef JSON_CONF_H
#define JSON_CONF_H

/**
	\file gen_conf.h
		\brief Generic json configure file processing.
*/
/** \cond 0 */
#include "cJSON.h"
/** \endcond */

#define	MAX_LOAD_DEPTH	16

#define LOAD_KEYWORD    "load_json"

cJSON *conf_load(const char *filename);

/**
	\fn	int conf_delete(cJSON *)
		\brief Destroy the internal global configure struct.
*/
int conf_delete(cJSON *);

cJSON *conf_get(const char *, cJSON *);

#define	conf_get_int(NAME, JSON) cJSON_GetObjectItem(JSON, NAME)->valueint
#define	conf_get_double(NAME, JSON) cJSON_GetObjectItem(JSON, NAME)->valuedouble
#define	conf_get_str(NAME, JSON) cJSON_GetObjectItem(JSON, NAME)->valuestring
#define	conf_get_bool(NAME, JSON) (cJSON_GetObjectItem(JSON, NAME)->type==cJSON_True)

#endif

