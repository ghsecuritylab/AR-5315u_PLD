#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <linux/netfilter.h>
#include <libnetfilter_queue/libnetfilter_queue.h>
#include <syslog.h>
#include "filter.h"

#define BUFSIZE 2048

// turn on the urlfilterd debug message.
// #define UFD_DEBUG 1

typedef enum
{
	PKT_ACCEPT,
	PKT_DROP
}pkt_decision_enum;

struct nfq_handle *h;
struct nfq_q_handle *qh;
char listtype[8];

//<< [BCMBG-NTWK-102]  Jim Lin: Fix issue as if web A with port A and web B with port B are only allowed rules in URL filter, web A with port B will get bypassed, 20131018
#if 0
void add_entry(char *website, char *folder)
#else
void add_entry(char *website, char *folder, char *port)
#endif
//>> [BCMBG-NTWK-102] end
{
	PURL new_entry, current, prev;
	new_entry = (PURL) malloc (sizeof(URL));
	strcpy(new_entry->website, website);
	strcpy(new_entry->folder, folder);
//<< [BCMBG-NTWK-102]  Jim Lin: Fix issue as if web A with port A and web B with port B are only allowed rules in URL filter, web A with port B will get bypassed, 20131018
	strcpy(new_entry->port, port);
//>> [BCMBG-NTWK-102] end	
	new_entry->next = NULL;

	if (purl == NULL)
	{
		purl = new_entry;
	}
	else 
	{
		current = purl;
		while (current) 
		{
			prev = current;
			current = current->next;
		}
		prev->next = new_entry;
	}
}

int get_url_info()
{
	char temp[MAX_WEB_LEN + MAX_FOLDER_LEN], *temp1, *temp2, web[MAX_WEB_LEN], folder[MAX_FOLDER_LEN];
//<< [BCMBG-NTWK-102]  Jim Lin: Fix issue as if web A with port A and web B with port B are only allowed rules in URL filter, web A with port B will get bypassed, 20131018
   char *ptr1;
//>> [BCMBG-NTWK-102] end
	FILE *f = fopen("/var/url_list", "r");
	if (f != NULL){
	   while (fgets(temp,96, f) != '\0')
	   {
//<< [BCMBG-NTWK-102]  Jim Lin: Fix issue as if web A with port A and web B with port B are only allowed rules in URL filter, web A with port B will get bypassed, 20131018
               if(ptr1=strstr(temp,"###"))
               {
                  *ptr1 = '\0';
                   ptr1+=3;
                }
//>> [BCMBG-NTWK-102] end		
		if (temp[0]=='h' && temp[1]=='t' && temp[2]=='t' && 
			temp[3]=='p' && temp[4]==':' && temp[5]=='/' && temp[6]=='/')
		{
			temp1 = temp + 7;	
		}
		else
		{
			temp1 = temp;	
		}

		if ((*temp1=='w') && (*(temp1+1)=='w') && (*(temp1+2)=='w') && (*(temp1+3)=='.'))
		{
			temp1 = temp1 + 4;
		}

		if ((temp2 = strchr(temp1, '\n')))
		{
			*temp2 = '\0';
		}
		       
		sscanf(temp1, "%[^/]", web);		
		temp1 = strchr(temp1, '/');
		if (temp1 == NULL)
		{
			strcpy(folder, "\0");
		}
		else
		{
			strcpy(folder, ++temp1);		
		}
//<< [BCMBG-NTWK-102]  Jim Lin: Fix issue as if web A with port A and web B with port B are only allowed rules in URL filter, web A with port B will get bypassed, 20131018
#if 0
		add_entry(web, folder);
#else
		add_entry(web, folder, ptr1);
#endif
//>> [BCMBG-NTWK-102] end
		list_count ++;
	   }
	   fclose(f);
	}
#ifdef UFD_DEBUG
	else {
	   printf("/var/url_list isn't presented.\n");
	   return 1;
	}
#endif


	return 0;
}

static int pkt_decision(struct nfq_data * payload)
{
	char *data;
	char *match, *folder, *url;
	PURL current;
	int payload_offset, data_len;
	struct iphdr *iph;
	struct tcphdr *tcp;
//<< [BCMBG-NTWK-102]  Jim Lin: Fix issue as if web A with port A and web B with port B are only allowed rules in URL filter, web A with port B will get bypassed, 20131018
	char *portPtr=NULL;
//>> [BCMBG-NTWK-102] end
	match = folder = url = NULL;

	data_len = nfq_get_payload(payload, &data);
	if( data_len == -1 )
	{
#ifdef UFD_DEBUG
	printf("data_len == -1!!!!!!!!!!!!!!!, EXIT\n");
#endif
		exit(1);
	}
#ifdef UFD_DEBUG
	printf("data_len=%d ", data_len);
#endif

	iph = (struct iphdr *)data;
	tcp = (struct tcphdr *)(data + (iph->ihl<<2));

	payload_offset = ((iph->ihl)<<2) + (tcp->doff<<2);
	match = (char *)(data + payload_offset);

	if(strstr(match, "GET ") == NULL && strstr(match, "POST ") == NULL && strstr(match, "HEAD ") == NULL)
	{
#ifdef UFD_DEBUG
	printf("****NO HTTP INFORMATION!!!\n");
#endif
		return PKT_ACCEPT;
	}

#ifdef UFD_DEBUG
	printf("####payload = %s\n\n", match);
#endif

	for (current = purl; current != NULL; current = current->next)
	{
		if (current->folder[0] != '\0')
		{
			folder = strstr(match, current->folder);
		}

		if ( (url = strstr(match, current->website)) != NULL ) 
		{
			if (strcmp(listtype, "Exclude") == 0) 
			{
//<< [BCMBG-NTWK-102]  Jim Lin: Fix issue as if web A with port A and web B with port B are only allowed rules in URL filter, web A with port B will get bypassed, 20131018
#if 1
				if (atoi(current->port) != 80)
				{
					char buf[12];
					sprintf(buf,":%s",current->port);
					portPtr=strstr(match,buf);
				}
				else
					portPtr=match;
				
				if (((folder != NULL) || (current->folder[0] == '\0') )&&(portPtr))
#else
				if ( (folder != NULL) || (current->folder[0] == '\0') )
#endif
//>> [BCMBG-NTWK-102] end
				{
#ifdef UFD_DEBUG
					printf("####This page is blocked by Exclude list!");
#endif
					return PKT_DROP;
				}
				else 
				{
#ifdef UFD_DEBUG
					printf("###Website hits but folder no hit in Exclude list! packets pass\n");
#endif
					return PKT_ACCEPT;
				}
			}
			else 
			{
//<< [BCMBG-NTWK-102]  Jim Lin: Fix issue as if web A with port A and web B with port B are only allowed rules in URL filter, web A with port B will get bypassed, 20131018
#if 1
				if (atoi(current->port) != 80)
				{
					char buf[12];
					sprintf(buf,":%s",current->port);
					portPtr=strstr(match,buf);
				}
				else
					portPtr=match;
				
				if (((folder != NULL) || (current->folder[0] == '\0') )&&(portPtr))
//<< [BCMBG-NTWK-102-1] JimLin: add more detailed descirption, 20131108
//				if (((folder != NULL) || (current->folder[0] == '\0') )&&(portPtr))
//>> [BCMBG-NTWK-102-1] end
#else
				if ( (folder != NULL) || (current->folder[0] == '\0') )
#endif
//>> [BCMBG-NTWK-102] end
				{
#ifdef UFD_DEBUG
					printf("####This page is accepted by Include list!");
#endif
					return PKT_ACCEPT;
				}
				else 
				{
#ifdef UFD_DEBUG
					printf("####Website hits but folder no hit in Include list!, packets drop\n");
#endif
					return PKT_DROP;
				}
			}
		}
	}

	if (url == NULL) 
	{
		if (strcmp(listtype, "Exclude") == 0) 
		{
#ifdef UFD_DEBUG
			printf("~~~~No Url hits!! This page is accepted by Exclude list!\n");
#endif
			return PKT_ACCEPT;
		}
		else 
		{
#ifdef UFD_DEBUG
			printf("~~~~No Url hits!! This page is blocked by Include list!\n");
#endif
			return PKT_DROP;
		}
	}

#ifdef UFD_DEBUG
	printf("~~~None of rules can be applied!! Traffic is allowed!!\n");
#endif
	return PKT_ACCEPT;
}


/*
 * callback function for handling packets
 */
static int cb(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg,
	      struct nfq_data *nfa, void *data)
{
	struct nfqnl_msg_packet_hdr *ph;
	int decision, id=0;

	ph = nfq_get_msg_packet_hdr(nfa);
	if (ph)
	{
		id = ntohl(ph->packet_id);
	}

	/* check if we should block this packet */
	decision = pkt_decision(nfa);
	if( decision == PKT_ACCEPT)
	{
		return nfq_set_verdict(qh, id, NF_ACCEPT, 0, NULL);
	}
	else
	{
		return nfq_set_verdict(qh, id, NF_DROP, 0, NULL);
	}
}


/*
 * Open a netlink connection and returns file descriptor
 */
int netlink_open_connection(void *data)
{
	struct nfnl_handle *nh;
 
#ifdef UFD_DEBUG
	printf("opening library handle\n");
#endif
	h = nfq_open();
	if (!h) 
	{
		fprintf(stderr, "error during nfq_open()\n");
		exit(1);
	}

#ifdef UFD_DEBUG
	printf("unbinding existing nf_queue handler for AF_INET (if any)\n");
#endif
	if (nfq_unbind_pf(h, AF_INET) < 0) 
	{
		fprintf(stderr, "error during nfq_unbind_pf()\n");
		exit(1);
	}

#ifdef UFD_DEBUG
	printf("binding nfnetlink_queue as nf_queue handler for AF_INET\n");
#endif
	if (nfq_bind_pf(h, AF_INET) < 0) 
	{
		fprintf(stderr, "error during nfq_bind_pf()\n");
		exit(1);
	}

#ifdef UFD_DEBUG
	printf("binding this socket to queue '0'\n");
#endif
	qh = nfq_create_queue(h,  0, &cb, NULL);
	if (!qh) 
	{
		fprintf(stderr, "error during nfq_create_queue()\n");
		exit(1);
	}

#ifdef UFD_DEBUG
	printf("setting copy_packet mode\n");
#endif
	if (nfq_set_mode(qh, NFQNL_COPY_PACKET, 0xffff) < 0) 
	{
		fprintf(stderr, "can't set packet_copy mode\n");
		exit(1);
	}

	nh = nfq_nfnlh(h);
	return nfnl_fd(nh);
}


int main(int argc, char **argv)
{
	int fd, rv;
	char buf[BUFSIZE]; 

	strcpy(listtype, argv[1]);
	if (get_url_info())
	{
	   printf("error during get_url_info()\n");
	   return 0;
	}

	memset(buf, 0, sizeof(buf));

	/* open a netlink connection to get packet from kernel */
	fd = netlink_open_connection(NULL);

	while (1)
	{
		rv = recv(fd, buf, sizeof(buf), 0);
		if ( rv >= 0) 
		{
#ifdef UFD_DEBUG
		   printf("pkt received\n");
#endif
		   nfq_handle_packet(h, buf, rv);
		   memset(buf, 0, sizeof(buf));
		}
		else
		{
		   nfq_close(h);
#ifdef UFD_DEBUG
		   printf("nfq close done\n");
#endif
		   fd = netlink_open_connection(NULL);
#ifdef UFD_DEBUG
		   printf("need to rebind to netfilter queue 0\n");
#endif
		}
	}
#ifdef UFD_DEBUG
        printf("unbinding from queue 0\n");
#endif
	nfq_destroy_queue(qh);
	nfq_close(h);

	return 0;
}
