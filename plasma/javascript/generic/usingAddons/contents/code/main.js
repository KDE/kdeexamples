// we create a function to use to listen to addonCreated events
function addonCreated(addon)
{
    // now we'll access a custom function in the addon, proving it worked!
    textArea.append(i18n("Addon says: %1", addon.toString()))
    if (addon.svg) {
        var svg = new SvgWidget
        svg.svg = addon.svg
        layout.addItem(svg)
    }

    // in real world usage, we may add this addon to a global Array or record its
    // existence in some other way for later usage
}

// now we register the function as an event listener with the right event name
// if we didn't care to actually do things with the addons from this script, we
// wouldn't need to do this; most times, though, we usually want to hang on to
// the addon object to do fun things with it
plasmoid.addEventListener("addonCreated", addonCreated)

// create a small little UI here
var layout = new LinearLayout
layout.orientation = QtVertical
var textArea = new TextEdit
layout.addItem(textArea)

textArea.readOnly = true
textArea.append(i18n("Loading addons..."))

// this maps to the X-KDE-PluginInfo-Category= entry in the addon's .desktop file entry
var addonType = "org.kde.plasma.javascript-addons-example"

// we request the list of all addons
var addons = plasmoid.listAddons(addonType)

if (addons.length < 1) {
    // uh-oh, something didn't work!
    textArea.append(i18n("You probably need to run `plasmapkg -t Plasma/JavascriptAddon -i exampleAddon && kbuildsycoca4`"))
} else {
    textArea.append(i18np("number of addons: 1", "number of addons: %1", addons.length))
    for (i in addons) {
        // an addon has a user visible name and an id; the id is used to load the addon
        textArea.append(i18n("Addon: ") + addons[i].name)
        plasmoid.loadAddon(addonType, addons[i].id)
    }
}

