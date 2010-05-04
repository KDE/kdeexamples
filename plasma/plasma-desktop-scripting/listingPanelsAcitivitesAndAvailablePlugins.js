panels()[0].height = 26

function printWidgets(container)
{
  widgets = container.widgets()
  for (i in widgets) {
    print("        " + i + ": " + widgets[i].type + ", id = " + widgets[i].id + ", version = " + widgets[i].version)
  }
}

print("Versions: Platform => " + platformVersion + ", Application => " + applicationVersion + ", Scripting API => " + scriptingVersion)
print("Available widgets: " + knownWidgetTypes)
print("Available activities: " + knownActivityTypes)
print("Available panels: " + knownPanelTypes)

print("=============");
print("Panels are: ")
p = panels()
for (i in p) {
  print("    " + p[i].type + ", id = " + p[i].id + ", version = " + p[i].version + ", widgets:")
  printWidgets(p[i])
} 

print("=============");
print("Activities are: ")
a = activities()
for (i in a) {
  print("    " + a[i].type + ", id = " + a[i].id + ", version = " + a[i].version + " widgets:") 
  printWidgets(a[i])
}