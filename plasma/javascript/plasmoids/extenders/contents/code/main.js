var ext

plasmoid.initExtenderItem = function(item)
{
    ext = item
    var button = new PushButton
    button.text = i18n("Hello")
    ext.widget = button
    print(i18n("Widget in %1 is %2", item.name, ext.name))
}

var e = plasmoid.extender()
if (e.hasItem("yes!")) {
    print(i18n("We already have our extender, it will be recreated for us. Expect a call to initEtenderItem."));
} else {
    // new ExtenderItems are automatically added to our widget's Extender
    ext = new ExtenderItem
    ext.name = "yes!"
    plasmoid.initExtenderItem(ext)
}

var layout = new LinearLayout
if (ext) {
    layout.addItem(ext)
}

