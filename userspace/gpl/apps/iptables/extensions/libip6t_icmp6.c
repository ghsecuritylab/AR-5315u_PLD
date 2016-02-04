/* Shared library add-on to iptables to add ICMP support. */
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <ip6tables.h>
#include <linux/netfilter_ipv6/ip6_tables.h>

struct icmpv6_names {
	const char *name;
	u_int8_t type;
	u_int8_t code_min, code_max;
};

//<< [CTFN-NMIS-017] Jim Lin: Support to permit and drop the particular ICMP/ICMPv6 message according to Type and Code Definition in direction WAN to LAN, 20120919
static const struct icmpv6_names icmpv6_codes[] = {
	{ "destination-unreachable", 1, 0, 0xFF },
	{   "no-route-to-destination", 			1, 0, 0 },
	{   "administratively-prohibited", 		1, 1, 1 },
	{   "beyond-scope-of-source-address", 	1, 2, 2 },
	{   "address-unreachable", 1, 3, 3 },
	{   "port-unreachable", 1, 4, 4 },
	{	"source-address-failed", 			1, 5, 5 },
	{	"reject-route-to-destination", 		1, 6, 6 },
	{	"error-source-routing-header", 		1, 7, 7 },

	{ "packet-too-big", 2, 0, 0xFF },

	{ "time-exceeded", 3, 0, 0xFF },
	/* Alias */ { "ttl-exceeded", 3, 0, 0xFF },
	{   "hop-limit-exceeded", 				3, 0, 0 },
	{   "fragment-reassembly-time-exceeded",3, 1, 1 },

	{ "parameter-problem", 4, 0, 0xFF },
	{   "erroneous-header-field",			4, 0, 0 },
	{   "unrecognized-next-header-type", 	4, 1, 1 },
	{   "unrecognized-ipv6-option", 		4, 2, 2 },

	{ "echo-request", 128, 0, 0xFF },
	/* Alias */ { "ping", 128, 0, 0xFF },

	{ "echo-reply", 129, 0, 0xFF },
	/* Alias */ { "pong", 129, 0, 0xFF },

	{ "multicast-listener-query",			130, 0, 0xFF },

	{ "multicast-listener-report",			131, 0, 0xFF },

	{ "multicast-listener-done",			132, 0, 0xFF },

	{ "router-solicitation", 133, 0, 0xFF },

	{ "router-advertisement", 134, 0, 0xFF },

	{ "neighbour-solicitation", 135, 0, 0xFF },
	/* Alias */ { "neighbor-solicitation", 135, 0, 0xFF },

	{ "neighbour-advertisement", 136, 0, 0xFF },
	/* Alias */ { "neighbor-advertisement", 136, 0, 0xFF },

	{ "redirect-message", 					137, 0, 0xFF },

	{ "router-renumbering",					138, 0, 0xFF },
	{   "router-renumbering-command",		138, 0, 0 },
	{   "router-renumbering-result",		138, 1, 1 },
	{   "sequence-number-reset",			138, 0xFF, 0xFF },

	{ "node-information-query",				139, 0, 0xFF },
		
	{ "node-information-response",			140, 0, 0xFF },

	{ "inverse-neighbor-discovery-solicitation", 141, 0, 0xFF },

	{ "inverse-neighbor-discovery-advertisement", 142, 0, 0xFF },

	{ "certification-path-solicitation", 148, 0, 0xFF },

	{ "certification-path-advertisement", 149, 0, 0xFF },

	{ "version2-multicast-listener-report", 143, 0, 0xFF },

	{ "multicast-router-advertisement", 	151, 0, 0xFF },
		
	{ "multicast-router-solicitation", 		152, 0, 0xFF },
		 
	{ "multicast-router-termination", 		153, 0, 0xFF },
};
//>> [CTFN-NMIS-017] End

static void
print_icmpv6types(void)
{
	unsigned int i;
	printf("Valid ICMPv6 Types:");

	for (i = 0; i < sizeof(icmpv6_codes)/sizeof(struct icmpv6_names); i++) {
		if (i && icmpv6_codes[i].type == icmpv6_codes[i-1].type) {
			if (icmpv6_codes[i].code_min == icmpv6_codes[i-1].code_min
			    && (icmpv6_codes[i].code_max
				== icmpv6_codes[i-1].code_max))
				printf(" (%s)", icmpv6_codes[i].name);
			else
				printf("\n   %s", icmpv6_codes[i].name);
		}
		else
			printf("\n%s", icmpv6_codes[i].name);
	}
	printf("\n");
}

/* Function which prints out usage message. */
static void icmp6_help(void)
{
	printf(
"ICMPv6 v%s options:\n"
" --icmpv6-type [!] typename	match icmpv6 type\n"
"				(or numeric type or type/code)\n"
"\n", IPTABLES_VERSION);
	print_icmpv6types();
}

static const struct option icmp6_opts[] = {
	{ "icmpv6-type", 1, NULL, '1' },
	{ }
};

static void
parse_icmpv6(const char *icmpv6type, u_int8_t *type, u_int8_t code[])
{
	unsigned int limit = sizeof(icmpv6_codes)/sizeof(struct icmpv6_names);
	unsigned int match = limit;
	unsigned int i;

	for (i = 0; i < limit; i++) {
//<< [CTFN-NMIS-017] Jim Lin: Support to permit and drop the particular ICMP/ICMPv6 message according to Type and Code Definition in direction WAN to LAN, 20120919
#if 0
		if (strncasecmp(icmpv6type, icmpv6_codes[i].name, strlen(icmpv6type))
#else
		if (strcmp(icmpv6type, icmpv6_codes[i].name)
#endif
//>> [CTFN-NMIS-017] End
		    == 0) {
			if (match != limit)
				exit_error(PARAMETER_PROBLEM,
					   "Ambiguous ICMPv6 type `%s':"
					   " `%s' or `%s'?",
					   icmpv6type,
					   icmpv6_codes[match].name,
					   icmpv6_codes[i].name);
			match = i;
		}
	}

	if (match != limit) {
		*type = icmpv6_codes[match].type;
		code[0] = icmpv6_codes[match].code_min;
		code[1] = icmpv6_codes[match].code_max;
	} else {
		char *slash;
		char buffer[strlen(icmpv6type) + 1];
		unsigned int number;

		strcpy(buffer, icmpv6type);
		slash = strchr(buffer, '/');

		if (slash)
			*slash = '\0';

		if (string_to_number(buffer, 0, 255, &number) == -1)
			exit_error(PARAMETER_PROBLEM,
				   "Invalid ICMPv6 type `%s'\n", buffer);
		*type = number;
		if (slash) {
			if (string_to_number(slash+1, 0, 255, &number) == -1)
				exit_error(PARAMETER_PROBLEM,
					   "Invalid ICMPv6 code `%s'\n",
					   slash+1);
			code[0] = code[1] = number;
		} else {
			code[0] = 0;
			code[1] = 0xFF;
		}
	}
}

/* Initialize the match. */
static void icmp6_init(struct xt_entry_match *m)
{
	struct ip6t_icmp *icmpv6info = (struct ip6t_icmp *)m->data;

	icmpv6info->code[1] = 0xFF;
}

/* Function which parses command options; returns true if it
   ate an option */
static int icmp6_parse(int c, char **argv, int invert, unsigned int *flags,
                       const void *entry, struct xt_entry_match **match)
{
	struct ip6t_icmp *icmpv6info = (struct ip6t_icmp *)(*match)->data;

	switch (c) {
	case '1':
		if (*flags == 1)
			exit_error(PARAMETER_PROBLEM,
				   "icmpv6 match: only use --icmpv6-type once!");
		check_inverse(optarg, &invert, &optind, 0);
		parse_icmpv6(argv[optind-1], &icmpv6info->type, 
			     icmpv6info->code);
		if (invert)
			icmpv6info->invflags |= IP6T_ICMP_INV;
		*flags = 1;
		break;

	default:
		return 0;
	}

	return 1;
}

static void print_icmpv6type(u_int8_t type,
			   u_int8_t code_min, u_int8_t code_max,
			   int invert,
			   int numeric)
{
	if (!numeric) {
		unsigned int i;

		for (i = 0;
		     i < sizeof(icmpv6_codes)/sizeof(struct icmpv6_names);
		     i++) {
			if (icmpv6_codes[i].type == type
			    && icmpv6_codes[i].code_min == code_min
			    && icmpv6_codes[i].code_max == code_max)
				break;
		}

		if (i != sizeof(icmpv6_codes)/sizeof(struct icmpv6_names)) {
			printf("%s%s ",
			       invert ? "!" : "",
			       icmpv6_codes[i].name);
			return;
		}
	}

	if (invert)
		printf("!");

	printf("type %u", type);
	if (code_min == 0 && code_max == 0xFF)
		printf(" ");
	else if (code_min == code_max)
		printf(" code %u ", code_min);
	else
		printf(" codes %u-%u ", code_min, code_max);
}

/* Prints out the union ipt_matchinfo. */
static void icmp6_print(const void *ip, const struct xt_entry_match *match,
                        int numeric)
{
	const struct ip6t_icmp *icmpv6 = (struct ip6t_icmp *)match->data;

	printf("ipv6-icmp ");
	print_icmpv6type(icmpv6->type, icmpv6->code[0], icmpv6->code[1],
		       icmpv6->invflags & IP6T_ICMP_INV,
		       numeric);

	if (icmpv6->invflags & ~IP6T_ICMP_INV)
		printf("Unknown invflags: 0x%X ",
		       icmpv6->invflags & ~IP6T_ICMP_INV);
}

/* Saves the match in parsable form to stdout. */
static void icmp6_save(const void *ip, const struct xt_entry_match *match)
{
	const struct ip6t_icmp *icmpv6 = (struct ip6t_icmp *)match->data;

	if (icmpv6->invflags & IP6T_ICMP_INV)
		printf("! ");

	printf("--icmpv6-type %u", icmpv6->type);
	if (icmpv6->code[0] != 0 || icmpv6->code[1] != 0xFF)
		printf("/%u", icmpv6->code[0]);
	printf(" ");
}

static void icmp6_check(unsigned int flags)
{
	if (!flags)
		exit_error(PARAMETER_PROBLEM,
			   "icmpv6 match: You must specify `--icmpv6-type'");
}

static struct ip6tables_match icmp6_match6 = {
	.name 		= "icmp6",
	.version 	= IPTABLES_VERSION,
	.size		= IP6T_ALIGN(sizeof(struct ip6t_icmp)),
	.userspacesize	= IP6T_ALIGN(sizeof(struct ip6t_icmp)),
	.help		= icmp6_help,
	.init		= icmp6_init,
	.parse		= icmp6_parse,
	.final_check	= icmp6_check,
	.print		= icmp6_print,
	.save		= icmp6_save,
	.extra_opts	= icmp6_opts,
};

void _init(void)
{
	register_match6(&icmp6_match6);
}
