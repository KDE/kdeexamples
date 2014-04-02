# What are these files?

These template files can be used to create a new framework.

You can do so by running

    ./setup.sh <MyFramework> <translation-system> </destdir/myframework>

Where <translation-system> is either "qt", "i18n" or "none.

This command copies the template files to `/destdir/myframework` and perform the
appropriate renames.

For this to be useful it has to be kept updated, I am going to do my best there,
but if you spot anything strange or outdated in there, please notify the
kde-frameworks-devel mailing list and/or fix it.

Note that the templates themselves are "buildable": you can create a build
directory, point cmake to the "template" directory and run "make install" to
build and install a `libFooBar.so`.
