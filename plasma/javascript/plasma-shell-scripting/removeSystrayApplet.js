/* Kubuntu 13.10 changes from networkmanagement to plasma-nm applet.
this script removes networkmanagement from systray which turns out to
be faffy as there is no API for it, we need to find the applet then 
wipe the config setting.

Copyright Jonathan Riddell, jriddell@ubuntu.com 2013-09-13
see LICENSING for copying licence
*/

pids = panelIds;
for (i = 0; i < pids.length; ++i) { //search through the panels
  panel = panelById(pids[i]);
  if (!panel) continue;
  ids = panel.widgetIds;
  for (j = 0; j < ids.length; ++j) { //search through the widgets for systray
    widget = panel.widgetById(ids[j]);
    if (!widget || widget.type != "systemtray") {
      continue;
    }
    //widget var is now the systray
    widget.currentConfigGroup = Array("Applets");
    noOfApplets = widget.configGroups.length;
    var groups = new Array();
    for (k = 0; k < noOfApplets; ++k) {
      groups.push(widget.configGroups[k])
    }
    for (k = 0; k < noOfApplets; ++k) {
      widget.currentConfigGroup = new Array("Applets", groups[k]);
      if (widget.readConfig("plugin") == "org.kde.networkmanagement") {
        widget.writeConfig("plugin",""); //found it at last, wipe it blank
      }
    }
  }
}
