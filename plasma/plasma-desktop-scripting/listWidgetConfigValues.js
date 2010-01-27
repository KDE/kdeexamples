function enumerateWidgets(c)
{
    widgets = c.widgetIds
    if (widgets.length < 1) {
        print("No widgets")
        return;
    }

    for (i = 0; i < widgets.length; ++i) {
        w = c.widgetById(widgets[i])
        print(w.type)
        keys = w.configKeys;

        if (keys.length > 0) {
            for (j = 0; j < keys.length; ++j) {
                print("    " + keys[j] + " = " + w.readConfig(keys[j], ""))
            }
        }
    }
}

containments = activityIds
for (i = 0; i < containments.length; ++i) {
    c = activityById(containments[i])
    if (c) {
        print("<b>" + c.id + ": " + c.type + "<b>")
        enumerateWidgets(c)
    } else {
        print ("could not find containment id " + id + " using " + func)
    }
}

containments = panelIds
for (i = 0; i < containments.length; ++i) {
    c = panelById(containments[i])
    if (c) {
        print("<b>" + c.id + ": " + c.type + "<b>")
        enumerateWidgets(c)
    } else {
        print ("could not find containment id " + id + " using " + func)
    }
}


