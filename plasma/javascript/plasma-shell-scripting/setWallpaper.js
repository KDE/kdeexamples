a = activityForScreen(0)

if (a) {
    // set a plugin, in this case the standard image handler
    a.wallpaperPlugin = 'image'

    // set a mode; the image plugin has both SingleImage and Slideshow
    // modes. in the configuration user interface these show up as two
    // separate options in the wallpaper types list
    a.wallpaperMode = 'SingleImage'

    // now lets set some configuration details; these are just the
    // entries as they appear in the -appletsrc configuration file.
    // we begin by setting the config group, which is in a subgroup of
    //[Wallpapers] that is named after the plugin
    a.currentConfigGroup = Array('Wallpaper', 'image')

    // wallpaper image paths can be full paths or the name of a wallpaper
    // package that is installed to one of the standard wallpaper
    // directories
    a.writeConfig('wallpaper', 'Horos')

    // other possible entries for the image wallpaper plugin include
    // wallpaperoclor, wallpaperposition, userswallpapers, slidepaths
    // and slideTimer. an easy way to discover these keys is to run
    // plasmawallpaperviewer with the desired plugin, right click to
    // call up the configuration, set some values and then look in the
    // plasmawallpaperviewerrc file.
}
