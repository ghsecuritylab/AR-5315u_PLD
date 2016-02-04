/* vi: set sw=4 ts=4: */
/*
 * Mini nslookup implementation for busybox
 *
 * Copyright (C) 1999,2000 by Lineo, inc. and John Beppu
 * Copyright (C) 1999,2000,2001 by John Beppu <beppu@codepoet.org>
 *
 * Correct default name server display and explicit name server option
 * added by Ben Zeckel <bzeckel@hmc.edu> June 2001
 *
 * Licensed under GPLv2 or later, see file LICENSE in this tarball for details.
 */

#include <resolv.h>
#include "libbb.h"

//<< Dean : Support NSLookupDiagnostics, 2016/01/04
#ifdef BRCM_CMS_BUILD
#include "cms_msg.h"
#include "cms_util.h"
#include "cms_log.h"
#endif
#define OPT_STRING "M"

enum {
    OPT_M            = (1 << 19),   /* BRCM, M create msg handler */
};
// brcm begin
#ifdef BRCM_CMS_BUILD

#define NSLOOKUP_IN_PROGRESS  0
#define NSLOOKUP_FINISHED     1
#define NSLOOKUP_DNS_NOEXIST  2  /* nslookup DNSServer not available */
#define NSLOOKUP_HOST_NOEXIST 3  /* nslookup unable to resolve host name */
#define NSLOOKUP_TIMEOUT      4  /* nslookup process exits on time out */
#define NSLOOKUP_ERROR        5  /* nslookup process exits on error */

#define DNS_RR_TYPE_A       0x0001 /* host address */
#define DNS_RR_TYPE_AAAA    0x001c /* IPv6 host address */
static void *msgHandle=NULL;
static CmsEntityId requesterId=0;
static NsLookupDataMsgBody nsLookupMsg;
static timeout=10000; //ms
#endif  /* BRCM_CMS_BUILD */
// brcm end

int glbCount=1, curCount=0;

// brcm begin
#ifdef BRCM_CMS_BUILD
/* this is call to send message back to SMD to relay to interested party about the
 * statistic of the most recent completed or stopped PING test */

static void sendEventMessage(int finish)
{
    char buf[sizeof(CmsMsgHeader) + sizeof(NsLookupDataMsgBody)]={0};
    CmsMsgHeader *msg=(CmsMsgHeader *) buf;
    NsLookupDataMsgBody *nsLookupBody = (NsLookupDataMsgBody*) (msg+1);
    CmsRet ret;

    if (finish == NSLOOKUP_FINISHED)
    {
        sprintf(nsLookupMsg.diagnosticsState, MDMVS_COMPLETE);
    }
    else if (finish == NSLOOKUP_IN_PROGRESS)
    {
        sprintf(nsLookupMsg.diagnosticsState, MDMVS_REQUESTED);
    }
    else if (finish == NSLOOKUP_DNS_NOEXIST)
    {
        sprintf(nsLookupMsg.diagnosticsState, MDMVS_ERROR_DNSSERVERNOTRESOLVED);
        sprintf(nsLookupMsg.status, MDMVS_ERROR_DNSSERVERNOTAVAILABLE);
        sprintf(nsLookupMsg.answerType, MDMVS_NONE);
        sprintf(nsLookupMsg.hostNameReturned, "");
        sprintf(nsLookupMsg.IPAddresses, "");
        nsLookupMsg.responseTime=0;
    }
    else if (finish == NSLOOKUP_HOST_NOEXIST)
    {
        sprintf(nsLookupMsg.diagnosticsState, MDMVS_ERROR_DNSSERVERNOTRESOLVED);
        sprintf(nsLookupMsg.status, MDMVS_ERROR_HOSTNAMENOTRESOLVED);
    }
    else if (finish == NSLOOKUP_TIMEOUT)
    {
        sprintf(nsLookupMsg.diagnosticsState, MDMVS_ERROR_DNSSERVERNOTRESOLVED);
        sprintf(nsLookupMsg.status, MDMVS_ERROR_TIMEOUT);
    }
    else if (finish == NSLOOKUP_ERROR)
    {
        sprintf(nsLookupMsg.diagnosticsState, MDMVS_ERROR_OTHER);
        sprintf(nsLookupMsg.status, MDMVS_ERROR_OTHER);
    }

   msg->type = CMS_MSG_NSLOOKUP_STATE_CHANGED;
   msg->src = MAKE_SPECIFIC_EID(getpid(), EID_NSLOOKUP);
   msg->dst = EID_SSK;
   msg->flags_event = 1;
   msg->dataLength = sizeof(NsLookupDataMsgBody);

   memcpy(nsLookupBody, &nsLookupMsg, sizeof(nsLookupMsg));

   if ((ret = cmsMsg_send(msgHandle, msg)) != CMSRET_SUCCESS)
   {
      cmsLog_error("could not send out CMS_MSG_TRACERT_STATE_CHANGED to ssk, ret=%d", ret);
   }
   else
   {
      cmsLog_notice("sent out CMS_MSG_TRACERT_STATE_CHANGED (finish=%d) to ssk", finish);
   }

   if (requesterId != 0)
   {
      msg->dst = requesterId;
      if ((ret = cmsMsg_send(msgHandle, msg)) != CMSRET_SUCCESS)
      {
         cmsLog_error("could not send out CMS_MSG_PING_STATE_CHANGED to requestId %d, ret=%d", ret,(int)requesterId);
      }
      else
      {
         cmsLog_notice("sent out CMS_MSG_PING_STATE_CHANGED (finish=%d) to requesterId %d", finish,(int)requesterId);
      }
   }

   sprintf(nsLookupMsg.diagnosticsState, "");
   sprintf(nsLookupMsg.status, "");
   sprintf(nsLookupMsg.answerType, "");
   sprintf(nsLookupMsg.hostNameReturned, "");
   sprintf(nsLookupMsg.IPAddresses, "");
   nsLookupMsg.responseTime = 0;
}

static void cmsCleanup(void)
{
   if (option_mask32 & OPT_M)
   {
      cmsMsg_cleanup(&msgHandle);
   }
   cmsLog_cleanup();
}

static void logStat(int finish)
{
   /*
    * Only call sendEventMessage if msgHandle to smd was successfully initialized.
    */
   if (msgHandle != NULL)
   {
      sendEventMessage(finish);
   }
}
#endif  /* BRCM_CMS_BUILD */
// brcm end
//>> Dean, END : Support NSLookupDiagnostics, 2016/01/04

/*
 * I'm only implementing non-interactive mode;
 * I totally forgot nslookup even had an interactive mode.
 *
 * This applet is the only user of res_init(). Without it,
 * you may avoid pulling in _res global from libc.
 */

/* Examples of 'standard' nslookup output
 * $ nslookup yahoo.com
 * Server:         128.193.0.10
 * Address:        128.193.0.10#53
 *
 * Non-authoritative answer:
 * Name:   yahoo.com
 * Address: 216.109.112.135
 * Name:   yahoo.com
 * Address: 66.94.234.13
 *
 * $ nslookup 204.152.191.37
 * Server:         128.193.4.20
 * Address:        128.193.4.20#53
 *
 * Non-authoritative answer:
 * 37.191.152.204.in-addr.arpa     canonical name = 37.32-27.191.152.204.in-addr.arpa.
 * 37.32-27.191.152.204.in-addr.arpa       name = zeus-pub2.kernel.org.
 *
 * Authoritative answers can be found from:
 * 32-27.191.152.204.in-addr.arpa  nameserver = ns1.kernel.org.
 * 32-27.191.152.204.in-addr.arpa  nameserver = ns2.kernel.org.
 * 32-27.191.152.204.in-addr.arpa  nameserver = ns3.kernel.org.
 * ns1.kernel.org  internet address = 140.211.167.34
 * ns2.kernel.org  internet address = 204.152.191.4
 * ns3.kernel.org  internet address = 204.152.191.36
 */

static int print_host(const char *hostname, const char *header)
{
	/* We can't use xhost2sockaddr() - we want to get ALL addresses,
	 * not just one */
	struct addrinfo *result = NULL;
	int rc=0;
	struct addrinfo hint;

//<< Dean : Support NSLookupDiagnostics, 2016/01/04
    struct timeval rest_tv;
    unsigned t1,t2, isHost=0;
    isHost = (strcmp(header,"Name:")==0);
    t1 = monotonic_us();
//>> Dean, END : Support NSLookupDiagnostics, 2016/01/04

	memset(&hint, 0 , sizeof(hint));
	/* hint.ai_family = AF_UNSPEC; - zero anyway */
	/* Needed. Or else we will get each address thrice (or more)
	 * for each possible socket type (tcp,udp,raw...): */
	hint.ai_socktype = SOCK_STREAM;
	// hint.ai_flags = AI_CANONNAME;
//<< Dean : Support NSLookupDiagnostics, 2016/01/04
    if (option_mask32 & OPT_M){
        if(isHost){
            int rc1,rc2;
            rc1 = cmsUtl_specifyQueryDnsServer(hostname, DNS_RR_TYPE_AAAA, nsLookupMsg.DNSServerIP,
                                              nsLookupMsg.IPAddresses, 2, timeout, &rest_tv);
            rc2 = cmsUtl_specifyQueryDnsServer(hostname, DNS_RR_TYPE_A, nsLookupMsg.DNSServerIP,
                                              nsLookupMsg.IPAddresses, 2, timeout, &rest_tv);
            rc = (rc1==FINDDOMAINIP || rc2==FINDDOMAINIP)?0:1;
        }
    }else{
        rc = getaddrinfo(hostname, NULL /*service*/, &hint, &result);
    }
    t2 = monotonic_us() - t1;
// brcm begin
#ifdef BRCM_CMS_BUILD
    if (!isHost && option_mask32 & OPT_M){
        sprintf(nsLookupMsg.DNSServerIP, hostname);
    }
    if (isHost && option_mask32 & OPT_M){
        if(!rc){
            sprintf(nsLookupMsg.status, MDMVS_SUCCESS);
            sprintf(nsLookupMsg.answerType, MDMVS_AUTHORITATIVE);
            sprintf(nsLookupMsg.hostNameReturned, hostname);
            nsLookupMsg.responseTime=t2/1000;
            nsLookupMsg.successCount++;
        }else{
            sprintf(nsLookupMsg.answerType, MDMVS_NONE);
            sprintf(nsLookupMsg.hostNameReturned, "");
            sprintf(nsLookupMsg.IPAddresses, "");
            nsLookupMsg.responseTime=0;
            logStat(NSLOOKUP_HOST_NOEXIST);
        }
    }
#endif /* BRCM_OMCI*/
// brcm end
//>> Dean, END : Support NSLookupDiagnostics, 2016/01/04

	if (!rc) {
		struct addrinfo *cur = result;
		unsigned cnt = 0;

		printf("%-10s %s\n", header, hostname);
//<< Dean : Support NSLookupDiagnostics, 2016/01/04
// brcm begin
#ifdef BRCM_CMS_BUILD
        if (isHost && option_mask32 & OPT_M){
			printf("Address  : %s\n", nsLookupMsg.IPAddresses);
        }
#endif /* BRCM_OMCI*/
// brcm end
//>> Dean, END : Support NSLookupDiagnostics, 2016/01/04
		// puts(cur->ai_canonname); ?
		while (cur) {
			char *dotted, *revhost;
			dotted = xmalloc_sockaddr2dotted_noport(cur->ai_addr);
			revhost = xmalloc_sockaddr2hostonly_noport(cur->ai_addr);

			printf("Address %u: %s%c", ++cnt, dotted, revhost ? ' ' : '\n');
			if (revhost) {
				puts(revhost);
				if (ENABLE_FEATURE_CLEAN_UP)
					free(revhost);
			}
			if (ENABLE_FEATURE_CLEAN_UP)
				free(dotted);
			cur = cur->ai_next;
		}
	} else {
#if ENABLE_VERBOSE_RESOLUTION_ERRORS
		bb_error_msg("can't resolve '%s': %s", hostname, gai_strerror(rc));
#else
		bb_error_msg("can't resolve '%s'", hostname);
#endif
	}

//<< Dean : Support NSLookupDiagnostics, 2016/01/04
#ifdef BRCM_CMS_BUILD
    if ( isHost && option_mask32 & OPT_M){
        if(!rc){
            logStat(NSLOOKUP_IN_PROGRESS);
        }else
            glbCount=0; // set glbCount=0 to exit while
    }
#endif
//>> Dean, END : Support NSLookupDiagnostics, 2016/01/04

	if (ENABLE_FEATURE_CLEAN_UP)
		freeaddrinfo(result);
	return (rc != 0);
}

/* lookup the default nameserver and display it */
static void server_print(void)
{
	char *server;
	struct sockaddr *sa;

#if ENABLE_FEATURE_IPV6
	sa = (struct sockaddr*)_res._u._ext.nsaddrs[0];
	if (!sa)
#endif
		sa = (struct sockaddr*)&_res.nsaddr_list[0];
	server = xmalloc_sockaddr2dotted_noport(sa);

	print_host(server, "Server:");
	if (ENABLE_FEATURE_CLEAN_UP)
		free(server);
	bb_putchar('\n');
}

/* alter the global _res nameserver structure to use
   an explicit dns server instead of what is in /etc/resolv.conf */
static void set_default_dns(const char *server)
{
	len_and_sockaddr *lsa;
	/* NB: this works even with, say, "[::1]:5353"! :) */
    int rc;
    struct timeval rest_tv;
    if(cmsUtl_isValidIpAddress(AF_INET, server) || cmsUtl_isValidIpAddress(AF_INET6, server)){
        strcpy(nsLookupMsg.DNSServerIP, server);
    }else{
        rc = cmsUtl_specifyQueryDnsServer(server, 1, "0.0.0.0", nsLookupMsg.DNSServerIP, 1, timeout, &rest_tv);
        if(rc != FINDDOMAINIP){
            strcpy(nsLookupMsg.DNSServerIP, "0.0.0.0");
            logStat(NSLOOKUP_DNS_NOEXIST);
            exit(0);
        }
    }

//	lsa = xhost2sockaddr(server, 53);
	lsa = xhost2sockaddr(nsLookupMsg.DNSServerIP, 53);

	if (lsa->u.sa.sa_family == AF_INET) {
		_res.nscount = 1;
		/* struct copy */
		_res.nsaddr_list[0] = lsa->u.sin;
	}
#if ENABLE_FEATURE_IPV6
	/* Hoped libc can cope with IPv4 address there too.
	 * No such luck, glibc 2.4 segfaults even with IPv6,
	 * maybe I misunderstand how to make glibc use IPv6 addr?
	 * (uclibc 0.9.31+ should work) */
	if (lsa->u.sa.sa_family == AF_INET6) {
		// glibc neither SEGVs nor sends any dgrams with this
		// (strace shows no socket ops):
		//_res.nscount = 0;
		_res._u._ext.nscount = 1;
		/* store a pointer to part of malloc'ed lsa */
		_res._u._ext.nsaddrs[0] = &lsa->u.sin6;
		/* must not free(lsa)! */
	}
#endif
}

int nslookup_main(int argc, char **argv) MAIN_EXTERNALLY_VISIBLE;
int nslookup_main(int argc, char **argv)
{
	/* We allow 1 or 2 arguments.
	 * The first is the name to be looked up and the second is an
	 * optional DNS server with which to do the lookup.
	 * More than 3 arguments is an error to follow the pattern of the
	 * standard nslookup */

//<< Dean : Support NSLookupDiagnostics, 2016/01/04
    int ret=0;

	if (!argv[1] || argv[1][0] == '-' || argc > 6)
		bb_show_usage();
//>> Dean, END : Support NSLookupDiagnostics, 2016/01/04

	/* initialize DNS structure _res used in printing the default
	 * name server and in the explicit name server option feature. */
	res_init();
	/* rfc2133 says this enables IPv6 lookups */
	/* (but it also says "may be enabled in /etc/resolv.conf") */
	/*_res.options |= RES_USE_INET6;*/

#ifdef BRCM_CMS_BUILD
    if (argc>5){
        option_mask32 |= OPT_M;
        requesterId = xatou16(argv[5]);
    }
    cmsLog_init(EID_NSLOOKUP);
    cmsLog_setLevel(DEFAULT_LOG_LEVEL);
    if (option_mask32 & OPT_M)
        cmsMsg_init(EID_NSLOOKUP, &msgHandle);
#endif

	if (argv[2])
		set_default_dns(argv[2]);

//<< Dean : Support NSLookupDiagnostics, 2016/01/04
    if (argc>3 && argv[3])
        glbCount = atoi(argv[3]);

    if (argc>4 && argv[4])
       timeout = atoi(argv[4]);

	server_print();
    while( ret==0 && curCount<glbCount){
        ret = print_host(argv[1], "Name:");
        curCount++;
    }
#ifdef BRCM_CMS_BUILD
    if (option_mask32 & OPT_M){
        if(!ret)
            logStat(NSLOOKUP_FINISHED);
        cmsCleanup();
    }
#endif
    return ret;
//>> Dean, END : Support NSLookupDiagnostics, 2016/01/04
}
