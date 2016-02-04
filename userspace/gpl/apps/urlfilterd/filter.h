#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WEB_LEN	40
#define MAX_FOLDER_LEN	56
#define MAX_LIST_NUM	100

typedef struct _URL{
	char website[MAX_WEB_LEN];
	char folder[MAX_FOLDER_LEN];
//<< [BCMBG-NTWK-102]  Jim Lin: Fix issue as if web A with port A and web B with port B are only allowed rules in URL filter, web A with port B will get bypassed, 20131018
	char port[MAX_WEB_LEN];
//>> [BCMBG-NTWK-102] end
	struct _URL *next;
}URL, *PURL;

PURL purl = NULL;

unsigned int list_count = 0;

//const char list_to_open[] = "/dan/url_list";

//extern int get_url_info();
//extern void add_entry(char *, char *);

