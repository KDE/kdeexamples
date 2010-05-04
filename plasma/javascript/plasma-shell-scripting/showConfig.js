a = activityForScreen(0)

if (a) {
    a.showConfigurationInterface()
    if (a.widgetIds.length > 0) {
        w = a.widgetById(a.widgetIds[0])
        if (w) {
            w.showConfigurationInterface()
        }
    }
}
