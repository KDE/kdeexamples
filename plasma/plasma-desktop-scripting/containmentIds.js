// screen geometries
var i = 0
while (i < screenCount()) {
    var geom = screenGeometry(i)
    print("screen " + i + " is " + geom.width() + "x" + geom.height())
    ++i
}

// containments
print("panels are: " + panelIds())
print("activities are: " + activityIds())

var panel = panelById(panelIds()[0])
print("panel id is " + panel.id)
print("panel name is " + panel.name)
print("panel type is " + panel.type)
