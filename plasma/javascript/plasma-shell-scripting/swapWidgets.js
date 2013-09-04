p = panelById(panelIds[0])
if (!p) {
    exit()
}

ids = p.widgetIds
targetIndex = -1
kickoff = 0;

for (i = 0; i < ids.length; ++i) {
    w = p.widgetById(ids[i])
    if (w) {
        if (w.type == 'launcher' && !kickoff) {
            kickoff = w
        } else if (w.type == 'notifier') {
            targetIndex = w.index
        }
    }

    if (targetIndex != -1 && kickoff) {
        kickoff.index = targetIndex
        break
    }
}

