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
// Board ID 96338SV Linux name
'96338SV|eth0',
//Board ID 96338L-2M-8M Linux name
'96338L-2M-8M|eth0',
// Board ID 96358GW Linux name
'96358GW|eth0',
'96358GW|eth1',
'96358GW|eth1.2',
'96358GW|eth1.3',
'96358GW|eth1.4',
// Board ID 96358VW Linux name
'96358VW|eth0',
'96358VW|eth1',
'96358VW|eth1.2',
'96358VW|eth1.3',
'96358VW|eth1.4',
// Board ID 96358VW2 Linux name
'96358VW2|eth0',
'96358VW2|eth1',
'96358VW2|eth1.2',
'96358VW2|eth1.3',
'96358VW2|eth1.4',
// Board ID 96368VVW Linux name
'96368VVW|eth0',
'96368VVW|eth1',
'96368VVW|eth2',
'96368VVW|eth3',
// Board ID 96362ADVNG Linux name
'96362ADVNG|eth0',
'96362ADVNG|eth1',
'96362ADVNG|eth2',
'96362ADVNG|eth3',
'96362ADVNG|eth4',
// Board ID 96368M-123 linux name
'96368M-123|eth0',
'96368M-123|eth1',
'96368M-123|eth2',
'96368M-123|eth3',
'96368M-123|eth4', 
// Board ID 96368M-1331N linux name
'96368M-1331N|eth0',
'96368M-1331N|eth1',
'96368M-1331N|eth2',
'96368M-1331N|eth3',
'96368M-1331N|eth4', 
// Board ID 96368M-1331N1 linux name
'96368M-1331N1|eth0',
'96368M-1331N1|eth1',
'96368M-1331N1|eth2',
'96368M-1331N1|eth3',
'96368M-1331N1|eth4',
//<< Daniel Su: Fix  names of ETH port are incorrect 
// Board ID 96368MBG-133 for NL-5602 linux name
'96368MBG-133|eth0',
'96368MBG-133|eth1',
'96368MBG-133|eth2',
'96368MBG-133|eth3',
// Board ID 96368MBG-133-1 for NL-3101 linux name
'96368MBG-133-1|eth0',
'96368MBG-133-1|eth1',
'96368MBG-133-1|eth2',
'96368MBG-133-1|eth3',
//>> Daniel Su End
// Board ID 96368MBG-1341N for NL-5600u linux name
'96368MBG-1341N|eth0',
'96368MBG-1341N|eth1',
'96368MBG-1341N|eth2',
'96368MBG-1341N|eth3',
'96368MBG-1341N|eth4',
// Board ID 96368MB-1341N-1 for NL-3100u linux name
'96368MB-1341N-1|eth0',
'96368MB-1341N-1|eth1',
'96368MB-1341N-1|eth2',
'96368MB-1341N-1|eth3',
'96368MB-1341N-1|eth4',
// Board ID 96368MBI_1441N
'96368MBI_1441N|eth1',
'96368MBI_1441N|eth2',
'96368MBI_1441N|eth3',
'96368MBI_1441N|eth4',
// Board ID 96368VB-1441N
'96368VB-1441N|eth0',
'96368VB-1441N|eth1',
'96368VB-1441N|eth2',
'96368VB-1441N|eth3',
'96368VB-1441N|eth4',
'96368VB-1441N|eth5',
// Board ID 963168VB-1441N
'963168VB-1441N|eth0',
'963168VB-1441N|eth1',
'963168VB-1441N|eth2',
'963168VB-1441N|eth3',
// Board ID 963168MB-1461N
'963168MB-1461N|eth0',
'963168MB-1461N|eth1',
'963168MB-1461N|eth2',
'963168MB-1461N|eth3',
];

var portName_U = [
// Wireless interface user-friendly name
'wl0',
// USB user-friendly name
'USB',
// Board ID 96338SV user-friendly name
'96338SV|ENET',
//Board ID 96338L-2M-8M user-friendly name
'96338L-2M-8M|ENET',
// Board ID 96358GW user-friendly name
'96358GW|ENET4',
'96358GW|ENET(1-3)',
'96358GW|ENET1',
'96358GW|ENET2',
'96358GW|ENET3',
// Board ID 96358VW user-friendly name
'96358VW|ENET4',
'96358VW|ENET(1-3)',
'96358VW|ENET1',
'96358VW|ENET2',
'96358VW|ENET3',
// Board ID 96358VW2 user-friendly name
'96358VW2|ENET4',
'96358VW2|ENET(1-3)',
'96358VW2|ENET1',
'96358VW2|ENET2',
'96358VW2|ENET3',
// Board ID 96368VVW user-friendly name
'96368VVW|ENET1',
'96368VVW|ENET2',
'96368VVW|ENET3',
'96368VVW|ENET4',
// Board ID 96362ADVNG user-friendly name
'96362ADVNG|ENET1',
'96362ADVNG|ENET2',
'96362ADVNG|ENET3',
'96362ADVNG|ENET4',
'96362ADVNG|ENET5',
// Board ID 96368M-123 linux name
'96368M-123|ENET0',
'96368M-123|ENET1',
'96368M-123|ENET2',
'96368M-123|ENET3',
'96368M-123|ENET4', 
// Board ID 96368M-1331N linux name
'96368M-1331N|ETHWAN',
'96368M-1331N|ENET1',
'96368M-1331N|ENET2',
'96368M-1331N|ENET3',
'96368M-1331N|ENET4', 
// Board ID 96368M-1331N1 linux name
'96368M-1331N1|ETHWAN',
'96368M-1331N1|ENET1',
'96368M-1331N1|ENET2',
'96368M-1331N1|ENET3',
'96368M-1331N1|ENET4',
// Board ID 96368MBG-133 for NL-5602 linux name
'96368MBG-133|ENET1',
'96368MBG-133|ENET2',
'96368MBG-133|ENET3',
'96368MBG-133|ENET4',
// Board ID 96368MB-133-1 for NL-3101 linux name
'96368MBG-133-1|ENET1',
'96368MBG-133-1|ENET2',
'96368MBG-133-1|ENET3',
'96368MBG-133-1|ENET4',
// Board ID 96368MBG-1341N for NL-5600u linux name
'96368MBG-1341N|ETHWAN',
'96368MBG-1341N|ENET1',
'96368MBG-1341N|ENET2',
'96368MBG-1341N|ENET3',
'96368MBG-1341N|ENET4',
// Board ID 96368MB-1341N-1 for NL-3100u linux name
'96368MB-1341N-1|ETHWAN',
'96368MB-1341N-1|ENET1',
'96368MB-1341N-1|ENET2',
'96368MB-1341N-1|ENET3',
'96368MB-1341N-1|ENET4',
// Board ID 96368MBI_1441N
'96368MBI_1441N|ENET1',
'96368MBI_1441N|ENET2',
'96368MBI_1441N|ENET3',
'96368MBI_1441N|ENET4',
// Board ID 96368VB-1441N
'96368VB-1441N|ETHWAN',
'96368VB-1441N|ENET1',
'96368VB-1441N|ENET2',
'96368VB-1441N|ENET3',
'96368VB-1441N|ENET4',
'96368VB-1441N|HPNA',
// Board ID 963168VB-1441N
'963168VB-1441N|ENET1',
'963168VB-1441N|ENET2',
'963168VB-1441N|ENET3',
'963168VB-1441N|ENET4',
// Board ID 963168MB-1461N
'963168MB-1461N|ETHWAN',
'963168MB-1461N|ENET1',
'963168MB-1461N|ENET2',
'963168MB-1461N|ENET3',
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
