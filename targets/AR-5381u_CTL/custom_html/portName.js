// PLEASE NOTE THAT A SPACE BETWEEN TWO WORDS IS TAKEN AS TWO SEPERATE
// WORDS. PLEASE KEEP THIS FILE CONSISTENT.
//
// For each Linux interface name in the boardparms.c file, add
// a corresponding Linux interface name and a user-friendly name
// of its equivalent that must be displayed on the WEB UI. It is
// best if the new inteface names are added at the end.
// Make sure modifications to portName_L are consistent with
//portName_U and viceversa

 portName_L = [
// Wireless interfac Linux interface name
'wl0',
// USB interface Linux interface name
'usb0',
// Board ID 96368VVW Linux name
'96368VVW|eth0',
'96368VVW|eth1',
'96368VVW|eth2',
'96368VVW|eth3',
// AR-5382u Linux name
'96328A-1341N1|eth0',
'96328A-1341N1|eth1',
'96328A-1341N1|eth2',
'96328A-1341N1|eth3',
// AR-5384u_CTU Linux name
'96328AT-1341N1|eth0',
'96328AT-1341N1|eth1',
'96328AT-1341N1|eth2',
'96328AT-1341N1|eth3',
'96328AT-1341N1|eth4',
// AR-5381u_CTL,8MB Linux name
'96328AT-1341N2|eth0',
'96328AT-1341N2|eth1',
'96328AT-1341N2|eth2',
'96328AT-1341N2|eth3',
'96328AT-1341N2|eth4',
// AR-5381u_JAZ,16MB Linux name
'96328A-1241N|eth0',
'96328A-1241N|eth1',
'96328A-1241N|eth2',
'96328A-1241N|eth3',
// AR-5220u_CTU Linux name
'96328AT-134|eth0',
'96328AT-134|eth1',
'96328AT-134|eth2',
'96328AT-134|eth3',
'96328AT-134|eth4',
// New AR-5381u_CTU,16MB Linux name
'96328AT-1441N|eth0',
'96328AT-1441N|eth1',
'96328AT-1441N|eth2',
'96328AT-1441N|eth3',
'96328AT-1441N|eth4',
// AR-5223u Linux name
'96328AT-1341|eth1',
'96328AT-1341|eth2',
'96328AT-1341|eth3',
'96328AT-1341|eth4',
// AR-5389 Linux name
'96328A-1341N4|eth1',
'96328A-1341N4|eth2',
'96328A-1341N4|eth3',
'96328A-1341N4|eth4',
// Board ID 96362ADVNG Linux name
'96362ADVNG|eth0',
'96362ADVNG|eth1',
'96362ADVNG|eth2',
'96362ADVNG|eth3',
'96362ADVNG|eth4'
];

var portName_U = [
// Wireless interface user-friendly name
'wl0',
// USB user-friendly name
'USB',
// Board ID 96368VVW user-friendly name
'96368VVW|ENET1',
'96368VVW|ENET2',
'96368VVW|ENET3',
'96368VVW|ENET4',
// AR-5382u user-friendly name
'96328A-1341N1|ENET1',
'96328A-1341N1|ENET2',
'96328A-1341N1|ENET3',
'96328A-1341N1|ENET4',
// AR-5384u_CTU user-friendly name
'96328AT-1341N1|ETHWAN',
'96328AT-1341N1|LAN1',
'96328AT-1341N1|LAN2',
'96328AT-1341N1|LAN3',
'96328AT-1341N1|LAN4',
// AR-5381u_CTL,8MB user-friendly name
'96328AT-1341N2|ETHWAN',
'96328AT-1341N2|LAN1',
'96328AT-1341N2|LAN2',
'96328AT-1341N2|LAN3',
'96328AT-1341N2|LAN4',
// AR-5381u_JAZ,16MB Linux name
'96328A-1241N|LAN1',
'96328A-1241N|LAN2',
'96328A-1241N|LAN3',
'96328A-1241N|LAN4',
// AR-5220u_CTU user-friendly name
'96328AT-134|ETHWAN',
'96328AT-134|LAN1',
'96328AT-134|LAN2',
'96328AT-134|LAN3',
'96328AT-134|LAN4',
// New AR-5381u_CTU,16MB user-friendly name
'96328AT-1441N|ETHWAN',
'96328AT-1441N|LAN1',
'96328AT-1441N|LAN2',
'96328AT-1441N|LAN3',
'96328AT-1441N|LAN4',
// AR-5223u Linux name
'96328AT-1341|LAN1',
'96328AT-1341|LAN2',
'96328AT-1341|LAN3',
'96328AT-1341|LAN4',
// AR-5389 Linux name
'96328A-1341N4|ETH1',
'96328A-1341N4|ETH2',
'96328A-1341N4|ETH3',
'96328A-1341N4|ETH4',
// Board ID 96362ADVNG user-friendly name
'96362ADVNG|ENET1',
'96362ADVNG|ENET2',
'96362ADVNG|ENET3',
'96362ADVNG|ENET4',
'96362ADVNG|ENET5'
];

function getUNameByLName(name) {
   var index = 0;
   var uName   = '';

   // SafetyNet if someone sends a name without prefixing the
   // board ID and |, then return that name.
   if (name.indexOf('|') == -1)
      return name;
      
   /*Wlan naming: Could be a better name*/
   if (name.indexOf('wl0.3') != -1) {
      return 'wl0_Guest3';
   }
   else if (name.indexOf('wl0.2') != -1) {
      return 'wl0_Guest2';
   }
   else if (name.indexOf('wl0.1') != -1) {
      return 'wl0_Guest1';
   }
   else if (name.indexOf('wl0') != -1) {
      return 'wlan0';
   }
    else if (name.indexOf('wl1.3') != -1) {
      return 'wl1_Guest3';
   }
    else if (name.indexOf('wl1.2') != -1) {
      return 'wl1_Guest2';
   }
    else if (name.indexOf('wl1.1') != -1) {
      return 'wl1_Guest1';
   }
    else if (name.indexOf('wl1') != -1) {
      return 'wlan1';
   }

   if (name.indexOf('usb0') != -1) {
      return 'USB';
   }
   for (index = 0; index < portName_L.length; index++) {
      if (portName_L[index] == name) {
         uName = portName_U[index].split('|');
         return uName[1];
      }
   }
   uName = name.split('|');
   return uName[1];
}

function getLNameByUName(name) {
   var index = 0;
   var brdIntf = name.split('|');
   var lName   = '';
   var uName   = '';

   // SafetyNet if someone sends a name without prefixing the
   // board ID and |, then return that name.
   if (name.indexOf('|') == -1)
      return name;
      
   if (name.indexOf('wl0_Guest3') != -1)
      return 'wl0.3';
   if (name.indexOf('wl0_Guest2') != -1)
      return 'wl0.2';
   if (name.indexOf('wl0_Guest1') != -1)
      return 'wl0.1';
   if (name.indexOf('wlan0') != -1)
      return 'wl0';
   if (name.indexOf('wl1_Guest3') != -1)
      return 'wl1.3';
   if (name.indexOf('wl1_Guest2') != -1)
      return 'wl1.2';
   if (name.indexOf('wl1_Guest1') != -1)
      return 'wl1.1';
   if (name.indexOf('wlan1') != -1)
      return 'wl1';
      
   if (name.indexOf('USB') != -1)
      return 'usb0';
   for (index = 0; index < portName_U.length; index++) {
      uName = portName_U[index].split('|');
      if (portName_U[index] == name) {
         lName = portName_L[index].split('|');
         return lName[1];
      }
   }
   lName = name.split('|');
   return lName[1];
}
