a = activityForScreen(0)

if (a) {
    a.addWidget("clock")
    p = panelById(panelIds[0])

    if (p) {
        for (i = 0; i < p.widgetIds.length; ++i) {
            w = p.widgetById(p.widgetIds[i])
                print (w.type)
            if (w.type == 'launcher') {
                a.addWidget(w);
            }
        }
    }
}
