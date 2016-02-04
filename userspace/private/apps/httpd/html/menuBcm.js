//Note: The options array initialized in menu.html follows
//      the MENU_OPTION order defined here.	Both sides must
//      be in the same order.
var MENU_OPTION_USER              = 0;
var MENU_OPTION_STANDARD          = 1;
var MENU_OPTION_PROTOCOL          = 2;
var MENU_OPTION_FIREWALL          = 3;
var MENU_OPTION_NAT               = 4;
var MENU_OPTION_IP_EXTENSION      = 5;
var MENU_OPTION_WIRELESS          = 6;
var MENU_OPTION_VOICE             = 7;
var MENU_OPTION_SNMP              = 8;
var MENU_OPTION_UPNP              = 9;
var MENU_OPTION_DDNSD             = 10;
var MENU_OPTION_SNTP              = 11;
var MENU_OPTION_EBTABLES          = 12;
var MENU_OPTION_BRIDGE            = 13;
var MENU_OPTION_TOD               = 14;
var MENU_OPTION_SIPROXD           = 15;
var MENU_OPTION_DHCPEN            = 16;
var MENU_OPTION_QOS               = 17;
var MENU_OPTION_PORTMAP           = 18;
var MENU_OPTION_IPP               = 19;
var MENU_OPTION_WIRELESS_SES      = 20;
var MENU_OPTION_RIP               = 21;
var MENU_OPTION_IPSEC             = 22;
var MENU_OPTION_CERT              = 23;
var MENU_OPTION_WL_QOS            = 24;
var MENU_OPTION_TR69C             = 25;
var MENU_OPTION_VDSL              = 26;
var MENU_OPTION_URLFILTER         = 27;
var MENU_OPTION_IPV6_SUPPORT      = 28;
var MENU_OPTION_IPV6_ENABLE       = 29;
var MENU_OPTION_DNSPROXY          = 30;
var MENU_OPTION_POLICY_ROUTING    = 31;
var MENU_OPTION_OMCI              = 32;
var MENU_OPTION_CHIPID            = 33;
var MENU_OPTION_WIRELESS_NUM_ADAPTOR =34;
var MENU_OPTION_DIAG_P8021AG      =35;
var MENU_OPTION_ETHWAN            =36;
var MENU_OPTION_PTMWAN            =37;
//<< [BCMBG-MGM-006] Charles Wei : Add the missing MENU_OPTION_DHCP_RELAY in menuBcm.js
var MENU_OPTION_DHCP_RELAY		  =38;
//>> [BCMBG-MGM-006]
var MENU_OPTION_PWRMNGT           =39;
var MENU_OPTION_VOICE_NTR         =40;
var MENU_OPTION_ATMWAN            =41;
var MENU_OPTION_MOCAWAN           =42;
var MENU_OPTION_VOICE_DECT        =43;
var MENU_OPTION_DSL_BONDING       =44;
var MENU_OPTION_MULTICAST         =45;
var MENU_OPTION_VPN               =46;
var MENU_OPTION_STORAGESERVICE    =47;
var MENU_OPTION_SUPPORT_MOCA      =48;
var MENU_OPTION_STANDBY           =49;
var MENU_OPTION_DLNA              =50;
var MENU_OPTION_WIRELESS_WAPI_AS  =51;
var MENU_OPTION_AUTODETECTION	  =52;
var MENU_OPTION_GPONWAN           =53;
var MENU_OPTION_POLICE_ENABLE     =54;
var MENU_OPTION_OSGI_JVM          =55;
var MENU_OPTION_EPONWAN           =56;
var MENU_OPTION_SAMBA             =57;
var MENU_OPTION_BMU               =58;
var MENU_OPTION_BUILD_VDSL        =59;
var MENU_OPTION_SUPPORT_LAN_VLAN  =60;
var MENU_OPTION_OPTICAL          = 61;
//<< [CTFN-MGM-001] Jimmy Wu : for Comtrend's username & password
var MENU_OPTION_ADM_USERNAME      = 62;
var MENU_OPTION_SPT_USERNAME      = 63;
var MENU_OPTION_USR_USERNAME      = 64;
//>> [CTFN-MGM-001] End
//<< [CTFN-NLAN-002] Jim Lin: Support DNS relay feature, 2010/12/28  
var MENU_OPTION_ENABLE_DNS_RELAY       = 65;
//>> [CTFN-NLAN-002] Jim Lin: Support DNS relay feature, 2010/12/28  
//<< [CTFN-NWAN-012] Lain: For IP Address Mapping feature, 2010/10/01
var MENU_OPTION_IPADDRMAP         = 66;
//>> [CTFN-NWAN-012] End
// << [CTFN-MGM-011] jojopo : Support services and IP address access control via web, like 3.xx, 2010/08/10
var MENU_OPTION_ACCCNTR           = 67;
var MENU_OPTION_ACCCNTRIP           = 68;
//>> [CTFN-MGM-011] End
//<< [CTFN-NMIS-005] xsonic: Support to enable/disable SIP ALG in Web GUI 2010/11/01
var MENU_OPTION_SIPALG        = 69;
//>> [CTFN-NMIS-005] End
//<< [CTFN-NMIS-011] Lucien Huang : Support to enable/disable IPSec ALG in Web GUI, 2011/07/27
var MENU_OPTION_IPSECALG          =70;
//>> [CTFN-NMIS-011] End
// << [CTFN-NMIS-009] Charles Wei: Enhance Samba feature to support non-security and security mode and remove redundant public and shared folders, 2011/06/23
var MENU_OPTION_STORAGE_USERACCOUNT 	  = 71;
// >> [CTFN-NMIS-009] End
//<< [CTFN-NMIS-014-1] Charles Wei: Add the missing ejGetOther() in menu.html and related modification	
var MENU_OPTION_NAT_SESSION				= 72;
//>> [CTFN-NMIS-014-1] End
//<< [CTFN-3G-001] MHTsai: Support 3G feature, 2010/08/09
var MENU_OPTION_3G_WAN            =73;
//>> [CTFN-3G-001] End
//<< [BCMBG-NTWK-025] Charles Wei: Fix that the menu has the item "Security Log" in Web GUI when the security log feature is disabled in the profile, 2010/07/07
var MENU_OPTION_SECURITY_LOG      = 74;
//>> [BCMBG-NTWK-025] End
// << [CTFN-NMIS-009-4] Charles Wei: Charles Wei: Add Enable/Disable Samba function
var MENU_OPTION_ENABLE_SAMBA 	  = 75;
// >> [CTFN-NMIS-009-4] End
//<< [CTFN-NWAN-016] Joba Yang: Support Auto-detection feature (implemented by Comtrend)
var MENU_OPTION_CT_AUTO_DETECTION 		 = 76;
//>> [CTFN-NWAN-016] End
//<< [CTFN-NMIS-019] David Rodriguez: Support Wake-on-LAN tool, 2013-07-05
var MENU_OPTION_WOLTOOL           = 77;
//>> [CTFN-NMIS-019] End
//<< [CTFN-SYS-022] Support option to hide DSL information and remove PHY/driver version from software version name when ATM/PTM is enabled
var MENU_OPTION_HIDE_DSL		 = 78;
//>> [CTFN-SYS-022] End 
//<< [CTFN-WIFI-014] Support two Wireless Interfaces with band defined in board parameter and modify SSID according to band info
var MENU_OPTION_WLPHYLIST = 79;
//>> [CTFN-WIFI-014] End

var wlItemsCgiCmd = new Array(
 	                    'wlswitchinterface0.wl',
                           'wlswitchinterface1.wl',
                           'wlswitchinterface2.wl',
                           'wlswitchinterface3.wl'
                          );

 var wlmenuTitle = new Array(
 	                    'wl0',
                           'wl1',
                           'wl2',
                           'wl3'
                          );
function menuAdmin(options) {
   var std = options[MENU_OPTION_STANDARD];
   var proto = options[MENU_OPTION_PROTOCOL];
   var firewall = options[MENU_OPTION_FIREWALL];
   var ipExt = options[MENU_OPTION_IP_EXTENSION];
   var wireless = options[MENU_OPTION_WIRELESS];
   var voice = options[MENU_OPTION_VOICE];
   var snmp = options[MENU_OPTION_SNMP];
   var ddnsd = options[MENU_OPTION_DDNSD];
   var sntp = options[MENU_OPTION_SNTP];
   var ebtables = options[MENU_OPTION_EBTABLES];
   var bridge = options[MENU_OPTION_BRIDGE];
   var tod = options[MENU_OPTION_TOD];
   var QosEnabled = options[MENU_OPTION_QOS];
   var vlanconfig = options[MENU_OPTION_PORTMAP];
   var ipp = options[MENU_OPTION_IPP];
   var dlna = options[MENU_OPTION_DLNA];
   var wireless_ses = options[MENU_OPTION_WIRELESS_SES];
   var rip = options[MENU_OPTION_RIP];
   var ipsec = options[MENU_OPTION_IPSEC];
   var certificate = options[MENU_OPTION_CERT];
   var wlqos = options[MENU_OPTION_WL_QOS];
   var tr69c = options[MENU_OPTION_TR69C];
   var ipv6Support = options[MENU_OPTION_IPV6_SUPPORT];
   var ipv6Enable = options[MENU_OPTION_IPV6_ENABLE];
   var upnp = options[MENU_OPTION_UPNP];
   var urlfilter = options[MENU_OPTION_URLFILTER];
   var dnsproxy = options[MENU_OPTION_DNSPROXY];
   var pr = options[MENU_OPTION_POLICY_ROUTING];
   var omci = options[MENU_OPTION_OMCI];
   var numWl = options[MENU_OPTION_WIRELESS_NUM_ADAPTOR];
   var p8021ag = options[MENU_OPTION_DIAG_P8021AG];
   var ethwan = options[MENU_OPTION_ETHWAN];
   var ptm = options[MENU_OPTION_PTMWAN];
   var pwrmngt = options[MENU_OPTION_PWRMNGT];
   var standby = options[MENU_OPTION_STANDBY];
   var voiceNtr = options[MENU_OPTION_VOICE_NTR];
   var atm = options[MENU_OPTION_ATMWAN];
   var mocawan = options[MENU_OPTION_MOCAWAN];
   var gponwan = options[MENU_OPTION_GPONWAN];
   var eponwan = options[MENU_OPTION_EPONWAN];
   var dect = options[MENU_OPTION_VOICE_DECT];
   var dslbonding = options[MENU_OPTION_DSL_BONDING];
   var multicast = options[MENU_OPTION_MULTICAST];
   var vpn = options[MENU_OPTION_VPN];
   var storageservice = options[MENU_OPTION_STORAGESERVICE];
   var sambaservice = options[MENU_OPTION_SAMBA];
   var mocaCfg = options[MENU_OPTION_SUPPORT_MOCA];
   var wireless_wapi = options[MENU_OPTION_WIRELESS_WAPI_AS];
   var autoDetection = options[MENU_OPTION_AUTODETECTION];
   var policeEnable = options[MENU_OPTION_POLICE_ENABLE];
   var isDsl = 0;
   //var osgi_jvm = options[MENU_OPTION_OSGI_JVM];
   var bmu = options[MENU_OPTION_BMU];
   var buildVdsl = options[MENU_OPTION_BUILD_VDSL];
   var lanvlanEnable = options[MENU_OPTION_SUPPORT_LAN_VLAN];
//<< [CTFN-NLAN-002] Jim Lin: Support DNS relay feature, 2010/12/28  
   var DNS_RELAY = options[MENU_OPTION_ENABLE_DNS_RELAY];
//>> [CTFN-NLAN-002] Jim Lin: Support DNS relay feature, 2010/12/28  
//<< [CTFN-NWAN-012] Lain: For IP Address Mapping feature, 2010/10/01
   var ipaddrmap = options[MENU_OPTION_IPADDRMAP];
//>> [CTFN-NWAN-012] End
// << [CTFN-MGM-011] jojopo : Support services and IP address access control via web, like 3.xx, 2010/08/10
   var acccntr = options[MENU_OPTION_ACCCNTR];
   var acccntrip = options[MENU_OPTION_ACCCNTRIP];
// >> [CTFN-MGM-011] End
//<< [CTFN-NMIS-005] xsonic: Support to enable/disable SIP ALG in Web GUI 2010/11/01
   var sipalgswitch = options[MENU_OPTION_SIPALG];                          
//>> [CTFN-NMIS-005] End
//<< [CTFN-NMIS-011] Lucien Huang : Support to enable/disable IPSec ALG in Web GUI, 2011/07/27
   var ipsecalgswitch = options[MENU_OPTION_IPSECALG];
//>> [CTFN-NMIS-011] End
// << [CTFN-NMIS-009] Charles Wei: Enhance Samba feature to support non-security and security mode and remove redundant public and shared folders, 2011/06/23
	var sambaSecurity = options[MENU_OPTION_STORAGE_USERACCOUNT];
// >> [CTFN-NMIS-009] End	
//<< [CTFN-3G-001] MHTsai: Support 3G feature, 2010/08/09
   var threegwan = options[MENU_OPTION_3G_WAN];
//>> [CTFN-3G-001] End
//<< [BCMBG-NTWK-025] Charles Wei : Fix that the menu has the item "Security Log" in Web GUI when the security log feature is disabled in the profile, 2010/07/07
   var security_log = options[MENU_OPTION_SECURITY_LOG];
//>> [BCMBG-NTWK-025] End
//<< [CTFN-NMIS-009-4] Charles Wei: Enhance Samba feature to support non-security and security mode and remove redundant public and shared folders, 2011/06/23
	var enableSambaServer = options[MENU_OPTION_ENABLE_SAMBA];
//>> [CTFN-NMIS-009-4] End	
//<< [CTFN-NWAN-016] Joba Yang: Support Auto-detection feature (implemented by Comtrend)
	var ctautodetect = options[MENU_OPTION_CT_AUTO_DETECTION];
//>> [CTFN-NWAN-016] End
//<< [CTFN-NMIS-019] David Rodriguez: Support Wake-on-LAN tool, 2013-07-05
   var woltool = options[MENU_OPTION_WOLTOOL];
//>> [CTFN-NMIS-019] End
//<< [CTFN-WIFI-014] Support two Wireless Interfaces with band defined in board parameter and modify SSID according to band info
   var phylist = options[MENU_OPTION_WLPHYLIST];
   var phymode = phylist.split('|');
//>> [CTFN-WIFI-014] End
//<< [CTFN-SYS-022] Support option to hide DSL information and remove PHY/driver version from software version name when ATM/PTM is enabled
 var hidedslopt = options[MENU_OPTION_HIDE_DSL];
	// Configure advanced setup/layer 2 interface 
	if (atm == '1' && hidedslopt == '0') {
		isDsl = 1;
		nodeAdvancedSetup = insFld(foldersTree, gFld(getMenuTitle(MENU_ADVANCED_SETUP), 'dslatm.cmd'));
		nodeLayer2Inteface = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_LAYER2_INTERFACE), 'dslatm.cmd'));
		insDoc(nodeLayer2Inteface, gLnk('R', getMenuTitle(MENU_DSL_ATM_INTERFACE), 'dslatm.cmd'));		
	} 
	if (ptm == '1' && hidedslopt == '0') {
		isDsl = 1;
		if (atm != '1') {
			nodeAdvancedSetup = insFld(foldersTree, gFld(getMenuTitle(MENU_ADVANCED_SETUP), 'dslptm.cmd'));
			nodeLayer2Inteface = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_LAYER2_INTERFACE), 'dslptm.cmd'));
		}
		insDoc(nodeLayer2Inteface, gLnk('R', getMenuTitle(MENU_DSL_PTM_INTERFACE), 'dslptm.cmd'));		
	}	
	if (gponwan == '1' ) {
		if (!(atm == '1' || ptm == '1')) {
			nodeAdvancedSetup = insFld(foldersTree, gFld(getMenuTitle(MENU_ADVANCED_SETUP), 'gponwan.cmd'));
			nodeLayer2Inteface = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_LAYER2_INTERFACE), 'gponwan.cmd'));
		}
		insDoc(nodeLayer2Inteface, gLnk('R', getMenuTitle(MENU_GPONWAN_INTERFACE), 'gponwan.cmd'));
	}
	if (eponwan == '1' ) {
		if (!(atm == '1' || ptm == '1') || gponwan == '1' ) {
			nodeAdvancedSetup = insFld(foldersTree, gFld(getMenuTitle(MENU_ADVANCED_SETUP), 'eponwan.cmd'));
			nodeLayer2Inteface = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_LAYER2_INTERFACE), 'eponwan.cmd'));
		}
		insDoc(nodeLayer2Inteface, gLnk('R', getMenuTitle(MENU_EPONWAN_INTERFACE), 'eponwan.cmd'));
	}	
	if (ethwan == '1' ) {
		if ((!(atm == '1' || ptm == '1' || gponwan == '1' || eponwan == '1'))|| hidedslopt == '1') {
			nodeAdvancedSetup = insFld(foldersTree, gFld(getMenuTitle(MENU_ADVANCED_SETUP), 'ethwan.cmd'));
			nodeLayer2Inteface = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_LAYER2_INTERFACE), 'ethwan.cmd'));
		}
		insDoc(nodeLayer2Inteface, gLnk('R', getMenuTitle(MENU_ETH_INTERFACE), 'ethwan.cmd'));
	}
	if (mocawan == '1') {
		if (!(atm == '1' || ptm == '1' || ethwan == '1')) {
			nodeAdvancedSetup = insFld(foldersTree, gFld(getMenuTitle(MENU_ADVANCED_SETUP), 'mocawan.cmd'));
			nodeLayer2Inteface = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_LAYER2_INTERFACE), 'mocawan.cmd'));
		}
		insDoc(nodeLayer2Inteface, gLnk('R', getMenuTitle(MENU_MOCA_INTERFACE), 'mocawan.cmd'));
	}  
	if( hidedslopt == '1'){
				isDsl = 0;
		}
//>> [CTFN-SYS-022] End 

	if (!(atm == '1' || ptm == '1' || ethwan == '1' || mocawan == '1' || gponwan == '1' || eponwan == '1'))
		nodeAdvancedSetup = insFld(foldersTree, gFld(getMenuTitle(MENU_ADVANCED_SETUP), 'wancfg.cmd'));
//<< [CTFN-3G-001] MHTsai: Support 3G feature, 2010/08/09
	if (threegwan == '1') {
		nodeWanService = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_WAN),'wancfg.cmd'));
		//insDoc(nodeWanService, gLnk('R', getMenuTitle(MENU_3G_WAN), '3gcfg.cmd'));
		insDoc(nodeWanService, gLnk('R', getMenuTitle(MENU_3G_WAN), '3gwan.cmd'));
	}
	else
//>> [CTFN-3G-001] End
	insDoc(nodeAdvancedSetup, gLnk('R', getMenuTitle(MENU_WAN),'wancfg.cmd'));

	if (vpn == '1') {
		nodeVPN = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_VPN), 'l2tpacwan.cmd'));
		insDoc(nodeVPN, gLnk('R', getMenuTitle(MENU_VPN_L2TPAC), 'l2tpacwan.cmd'));		
	}
	
   nodeLAN = insDoc(nodeAdvancedSetup, gFld(getMenuTitle(MENU_LAN),'lancfg2.html'));
   if ( lanvlanEnable == '1' ) 
      insDoc(nodeLAN, gLnk('R', getMenuTitle(MENU_LAN_VLAN),'lanvlancfg.html'));
   if ( ipv6Enable == '1' ) {
      insDoc(nodeLAN, gLnk('R', getMenuTitle(MENU_LAN6),'ipv6lancfg.html'));
//<< [CTFN-IPV6-009] Camille Wu: Support static IPv4/IPv6 neighbor via CLI/GUI and add IPv6 neighbor table in IPv6/Device Info page, 2012/02/17
   insDoc(nodeLAN, gLnk('R', getMenuTitle(MENU_STATIC_IP_NEIGHBOR),'staticipneighborcfg.cmd'));
//>> [CTFN-IPV6-009] End
   }

//<< [CTFN-NWAN-016] Joba Yang: Support Auto-detection feature (implemented by Comtrend)
	if(ctautodetect == '1')
      insDoc(nodeAdvancedSetup, gFld(getMenuTitle(MENU_CTAUTODETECTION), 'ctautodetect.cmd'));
//>> [CTFN-NWAN-016] End
   // Configure connection auto detection
   if (autoDetection == '1')
      insDoc(nodeAdvancedSetup, gFld(getMenuTitle(MENU_AUTODETECTION), 'autodetection.cmd?action=view'));

   if ( mocaCfg == '1' ) {
      insDoc(nodeAdvancedSetup, gLnk('R', getMenuTitle(MENU_MOCA_CONFIGURATION),'mocacfg.html'));
   }

   // Configure security menu
   // If firewall is enabled and not in ipExt mode enable firewall menus
   // if (proto != 'Bridge' && ipExt != '1' ) {
   if ( proto != 'Not Applicable' && ipExt != '1' ) {
      // NAT menu is always displayed now
      nodeNat = insDoc(nodeAdvancedSetup, gFld(getMenuTitle(MENU_SC_NAT), 'scvrtsrv.cmd?action=view'));
      insDoc(nodeNat, gLnk('R', getMenuTitle(MENU_SC_VIRTUAL_SERVER), 'scvrtsrv.cmd?action=view'));
      insDoc(nodeNat, gLnk('R', getMenuTitle(MENU_SC_PORT_TRIGGER), 'scprttrg.cmd?action=view'));
      insDoc(nodeNat, gLnk('R', getMenuTitle(MENU_SC_DMZ_HOST), 'scdmz.html'));
//<< [CTFN-NWAN-012] Lain: For IP Address Mapping feature, 2010/10/01
      if ( ipaddrmap == '1' )
	     insDoc(nodeNat, gLnk('R', getMenuTitle(MENU_SC_IP_ADDR_MAP), 'ipaddrmap.cmd?action=view'));
//>> [CTFN-NWAN-012] End
//<< [CTFN-NMIS-005] xsonic: Support to enable/disable SIP ALG in Web GUI 2010/11/01
	if(sipalgswitch=='1')
		insDoc(nodeNat, gLnk('R', getMenuTitle(MENU_SIP_ALG), 'sipalgcfg.html'));
//>> [CTFN-NMIS-005] End
//<< [CTFN-NMIS-011] Lucien Huang : Support to enable/disable IPSec ALG in Web GUI, 2011/07/27
      if(ipsecalgswitch=='1')
         insDoc(nodeNat, gLnk('R', getMenuTitle(MENU_IPSEC_ALG), 'algipseccfg.html'));
//>> [CTFN-NMIS-011] End

      // Security menu is always displayed now                   	
      nodeFirewall = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_SC_SECURITY), 'scoutflt.cmd?action=view'));
      nodeIpFlt = insFld(nodeFirewall, gFld(getMenuTitle(MENU_SC_IP_FILTER), 'scoutflt.cmd?action=view'));
      insDoc(nodeIpFlt, gLnk('R', getMenuTitle(MENU_SC_OUTGOING), 'scoutflt.cmd?action=view'));
      insDoc(nodeIpFlt, gLnk('R', getMenuTitle(MENU_SC_INCOMING), 'scinflt.cmd?action=view'));
      insFld(nodeFirewall, gFld(getMenuTitle(MENU_MAC_FILTER),'scmacflt.cmd?action=view'));

      if ( tod == '1' ) 
      {
         nodeParentalControl = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_PARENTAL_CNTL),'todmngr.tod?action=view'));
         insDoc(nodeParentalControl, gFld(getMenuTitle(MENU_TOD),'todmngr.tod?action=view'));
      }
      if ( urlfilter == '1' )
         insDoc(nodeParentalControl, gFld(getMenuTitle(MENU_URLFILTER),'urlfilter.cmd?action=view'));
   }

      // Configure QoS class menu
   nodeQos = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_QOS),'qosqmgmt.html'));
   insDoc(nodeQos, gLnk('R', getMenuTitle(MENU_QOS_QUEUE), 'qosqueue.cmd?action=view'));
   if (policeEnable == '1')
      insDoc(nodeQos, gLnk('R', getMenuTitle(MENU_QOS_POLICER), 'qospolicer.cmd?action=view'));
   insDoc(nodeQos, gLnk('R', getMenuTitle(MENU_QOS_CLASS), 'qoscls.cmd?action=view'));

   
   // Configure routing menu
   nodeRouting = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_ROUTING), 'rtdefaultcfg.html'));
   insDoc(nodeRouting, gLnk('R', getMenuTitle(MENU_RT_DEFAULT_ROUTE), 'rtdefaultcfg.html'));
   insDoc(nodeRouting, gLnk('R', getMenuTitle(MENU_RT_STATIC_ROUTE),'rtroutecfg.cmd?action=viewcfg'));
   if (pr == '1' )
      insDoc(nodeRouting, gLnk('R', getMenuTitle(MENU_POLICY_ROUTING),'prmngr.cmd?action=view'));

   if ( (proto == 'PPPoE' && ipExt == '0') ||
        (proto == 'PPPoA' && ipExt == '0') ||
        (proto == 'MER') ||
        (proto == 'IPoA') ) {
      // configure rip
      if ( rip == '1' )
         insDoc(nodeRouting, gLnk('R', getMenuTitle(MENU_RT_RIP),'ripcfg.cmd?action=view'));
      // configure dns server
      nodeDnsSetup = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_DNS), 'dnscfg.html'));
      insDoc(nodeDnsSetup, gLnk('R', getMenuTitle(MENU_DNS_SETUP), 'dnscfg.html'));
      // configure ddns client
      if ( ddnsd == '1' )
         insDoc(nodeDnsSetup, gLnk('R', getMenuTitle(MENU_DDNS), 'ddnsmngr.cmd'));
   }


   if (isDsl == 1)
   {
      // Configure ADSL Setting Menu based on Annex
      if ( std == 'annex_c' )
         insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_DSL), 'adslcfgc.html'));
      else if (buildVdsl == '1')
         insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_DSL), 'xdslcfg.html'));
      else
         insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_DSL), 'adslcfg.html'));

      if (dslbonding == '1')
         insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_DSL_BONDING), 'dslbondingcfg.html'));
   }

	// Configure upnp
	if (upnp == '1')
	   insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_UPNP), 'upnpcfg.html'));

	
   // Configure dnsproxy
//<< [CTFN-NLAN-002] Jim Lin: Support DNS relay feature, 2010/12/28  
   if ((DNS_RELAY == '1')&&(dnsproxy == '1'))
		insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_DNSPROXY1), 'dnsproxycfg.html'));
   else
   	{
//>> [CTFN-NLAN-002] Jim Lin: Support DNS relay feature, 2010/12/28     
   if (dnsproxy == '1')
      insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_DNSPROXY), 'dnsproxycfg.html'));
//<< [CTFN-NLAN-002] Jim Lin: Support DNS relay feature, 2010/12/28  
	}
//>> [CTFN-NLAN-002] Jim Lin: Support DNS relay feature, 2010/12/28     

   // Configure print server
   if ( ipp == '1' )
      insDoc(nodeAdvancedSetup, gFld(getMenuTitle(MENU_IPP), 'ippcfg.html'));

   // Configure dlna
   if ( dlna == '1' )
      insDoc(nodeAdvancedSetup, gFld(getMenuTitle(MENU_DLNA), 'dlnacfg.html'));

//<< [CTFN-3G-001] MHTsai: Support 3G feature, 2010/08/09
   // Configure 3G
   if (threegwan == '1') {
      node3gConfig = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_3G_SETUP), '3gbackup.html'));
      //node3gConfig = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_3G_SETUP), 'pincfg.cmd'));
      insDoc(node3gConfig, gLnk('R', getMenuTitle(MENU_3G_BACKUP),'3gbackup.html'));
      insDoc(node3gConfig, gLnk('R', getMenuTitle(MENU_3G_PIN_CFG),'pincfg.cmd'));
	  //insDoc(node3gConfig, gLnk('R', getMenuTitle(MENU_3G_DONGLE_CFG),'3gbackup.html'));
   }
//>> [CTFN-3G-001] End

   // Configure wireless menu

   if ( parseInt(numWl) != 0 ) {
      if(numWl != '1')
         wlanMenu = insFld(foldersTree, gFld(getMenuTitle(MENU_WIRELESS_SETTINGS), wlItemsCgiCmd[0]));
 
      for(i = 0; i < parseInt(numWl); i++)
      {
         // Configure wireless menu
         if(numWl == '1')
            nodeWireless = insFld(foldersTree, gFld(getMenuTitle(MENU_WIRELESS_SETTINGS), wlItemsCgiCmd[0]));
//<< [CTFN-WIFI-014] Support two Wireless Interfaces with band defined in board parameter and modify SSID according to band info
         else{
		if(phymode[i].length > 0)
            nodeWireless = insFld(wlanMenu, gFld(phymode[i], wlItemsCgiCmd[i]));
         else
            nodeWireless = insFld(wlanMenu, gFld(wlmenuTitle[i], wlItemsCgiCmd[i]));
         }
//>> [CTFN-WIFI-014] End
         insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_BASIC), 'wlcfg.html'));
         insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_SECURITY), 'wlsecurity.html'));
         insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_MAC_FILTERING), 'wlmacflt.cmd?action=view'));
         insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_WDS), 'wlwds.cmd?action=view'));
         insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_ADVANCED), 'wlcfgadv.html'));
//<< [CTFN-WIFI-015] Add Wireless Channel Graph and Site Survey feature in Wireless/Site Survey page, 2012/09/21
         insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_SS), 'wlsry.cmd'));
//>> [CTFN-WIFI-015] End
         //SUPPORT_SES
         if ( wireless_ses == '1' ) { 
            insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_SES), 'wlses.html'));      
         }
      
         insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_STATION_LIST), 'wlstationlist.cmd'));
      }

      if ( wireless_wapi == '1' ) {      
          if (numWl == '1') {
             insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_WAPI_AS), 'wlwapias.html'));
          }
          else {
             insDoc(wlanMenu, gLnk('R', getMenuTitle(MENU_WL_WAPI_AS), 'wlwapias.html'));
          }
      }
   }


     /*Storage Service menu */
   if(storageservice == '1')
   {
      nodeStorage = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_STORAGESERVICE), 'storageservicecfg.cmd?view'));
      insDoc(nodeStorage, gLnk('R', getMenuTitle(MENU_STORAGE_INFO), 'storageservicecfg.cmd?view'));
// << [CTFN-NMIS-009] Charles Wei: Enhance Samba feature to support non-security and security mode and remove redundant public and shared folders, 2011/06/23
      //insDoc(nodeStorage, gLnk('R', getMenuTitle(MENU_STORAGE_SMBCONFIG), 'storagesmbcfg.cmd?action=view'));
      if(sambaSecurity == '1' && enableSambaServer == '1')
         insDoc(nodeStorage, gLnk('R', getMenuTitle(MENU_STORAGE_USERACCOUNT), 'storageuseraccountcfg.cmd?view'));
// >> [CTFN-NMIS-009] Charles Wei: End
   }

   // Configure voice menu
   if ( voice == 'MGCP' ) {
      nodeVoice = insFld(foldersTree, gFld(getMenuTitle(MENU_VOICE_SETTINGS), 'voicemgcp_basic.html'));
      insDoc(nodeVoice, gLnk('R', getMenuTitle(MENU_VOICE_MGCP), 'voicemgcp_basic.html'));
      if( voiceNtr != '2' ) {
         insDoc(nodeVoice, gLnk('R', getMenuTitle(MENU_VOICE_NTR), 'voicentr.html'));
      }
   }
   else if ( voice == 'SIP' ) {
      nodeVoice = insFld(foldersTree, gFld(getMenuTitle(MENU_VOICE_SETTINGS), 'voicesip_basic.html'));
      insDoc(nodeVoice, gLnk('R', getMenuTitle(MENU_VOICE_SIP_BASIC), 'voicesip_basic.html'));
      insDoc(nodeVoice, gLnk('R', getMenuTitle(MENU_VOICE_SIP_ADVANCED), 'voicesip_advanced.html'));
      insDoc(nodeVoice, gLnk('R', getMenuTitle(MENU_VOICE_SIP_DEBUG), 'voicesip_debug.html'));
      if( voiceNtr != '2' ) {
         insDoc(nodeVoice, gLnk('R', getMenuTitle(MENU_VOICE_NTR), 'voicentr.html'));
      }
      if( dect == '1' ) {
         insDoc(nodeVoice, gLnk('R', getMenuTitle(MENU_VOICE_DECT), 'voicedect.html'));
      }
   }

   // Configure VLAN port mapping menu
   if ( vlanconfig == '1' ) {
      insDoc(nodeAdvancedSetup, gLnk('R', getMenuTitle(MENU_INTF_GROUPING),'portmap.cmd'));
   }

   if ( ipv6Support == '1' ) {
      nodeIpTunnel = insDoc(nodeAdvancedSetup, gFld(getMenuTitle(MENU_IP_TUNNEL),'tunnelcfg.cmd?action=viewcfg'));
      insDoc(nodeIpTunnel, gLnk('R', getMenuTitle(MENU_6IN4_TUNNEL),'tunnelcfg.cmd?action=viewcfg'));
      insDoc(nodeIpTunnel, gLnk('R', getMenuTitle(MENU_4IN6_TUNNEL),'tunnelcfg.cmd?action=view'));
   }

   if ( ipsec == '1' ) {
      insDoc(nodeAdvancedSetup, gLnk('R', getMenuTitle(MENU_SC_IPSEC), 'ipsec.cmd?action=view'));
   }
   if (certificate == '1')  {
      nodeCert = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_CERT), 'certlocal.cmd?action=view'));
      insDoc(nodeCert, gLnk('R', getMenuTitle(MENU_CERT_LOCAL), 'certlocal.cmd?action=view'));
      insDoc(nodeCert, gLnk('R', getMenuTitle(MENU_CERT_CA), 'certca.cmd?action=view'));
   }

   // Configure standby menu item 
   if ( standby == '1' ) 
      insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_STANDBY), 'standby.html'));

   // Configure power management 
   if ( pwrmngt == '1' ) 
      insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_PWRMNGT), 'pwrmngt.html'));
  
   if ( bmu == '1' ) 
      insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_BMU), 'bmu.html'));

   if ( multicast == '1' ) 
      insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_MULTICAST), 'multicast.html'));
  
   // Configure diagnostics menu
   nodeDiagnostics = insFld(foldersTree, gFld(getMenuTitle(MENU_DIAGNOSTICS), 'diag.html'));
   if (p8021ag == '1') {
      insDoc(nodeDiagnostics, gLnk('R', getMenuTitle(MENU_DIAGNOSTICS),'diag.html'));
      insDoc(nodeDiagnostics, gLnk('R', getMenuTitle(MENU_DIAGP8021AG),'diag8021ag.html'));
   }

   // Configure management menu
   nodeMngr = insFld(foldersTree, gFld(getMenuTitle(MENU_MANAGEMENT), 'backupsettings.html'));

   nodeSettings = insFld(nodeMngr, gFld(getMenuTitle(MENU_TL_SETTINGS), 'backupsettings.html'));
   insDoc(nodeSettings, gLnk('R', getMenuTitle(MENU_TL_SETTINGS_BACKUP),'backupsettings.html'));
   insDoc(nodeSettings, gLnk('R', getMenuTitle(MENU_TL_SETTINGS_UPDATE),'updatesettings.html'));
   insDoc(nodeSettings, gLnk('R', getMenuTitle(MENU_TL_SETTINGS_DEFAULT), 'defaultsettings.html'));

   insFld(nodeMngr, gFld(getMenuTitle(MENU_TL_SYSTEM_LOG), 'logintro.html'));
//<< [BCMBG-NTWK-025] Charles Wei : Fix that the menu has the item "Security Log" in Web GUI when the security log feature is disabled in the profile, 2010/07/07
   if ( security_log == '1' )
//>> [BCMBG-NTWK-025] End
   insFld(nodeMngr, gFld(getMenuTitle(MENU_TL_SECURITY_LOG), 'seclogintro.html'));
   if ( snmp == '1' )
      insFld(nodeMngr, gFld(getMenuTitle(MENU_TL_SNMP), 'snmpconfig.html'));
   //if ( tr69c == '1' )
      //insFld(nodeMngr, gFld(getMenuTitle(MENU_TR69C), 'tr69cfg.html'));
   if ( omci == '1' ) {
      nodeOmci = insFld(nodeMngr, gFld(getMenuTitle(MENU_OMCI_CFG), 'omcicfg.cmd?action=view'));
      insDoc(nodeOmci, gLnk('R', getMenuTitle(MENU_OMCI_GET_SET),'omcicfg.cmd?action=view'));
      insDoc(nodeOmci, gLnk('R', getMenuTitle(MENU_OMCI_CREATE),'omcicreate.cmd?action=view'));
      insDoc(nodeOmci, gLnk('R', getMenuTitle(MENU_OMCI_GET_NEXT),'omcigetnext.cmd?action=view'));
      insDoc(nodeOmci, gLnk('R', getMenuTitle(MENU_OMCI_MACRO),'omcimacro.cmd?action=view'));
      insDoc(nodeOmci, gLnk('R', getMenuTitle(MENU_OMCI_DOWNLOAD),'omcidownload.html'));
      insDoc(nodeOmci, gLnk('R', getMenuTitle(MENU_OMCI_SYSTEM),'omcisystem.html'));
   }	  
   if ( sntp == '1' && proto != 'Bridge' && !(proto=='PPPoE' && ipExt=='1') && !(proto=='PPPoA' && ipExt=='1') )
      insFld(nodeMngr, gFld(getMenuTitle(MENU_SNTP), 'sntpcfg.html'));

   nodeAccCntr = insFld(nodeMngr, gFld(getMenuTitle(MENU_ACC_CNTR), 'password.html'));
   insDoc(nodeAccCntr, gLnk('R', getMenuTitle(MENU_ACC_CNTR_PASSWORD), 'password.html'));

   //   if (osgi_jvm == 1)
   //   {
   //   	nodeSWModules = insFld(nodeMngr, gFld(getMenuTitle(MENU_SW_MODULES), 'swmodulesEE.cmd'));
   //   	insDoc(nodeSWModules, gLnk('R', getMenuTitle(MENU_SW_MODULES_EE),'swmodulesEE.cmd'));
   //   	insDoc(nodeSWModules, gLnk('R', getMenuTitle(MENU_SW_MODULES_DU),'swmodulesDU.cmd'));
   //   	insDoc(nodeSWModules, gLnk('R', getMenuTitle(MENU_SW_MODULES_EU), 'swmodulesEU.cmd'));
   //   }
// << [CTFN-MGM-011] jojopo : Support services and IP address access control via web, like 3.xx, 2010/08/10
   if(acccntr == '1')
      insDoc(nodeAccCntr, gLnk('R', getMenuTitle(MENU_ACC_CNTR_SERVICE), 'acccntr.cmd'));
   if(acccntrip == '1')
   insDoc(nodeAccCntr, gLnk('R', getMenuTitle(MENU_ACC_CNTR_IPADDR), 'scaccc.cmd?action=view'));
// >> [CTFN-MGM-011] End

//<< [CTFN-NMIS-019] David Rodriguez: Support Wake-on-LAN tool, 2013-07-05
   if (woltool == '1')
      insFld(nodeMngr, gFld(getMenuTitle(MENU_WOL_TOOL), 'wakeonlan.html'));
//>> [CTFN-NMIS-019] End

   insFld(nodeMngr, gFld(getMenuTitle(MENU_TL_UPDATE_SOFTWARE), 'upload.html'));

   insFld(nodeMngr, gFld(getMenuTitle(MENU_RESET_ROUTER), 'resetrouter.html'));

}

function menuSupport(options) {
   var std = options[MENU_OPTION_STANDARD];
   var proto = options[MENU_OPTION_PROTOCOL];
   var ipExt = options[MENU_OPTION_IP_EXTENSION];
   var wireless = options[MENU_OPTION_WIRELESS];
   var voice = options[MENU_OPTION_VOICE];
   var snmp = options[MENU_OPTION_SNMP];
   var ddnsd = options[MENU_OPTION_DDNSD];
   var sntp = options[MENU_OPTION_SNTP];
   var QosEnabled = options[MENU_OPTION_QOS];
   var ipp = options[MENU_OPTION_IPP];
   var rip = options[MENU_OPTION_RIP];
   var tr69c = options[MENU_OPTION_TR69C];
   var ipv6Support = options[MENU_OPTION_IPV6_SUPPORT];
   var ipv6Enable = options[MENU_OPTION_IPV6_ENABLE];
   var upnp = options[MENU_OPTION_UPNP];
   var dnsproxy = options[MENU_OPTION_DNSPROXY];
   var omci = options[MENU_OPTION_OMCI];
   var numWl = options[MENU_OPTION_WIRELESS_NUM_ADAPTOR];
   var wireless_ses = options[MENU_OPTION_WIRELESS_SES];
   var ethwan = options[MENU_OPTION_ETHWAN];
   var ptm = options[MENU_OPTION_PTMWAN];
   var pwrmngt = options[MENU_OPTION_PWRMNGT];
   var standby = options[MENU_OPTION_STANDBY];
   var voiceNtr = options[MENU_OPTION_VOICE_NTR];
   var atm = options[MENU_OPTION_ATMWAN];
   var mocawan = options[MENU_OPTION_MOCAWAN];
   var gponwan = options[MENU_OPTION_GPONWAN];
   var eponwan = options[MENU_OPTION_EPONWAN];
   var dect = options[MENU_OPTION_VOICE_DECT];
   var dslbonding = options[MENU_OPTION_DSL_BONDING];
   var multicast = options[MENU_OPTION_MULTICAST];
   var vpn = options[MENU_OPTION_VPN];
   var storageservice = options[MENU_OPTION_STORAGESERVICE];
   var sambaservice = options[MENU_OPTION_SAMBA];
   var mocaCfg = options[MENU_OPTION_SUPPORT_MOCA];
   var wireless_wapi = options[MENU_OPTION_WIRELESS_WAPI_AS];
   var policeEnable = options[MENU_OPTION_POLICE_ENABLE];
   var bmu = options[MENU_OPTION_BMU];
   var isDsl = 0;
   var osgi_jvm = options[MENU_OPTION_OSGI_JVM];
   var buildVdsl = options[MENU_OPTION_BUILD_VDSL];
   var lanvlanEnable = options[MENU_OPTION_SUPPORT_LAN_VLAN];
//<< [CTFN-NLAN-002] Jim Lin: Support DNS relay feature, 2010/12/28  
   var DNS_RELAY = options[MENU_OPTION_ENABLE_DNS_RELAY];
//>> [CTFN-NLAN-002] Jim Lin: Support DNS relay feature, 2010/12/28  
// << [CTFN-MGM-011] jojopo : Support services and IP address access control via web, like 3.xx, 2010/08/10
   var acccntr = options[MENU_OPTION_ACCCNTR];
   var acccntrip = options[MENU_OPTION_ACCCNTRIP];
// >> [CTFN-MGM-011] End
// << [CTFN-NMIS-009-2] Charles Wei : Add the missing code for "support" account
	var sambaSecurity = options[MENU_OPTION_STORAGE_USERACCOUNT];
// >> [CTFN-NMIS-009-2] End	
//<< [CTFN-3G-001] MHTsai: Support 3G feature, 2010/08/09
   var threegwan = options[MENU_OPTION_3G_WAN];
//>> [CTFN-3G-001] End
//<< [BCMBG-NTWK-025] Charles Wei : Fix that the menu has the item "Security Log" in Web GUI when the security log feature is disabled in the profile, 2010/07/07
   var security_log = options[MENU_OPTION_SECURITY_LOG];
//>> [BCMBG-NTWK-025] End
//<< [CTFN-NMIS-009-4] Charles Wei: Enhance Samba feature to support non-security and security mode and remove redundant public and shared folders, 2011/06/23
	var enableSambaServer = options[MENU_OPTION_ENABLE_SAMBA];
//>> [CTFN-NMIS-009-4] End	
//<< [CTFN-NWAN-016] Joba Yang: Support Auto-detection feature (implemented by Comtrend)
	var ctautodetect = options[MENU_OPTION_CT_AUTO_DETECTION];
//>> [CTFN-NWAN-016] End
//<< [CTFN-WIFI-014] Support two Wireless Interfaces with band defined in board parameter and modify SSID according to band info
   var phylist = options[MENU_OPTION_WLPHYLIST];
   var phymode = phylist.split('|');
//>> [CTFN-WIFI-014] End
//<< [CTFN-SYS-022] Support option to hide DSL information and remove PHY/driver version from software version name when ATM/PTM is enabled
 var hidedslopt = options[MENU_OPTION_HIDE_DSL];
	// Configure advanced setup/layer 2 interface 
	if (atm == '1' && hidedslopt == '0') {
		isDsl = 1;
		nodeAdvancedSetup = insFld(foldersTree, gFld(getMenuTitle(MENU_ADVANCED_SETUP), 'dslatm.cmd'));
		nodeLayer2Inteface = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_LAYER2_INTERFACE), 'dslatm.cmd'));
		insDoc(nodeLayer2Inteface, gLnk('R', getMenuTitle(MENU_DSL_ATM_INTERFACE), 'dslatm.cmd'));		
	} 
	if (ptm == '1' && hidedslopt == '0') {
		isDsl = 1;
		if (atm != '1') {
			nodeAdvancedSetup = insFld(foldersTree, gFld(getMenuTitle(MENU_ADVANCED_SETUP), 'dslptm.cmd'));
			nodeLayer2Inteface = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_LAYER2_INTERFACE), 'dslptm.cmd'));
		}
		insDoc(nodeLayer2Inteface, gLnk('R', getMenuTitle(MENU_DSL_PTM_INTERFACE), 'dslptm.cmd'));		
	}	   	
	if (gponwan == '1' ) {
		if (!(atm == '1' || ptm == '1')) {
			nodeAdvancedSetup = insFld(foldersTree, gFld(getMenuTitle(MENU_ADVANCED_SETUP), 'gponwan.cmd'));
			nodeLayer2Inteface = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_LAYER2_INTERFACE), 'gponwan.cmd'));
		}
		insDoc(nodeLayer2Inteface, gLnk('R', getMenuTitle(MENU_GPONWAN_INTERFACE), 'gponwan.cmd'));
	}
	if (eponwan == '1' ) {
		if (!(atm == '1' || ptm == '1') || gponwan == '1' ) {
			nodeAdvancedSetup = insFld(foldersTree, gFld(getMenuTitle(MENU_ADVANCED_SETUP), 'eponwan.cmd'));
			nodeLayer2Inteface = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_LAYER2_INTERFACE), 'eponwan.cmd'));
		}
		insDoc(nodeLayer2Inteface, gLnk('R', getMenuTitle(MENU_EPONWAN_INTERFACE), 'eponwan.cmd'));
	}	
	if (ethwan == '1' ) {
		if ((!(atm == '1' || ptm == '1' || gponwan == '1' || eponwan == '1'))|| hidedslopt == '1') {
			nodeAdvancedSetup = insFld(foldersTree, gFld(getMenuTitle(MENU_ADVANCED_SETUP), 'ethwan.cmd'));
			nodeLayer2Inteface = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_LAYER2_INTERFACE), 'ethwan.cmd'));
		}
		insDoc(nodeLayer2Inteface, gLnk('R', getMenuTitle(MENU_ETH_INTERFACE), 'ethwan.cmd'));
	}
	if (mocawan == '1') {
		if (!(atm == '1' || ptm == '1' || ethwan == '1')) {
			nodeAdvancedSetup = insFld(foldersTree, gFld(getMenuTitle(MENU_ADVANCED_SETUP), 'mocawan.cmd'));
			nodeLayer2Inteface = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_LAYER2_INTERFACE), 'mocawan.cmd'));
		}
		insDoc(nodeLayer2Inteface, gLnk('R', getMenuTitle(MENU_MOCA_INTERFACE), 'mocawan.cmd'));
	}  
	if( hidedslopt == '1'){
				isDsl = 0;
		}
//>> [CTFN-SYS-022] End 	
	if (!(atm == '1' || ptm == '1' || ethwan == '1' || mocawan == '1' || gponwan == '1' || eponwan == '1'))
		nodeAdvancedSetup = insFld(foldersTree, gFld(getMenuTitle(MENU_ADVANCED_SETUP), 'wancfg.cmd'));
//<< [CTFN-3G-001] MHTsai: Support 3G feature, 2010/08/09
	if (threegwan == '1') {
		nodeWanService = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_WAN),'wancfg.cmd'));
		//insDoc(nodeWanService, gLnk('R', getMenuTitle(MENU_3G_WAN), '3gcfg.cmd'));
		insDoc(nodeWanService, gLnk('R', getMenuTitle(MENU_3G_WAN), '3gwan.cmd'));
	}
	else
//>> [CTFN-3G-001] End
	insDoc(nodeAdvancedSetup, gLnk('R', getMenuTitle(MENU_WAN),'wancfg.cmd'));

	if (vpn == '1') {
		nodeVPN = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_VPN), 'l2tpacwan.cmd'));
		insDoc(nodeVPN, gLnk('R', getMenuTitle(MENU_VPN_L2TPAC), 'l2tpacwan.cmd'));		
	}
		
   nodeLAN = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_LAN),'lancfg2.html'));
   if ( lanvlanEnable == '1' ) 
      insFld(nodeLAN, gFld(getMenuTitle(MENU_LAN_VLAN),'lanvlancfg.html'));
   
   if ( ipv6Enable == '1' ) {
      insDoc(nodeLAN, gLnk('R', getMenuTitle(MENU_LAN6),'ipv6lancfg.html'));
   }
//<< [CTFN-NWAN-016] Joba Yang: Support Auto-detection feature (implemented by Comtrend)
	if(ctautodetect == '1')
      insDoc(nodeAdvancedSetup, gFld(getMenuTitle(MENU_CTAUTODETECTION), 'ctautodetect.cmd'));
//>> [CTFN-NWAN-016] End   
   if ( mocaCfg == '1' ) {
      insDoc(nodeAdvancedSetup, gLnk('R', getMenuTitle(MENU_MOCA_CONFIGURATION),'mocacfg.html'));
   }

      // Configure QoS class menu
   nodeQos = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_QOS),'qosqmgmt.html'));
   insDoc(nodeQos, gLnk('R', getMenuTitle(MENU_QOS_QUEUE), 'qosqueue.cmd?action=view'));
   if (policeEnable == '1')
      insDoc(nodeQos, gLnk('R', getMenuTitle(MENU_QOS_POLICER), 'qospolicer.cmd?action=view'));
   insDoc(nodeQos, gLnk('R', getMenuTitle(MENU_QOS_CLASS), 'qoscls.cmd?action=view'));

   // Configure routing menu
   nodeRouting = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_ROUTING), 'rtdefaultcfg.html'));
   insDoc(nodeRouting, gLnk('R', getMenuTitle(MENU_RT_DEFAULT_ROUTE), 'rtdefaultcfg.html'));
   insDoc(nodeRouting, gLnk('R', getMenuTitle(MENU_RT_STATIC_ROUTE),'rtroutecfg.cmd?action=viewcfg'));

   if ( (proto == 'PPPoE' && ipExt == '0') ||
        (proto == 'PPPoA' && ipExt == '0') ||
        (proto == 'MER') ||
        (proto == 'IPoA') ) {
      // configure rip
      if ( rip == '1' )
         insDoc(nodeRouting, gLnk('R', getMenuTitle(MENU_RT_RIP),'ripcfg.cmd?action=view'));
      // configure dns server
      nodeDnsSetup = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_DNS), 'dnscfg.html'));
      insDoc(nodeDnsSetup, gLnk('R', getMenuTitle(MENU_DNS_SETUP), 'dnscfg.html'));
      // configure ddns client
      if ( ddnsd == '1' )
         insDoc(nodeDnsSetup, gLnk('R', getMenuTitle(MENU_DDNS), 'ddnsmngr.cmd'));
   }

   if (isDsl == 1)
   {
      // Configure ADSL Setting Menu based on Annex
      if ( std == 'annex_c' )
         insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_DSL), 'adslcfgc.html'));
      else if (buildVdsl == '1')
         insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_DSL), 'xdslcfg.html'));
      else
         insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_DSL), 'adslcfg.html'));

      if (dslbonding == '1')
         insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_DSL_BONDING), 'dslbondingcfg.html'));
   }

	
   // Configure print server
   if ( ipp == '1' )
      insDoc(nodeAdvancedSetup, gFld(getMenuTitle(MENU_IPP), 'ippcfg.html'));
   
   // Configure upnp
   if (upnp == '1')
      insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_UPNP), 'upnpcfg.html'));

   // Configure dnsproxy
//<< [CTFN-NLAN-002] Jim Lin: Support DNS relay feature, 2010/12/28  
   if ((DNS_RELAY == '1')&&(dnsproxy == '1'))
		insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_DNSPROXY1), 'dnsproxycfg.html'));
   else
   	{
//>> [CTFN-NLAN-002] Jim Lin: Support DNS relay feature, 2010/12/28     
   if (dnsproxy == '1')
      insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_DNSPROXY), 'dnsproxycfg.html'));
//<< [CTFN-NLAN-002] Jim Lin: Support DNS relay feature, 2010/12/28  
	}
//>> [CTFN-NLAN-002] Jim Lin: Support DNS relay feature, 2010/12/28       
   // Configure standby menu item 
   if ( standby == '1' ) 
      insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_STANDBY), 'standby.html'));

//<< [CTFN-3G-001] MHTsai: Support 3G feature, 2010/08/09
   // Configure 3G
   if (threegwan == '1') {
      node3gConfig = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_3G_SETUP), '3gbackup.html'));
      //node3gConfig = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_3G_SETUP), 'pincfg.cmd'));
      insDoc(node3gConfig, gLnk('R', getMenuTitle(MENU_3G_BACKUP),'3gbackup.html'));
      insDoc(node3gConfig, gLnk('R', getMenuTitle(MENU_3G_PIN_CFG),'pincfg.cmd'));
	  //insDoc(node3gConfig, gLnk('R', getMenuTitle(MENU_3G_DONGLE_CFG),'3gbackup.html'));
   }
//>> [CTFN-3G-001] End

   // Configure power management 
   if ( pwrmngt == '1' ) 
      insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_PWRMNGT), 'pwrmngt.html'));
  
   if ( bmu == '1' ) 
      insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_BMU), 'bmu.html'));

   // Configure wireless menu
   if ( parseInt(numWl) != 0 ) {

       if(numWl != '1')
           wlanMenu = insFld(foldersTree, gFld(getMenuTitle(MENU_WIRELESS_SETTINGS), wlItemsCgiCmd[0]));
 
       for(i = 0; i < parseInt(numWl); i++)
       {
   // Configure wireless menu
            if(numWl == '1')
                nodeWireless = insFld(foldersTree, gFld(getMenuTitle(MENU_WIRELESS_SETTINGS), wlItemsCgiCmd[0]));
//<< [CTFN-WIFI-014] Support two Wireless Interfaces with band defined in board parameter and modify SSID according to band info
	     else{
		if(phymode[i].length > 0)
            nodeWireless = insFld(wlanMenu, gFld(phymode[i], wlItemsCgiCmd[i]));
	     else
		  nodeWireless = insFld(wlanMenu, gFld(wlmenuTitle[i], wlItemsCgiCmd[i]));
         }
//>> [CTFN-WIFI-014] End
      insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_BASIC), 'wlcfg.html'));
      insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_SECURITY), 'wlsecurity.html'));
      insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_MAC_FILTERING), 'wlmacflt.cmd?action=view'));
      insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_WDS), 'wlwds.cmd?action=view'));
      insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_ADVANCED), 'wlcfgadv.html'));
//<< [CTFN-WIFI-015] Add Wireless Channel Graph and Site Survey feature in Wireless/Site Survey page, 2012/09/21
         insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_SS), 'wlsry.cmd'));
//>> [CTFN-WIFI-015] End
      //SUPPORT_SES
      if ( wireless_ses == '1' ) { 
         insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_SES), 'wlses.html'));      
      }
      
      insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_STATION_LIST), 'wlstationlist.cmd'));
   


        }
      if ( wireless_wapi == '1' ) {      
          if (numWl == '1') {
             insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_WAPI_AS), 'wlwapias.html'));
          }
          else {
             insDoc(wlanMenu, gLnk('R', getMenuTitle(MENU_WL_WAPI_AS), 'wlwapias.html'));
          }
      }
   }

     /*Storage Service menu */
   if(storageservice == '1')
   {
      nodeStorage = insFld(nodeAdvancedSetup, gFld(getMenuTitle(MENU_STORAGESERVICE), 'storageservicecfg.cmd?view'));
      insDoc(nodeStorage, gLnk('R', getMenuTitle(MENU_STORAGE_INFO), 'storageservicecfg.cmd?view'));
// << [CTFN-NMIS-009] Charles Wei: Enhance Samba feature to support non-security and security mode and remove redundant public and shared folders, 2011/06/23
   if(sambaSecurity == '1' && enableSambaServer == '1')
         insDoc(nodeStorage, gLnk('R', getMenuTitle(MENU_STORAGE_USERACCOUNT), 'storageuseraccountcfg.cmd?view'));
// >> [CTFN-NMIS-009] Charles Wei: End
   }

   // Configure voice menu
   if ( voice == 'MGCP' ) {
      nodeVoice = insFld(foldersTree, gFld(getMenuTitle(MENU_VOICE_SETTINGS), 'voicemgcp_basic.html'));
      insDoc(nodeVoice, gLnk('R', getMenuTitle(MENU_VOICE_MGCP), 'voicemgcp_basic.html'));
      if( voiceNtr != '2' ) {
         insDoc(nodeVoice, gLnk('R', getMenuTitle(MENU_VOICE_NTR), 'voicentr.html'));
      }     
   }
   else if ( voice == 'SIP' ) {
      nodeVoice = insFld(foldersTree, gFld(getMenuTitle(MENU_VOICE_SETTINGS), 'voicesip_basic.html'));
      insDoc(nodeVoice, gLnk('R', getMenuTitle(MENU_VOICE_SIP_BASIC), 'voicesip_basic.html'));
      insDoc(nodeVoice, gLnk('R', getMenuTitle(MENU_VOICE_SIP_ADVANCED), 'voicesip_advanced.html'));
      insDoc(nodeVoice, gLnk('R', getMenuTitle(MENU_VOICE_SIP_DEBUG), 'voicesip_debug.html'));
      if( voiceNtr != '2' ) {
         insDoc(nodeVoice, gLnk('R', getMenuTitle(MENU_VOICE_NTR), 'voicentr.html'));
      }
      if( dect == '1' ) {
         insDoc(nodeVoice, gLnk('R', getMenuTitle(MENU_VOICE_DECT), 'voicedect.html'));
      }   
   }

    // Configure diagnostics menu
   nodeDiagnostics = insFld(foldersTree, gFld(getMenuTitle(MENU_DIAGNOSTICS), 'diag.html'));

   // Configure management menu
   nodeMngr = insFld(foldersTree, gFld(getMenuTitle(MENU_MANAGEMENT), 'backupsettings.html'));
   nodeSettings = insFld(nodeMngr, gFld(getMenuTitle(MENU_TL_SETTINGS), 'backupsettings.html'));
   insDoc(nodeSettings, gLnk('R', getMenuTitle(MENU_TL_SETTINGS_BACKUP),'backupsettings.html'));
   insDoc(nodeSettings, gLnk('R', getMenuTitle(MENU_TL_SETTINGS_UPDATE),'updatesettings.html'));
   insDoc(nodeSettings, gLnk('R', getMenuTitle(MENU_TL_SETTINGS_DEFAULT), 'defaultsettings.html'));

   insFld(nodeMngr, gFld(getMenuTitle(MENU_TL_SYSTEM_LOG), 'logintro.html'));
//<< [BCMBG-NTWK-025] Charles Wei: Fix that the menu has the item "Security Log" in Web GUI when the security log feature is disabled in the profile, 2010/07/07
   if ( security_log == '1' )
//>> [BCMBG-NTWK-025] End
   insFld(nodeMngr, gFld(getMenuTitle(MENU_TL_SECURITY_LOG), 'seclogintro.html'));
   if ( snmp == '1' )
      insFld(nodeMngr, gFld(getMenuTitle(MENU_TL_SNMP), 'snmpconfig.html'));
   if ( tr69c == '1' )
      insFld(nodeMngr, gFld(getMenuTitle(MENU_TR69C), 'tr69cfg.html'));
   if ( omci == '1' ) {
      nodeOmci = insFld(nodeMngr, gFld(getMenuTitle(MENU_OMCI_CFG), 'omcicfg.cmd?action=view'));
      insDoc(nodeOmci, gLnk('R', getMenuTitle(MENU_OMCI_GET_SET),'omcicfg.cmd?action=view'));
      insDoc(nodeOmci, gLnk('R', getMenuTitle(MENU_OMCI_CREATE),'omcicreate.cmd?action=view'));
      insDoc(nodeOmci, gLnk('R', getMenuTitle(MENU_OMCI_GET_NEXT),'omcigetnext.cmd?action=view'));
      insDoc(nodeOmci, gLnk('R', getMenuTitle(MENU_OMCI_MACRO),'omcimacro.cmd?action=view'));
      insDoc(nodeOmci, gLnk('R', getMenuTitle(MENU_OMCI_DOWNLOAD),'omcidownload.html'));
      insDoc(nodeOmci, gLnk('R', getMenuTitle(MENU_OMCI_SYSTEM),'omcisystem.html'));
   }
   if ( sntp == '1' && proto != 'Bridge' && !(proto=='PPPoE' && ipExt=='1') && !(proto=='PPPoA' && ipExt=='1') )
      insFld(nodeMngr, gFld(getMenuTitle(MENU_SNTP), 'sntpcfg.html'));
// << [CTFN-MGM-011] jojopo : Support services and IP address access control via web, like 3.xx, 2010/08/10
   if(acccntr == '1')
      insFld(nodeMngr, gFld(getMenuTitle(MENU_ACC_CNTR_SERVICE), 'acccntr.cmd'));
//<< [CTFN-MGM-011-3] Charles Wei: Add the missing codes in Access Control for "support" account
   nodeAccCntr = insFld(nodeMngr, gFld(getMenuTitle(MENU_ACC_CNTR), 'password.html'));
//<< [CTFN-MGM-011-4] Charles Wei: Add the missing Password option in Access Control for "support" account
   insDoc(nodeAccCntr, gLnk('R', getMenuTitle(MENU_ACC_CNTR_PASSWORD), 'password.html'));
//>> [CTFN-MGM-011-4] End
//>> [CTFN-MGM-011-3] End
   if(acccntrip == '1')
   insDoc(nodeAccCntr, gLnk('R', getMenuTitle(MENU_ACC_CNTR_IPADDR), 'scaccc.cmd?action=view'));
// >> [CTFN-MGM-011] End
   if (osgi_jvm == 1)
   {
   	nodeSWModules = insFld(nodeMngr, gFld(getMenuTitle(MENU_SW_MODULES), 'swmodulesEE.cmd'));
   	insDoc(nodeSWModules, gLnk('R', getMenuTitle(MENU_SW_MODULES_EE),'swmodulesEE.cmd'));
   	insDoc(nodeSWModules, gLnk('R', getMenuTitle(MENU_SW_MODULES_DU),'swmodulesDU.cmd'));
   	insDoc(nodeSWModules, gLnk('R', getMenuTitle(MENU_SW_MODULES_EU), 'swmodulesEU.cmd'));
   }

   insFld(nodeMngr, gFld(getMenuTitle(MENU_TL_UPDATE_SOFTWARE), 'upload.html'));
   insFld(nodeMngr, gFld(getMenuTitle(MENU_RESET_ROUTER), 'resetrouter.html'));
}

function menuUser() {
//<< jojopo : for user account menu , 2015/12/24
   var snmp = options[MENU_OPTION_SNMP];
   var tr69c = options[MENU_OPTION_TR69C];
   var omci = options[MENU_OPTION_OMCI];
   var numWl = options[MENU_OPTION_WIRELESS_NUM_ADAPTOR];
   var wireless_ses = options[MENU_OPTION_WIRELESS_SES];
   var wireless_wapi = options[MENU_OPTION_WIRELESS_WAPI_AS];
//<< [CTFN-WIFI-014] Support two Wireless Interfaces with band defined in board parameter and modify SSID according to band info
   var phylist = options[MENU_OPTION_WLPHYLIST];
   var phymode = phylist.split('|');
//>> [CTFN-WIFI-014] End

   // Configure advanced setup menu
   nodeAdvancedSetup = insFld(foldersTree, gFld(getMenuTitle(MENU_ADVANCED_SETUP), 'urlfilter.cmd?action=view'));

   // Configure wireless menu
   if ( parseInt(numWl) != 0 ) {

       if(numWl != '1')
           wlanMenu = insFld(foldersTree, gFld(getMenuTitle(MENU_WIRELESS_SETTINGS), wlItemsCgiCmd[0]));

       for(i = 0; i < parseInt(numWl); i++)
       {
          // Configure wireless menu
          if(numWl == '1')
             nodeWireless = insFld(foldersTree, gFld(getMenuTitle(MENU_WIRELESS_SETTINGS), wlItemsCgiCmd[0]));
//<< [CTFN-WIFI-014] Support two Wireless Interfaces with band defined in board parameter and modify SSID according to band info
          else{
             if(phymode[i].length > 0)
                nodeWireless = insFld(wlanMenu, gFld(phymode[i], wlItemsCgiCmd[i]));
             else
                nodeWireless = insFld(wlanMenu, gFld(wlmenuTitle[i], wlItemsCgiCmd[i]));
          }
//>> [CTFN-WIFI-014] End
          insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_BASIC), 'wlcfg.html'));
          insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_SECURITY), 'wlsecurity.html'));
          insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_MAC_FILTERING), 'wlmacflt.cmd?action=view'));
          insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_WDS), 'wlwds.cmd?action=view'));
          insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_ADVANCED), 'wlcfgadv.html'));
//<< [CTFN-WIFI-015] Add Wireless Channel Graph and Site Survey feature in Wireless/Site Survey page, 2012/09/21
          insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_SS), 'wlsry.cmd'));
//>> [CTFN-WIFI-015] End
          //SUPPORT_SES
          if ( wireless_ses == '1' ) {
             insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_SES), 'wlses.html'));
          }

          insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_STATION_LIST), 'wlstationlist.cmd'));

       }

       if ( wireless_wapi == '1' ) {
          if (numWl == '1') {
             insDoc(nodeWireless, gLnk('R', getMenuTitle(MENU_WL_WAPI_AS), 'wlwapias.html'));
          }
          else {
             insDoc(wlanMenu, gLnk('R', getMenuTitle(MENU_WL_WAPI_AS), 'wlwapias.html'));
          }
       }
   }

   
   // Configure diagnostics menu
   nodeDiagnostics = insFld(foldersTree, gFld(getMenuTitle(MENU_DIAGNOSTICS), 'diag.html'));

   // Configure management menu
   if(0) {
   nodeMngr = insFld(foldersTree, gFld(getMenuTitle(MENU_MANAGEMENT), 'logintro.html'));
   insFld(nodeMngr, gFld(getMenuTitle(MENU_TL_SYSTEM_LOG), 'logintro.html'));
   if ( snmp == '1' )
   insFld(nodeMngr, gFld(getMenuTitle(MENU_TL_SNMP), 'snmpconfig.html'));
   if ( tr69c == '1' )
      insFld(nodeMngr, gFld(getMenuTitle(MENU_TR69C), 'tr69cfg.html'));
   if ( omci == '1' ) {
      nodeOmci = insFld(nodeMngr, gFld(getMenuTitle(MENU_OMCI_CFG), 'omcicfg.cmd?action=view'));
      insDoc(nodeOmci, gLnk('R', getMenuTitle(MENU_OMCI_GET_SET),'omcicfg.cmd?action=view'));
      insDoc(nodeOmci, gLnk('R', getMenuTitle(MENU_OMCI_CREATE),'omcicreate.cmd?action=view'));
      insDoc(nodeOmci, gLnk('R', getMenuTitle(MENU_OMCI_GET_NEXT),'omcigetnext.cmd?action=view'));
      insDoc(nodeOmci, gLnk('R', getMenuTitle(MENU_OMCI_MACRO),'omcimacro.cmd?action=view'));
      insDoc(nodeOmci, gLnk('R', getMenuTitle(MENU_OMCI_DOWNLOAD),'omcidownload.html'));
      insDoc(nodeOmci, gLnk('R', getMenuTitle(MENU_OMCI_SYSTEM),'omcisystem.html'));
   }
   insFld(nodeMngr, gFld(getMenuTitle(MENU_TL_UPDATE_SOFTWARE), 'upload.html'));
   }
//>> jojopo : end
}

function createBcmMenu(options) {
   var user = options[MENU_OPTION_USER];
   var proto = options[MENU_OPTION_PROTOCOL];
   var ipExt = options[MENU_OPTION_IP_EXTENSION];
   var dhcpen = options[MENU_OPTION_DHCPEN];
   var mocaStats = options[MENU_OPTION_SUPPORT_MOCA];
   var ptm = options[MENU_OPTION_PTMWAN];
   var atm = options[MENU_OPTION_ATMWAN];
   var mocawan = options[MENU_OPTION_MOCAWAN];
   var ethwan = options[MENU_OPTION_ETHWAN];
   var gponwan = options[MENU_OPTION_GPONWAN];
   var eponwan = options[MENU_OPTION_EPONWAN];
   var optical = options[MENU_OPTION_OPTICAL];
//<< [CTFN-MGM-001] Jimmy Wu : for Comtrend's username & password
   var admusername = options[MENU_OPTION_ADM_USERNAME];
   var sptusername = options[MENU_OPTION_SPT_USERNAME];
   var usrusername = options[MENU_OPTION_USR_USERNAME];
//>> [CTFN-MGM-001] End
//<< [CTFN-3G-001] MHTsai: Support 3G feature, 2010/08/09
   var threegwan = options[MENU_OPTION_3G_WAN];
//>> [CTFN-3G-001] End
//<< [CTFN-IPV6-008] Camille Wu: Add IPv6 Network Information and IPv6 Routing in Device info page.
   var ipv6Support = options[MENU_OPTION_IPV6_SUPPORT];
//>> [CTFN-IPV6-008] End
//<< [CTFN-NMIS-006-3] Camille Wu: Display IGMP Proxy entries only if multicast is compiled, 2012/08/07
   var multicast = options[MENU_OPTION_MULTICAST];
//>> [CTFN-NMIS-006-3] End
//<< [CTFN-NMIS-014] Charles Wei: Support to display the NAT sessions on Web GUI and add nat command to show the NAT sessions
//<<  [CTFN-NMIS-014-1] Charles Wei: Add the missing ejGetOther() in menu.html and related modification
   var natSession = options[MENU_OPTION_NAT_SESSION];
//>> [CTFN-NMIS-014-1] End
//>> [CTFN-NMIS-014] End
//<< [CTFN-SYS-022] Support option to hide DSL information and remove PHY/driver version from software version name when ATM/PTM is enabled
 var hidedslopt = options[MENU_OPTION_HIDE_DSL];
//>> [CTFN-SYS-022] End 

   foldersTree = gFld('', 'info.html');
   // device info menu
   nodeDeviceInfo = insFld(foldersTree, gFld(getMenuTitle(MENU_DEVICE_INFO), 'info.html'));
   // device summary menu
   insFld(nodeDeviceInfo, gFld(getMenuTitle(MENU_DEVICE_SUMMARY), 'info.html'));
   // device wan menu
   insFld(nodeDeviceInfo, gFld(getMenuTitle(MENU_DEVICE_WAN), 'wancfg.cmd?action=view'));
   // device statistics menu
   nodeSts = insFld(nodeDeviceInfo, gFld(getMenuTitle(MENU_STATISTICS), 'statsifc.html'));
   insDoc(nodeSts, gLnk('R', getMenuTitle(MENU_ST_LAN), 'statsifc.html'));
   if (mocaStats == '1')
      insDoc(nodeSts, gLnk('R', getMenuTitle(MENU_ST_MOCA), 'statsmoca.cmd?choice=LAN'));
   if (ptm == '1' || atm == '1' || mocawan == '1' ||
       ethwan == '1' || gponwan == '1' || eponwan == '1')
      insDoc(nodeSts, gLnk('R', getMenuTitle(MENU_WAN), 'statswan.cmd'));
//<< [CTFN-SYS-022] Support option to hide DSL information and remove PHY/driver version from software version name when ATM/PTM is enabled
	if ((ptm == '1' || atm == '1')&&hidedslopt=='0') {
//   if (ptm == '1' || atm == '1') {
//>> [CTFN-SYS-022] End 
      insDoc(nodeSts, gLnk('R', getMenuTitle(MENU_ST_ATM), 'statsxtm.cmd'));
      insDoc(nodeSts, gLnk('R', getMenuTitle(MENU_ST_ADSL), 'statsadsl.html'));
   }
   if (optical == '1')
      insDoc(nodeSts, gLnk('R', getMenuTitle(MENU_OPTICAL), 'statsopticifc.html'));
   // device route menu
   insFld(nodeDeviceInfo, gFld(getMenuTitle(MENU_DEVICE_ROUTE), 'rtroutecfg.cmd?action=view'));
   insFld(nodeDeviceInfo, gFld(getMenuTitle(MENU_RT_ARP),'arpview.cmd'));
   // dhcp info
   if (!(proto == 'Bridge' || ipExt == '1') && dhcpen == '1') {
//<< [CTFN-IPV6-011] Camille Wu: Add DHCPv6 leases table in DHCP/Device Info page, 2012/02/22
    nodedh =insFld(nodeDeviceInfo, gFld(getMenuTitle(MENU_DHCPINFO),'dhcpinfo.html'));
       insDoc(nodedh, gLnk('R', getMenuTitle(MENU_DHCP4), 'dhcpinfo.html'));
// << jojopo : dhcpv6 lease table, 2011/07/04
   if (ipv6Support == '1'){
       insDoc(nodedh, gLnk('R', getMenuTitle(MENU_DHCP6), 'dhcpv6_update.cmd'));
   }
//>> [CTFN-IPV6-011] End
//<< [CTFN-NMIS-014] Charles Wei: Support to display the NAT sessions on Web GUI and add nat command to show the NAT sessions
//<<  [CTFN-NMIS-014-1] Charles Wei: Add the missing ejGetOther() in menu.html and related modification
   if (natSession == '1')
//>> [CTFN-NMIS-014-1] End
	  insFld(nodeDeviceInfo, gFld(getMenuTitle(MENU_NAT_SESSION),'cgiNatSession.cmd'));
//>> [CTFN-NMIS-014] End
   }
//<< [CTFN-NMIS-006] TingChun, Display the list of IGMP proxy entries in Device Info, 2010/11/12
//<< [CTFN-NMIS-006-3] Camille Wu: Display IGMP Proxy entries only if multicast is compiled, 2012/08/07
   if ( multicast == '1' ) 
//>> [CTFN-NMIS-006-3] End
      insFld(nodeDeviceInfo, gFld(getMenuTitle(MENU_IGMP_PROXY),'igmp.cmd'));
//>> [CTFN-NMIS-006] End

//<< [CTFN-3G-001] MHTsai: Support 3G feature, 2010/08/09
   if (threegwan == '1') {
      insFld(nodeDeviceInfo, gFld(getMenuTitle(MENU_ST_3G),'stats3g.cmd'));
   }
//>> [CTFN-3G-001] End
//<< [CTFN-IPV6-008] Camille Wu: Add IPv6 Network Information and IPv6 Routing in Device info page.
   if (ipv6Support == '1'){
    nodev6 =insFld(nodeDeviceInfo, gFld(getMenuTitle(MENU_DEVICE_6TITLE), 'v6info.cmd'));
       insDoc(nodev6, gLnk('R', getMenuTitle(MENU_DEVICE_6INFO), 'v6info.cmd'));
//<< [CTFN-IPV6-009] Camille Wu: Support static IPv4/IPv6 neighbor via CLI/GUI and add IPv6 neighbor table in IPv6/Device Info page, 2012/02/17
       insDoc(nodev6, gLnk('R', getMenuTitle(MENU_IPV6_NEIGHBOR_TABLE), 'ipv6neighborview.cmd'));
//>> [CTFN-IPV6-009] End
       insDoc(nodev6, gLnk('R', getMenuTitle(MENU_DEVICE_V6RT), 'v6route.cmd'));
   	}
//>> [CTFN-IPV6-008] End
//<< [CTFN-MGM-001] Jimmy Wu : for Comtrend's username & password
   if ( user == admusername )
      menuAdmin(options);
   else if ( user == sptusername )
      menuSupport(options);
   else if ( user == usrusername )
      menuUser();
//>> [CTFN-MGM-001] End

}
