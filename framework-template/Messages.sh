#!bin/sh

# Invoke the extractrc script on all .ui, .rc, and .kcfg files in the sources.
# The results are stored in a pseudo .cpp file to be picked up by xgettext.
lst=`find src -name \*.rc -o -name \*.ui -o -name \*.kcfg`
if [ -n "$lst" ] ; then
    $EXTRACTRC $lst >> rc.cpp
fi

# If your framework contains tips-of-the-day, call preparetips as well.
if [ -f "data/tips" ] ; then
    ( cd data && $PREPARETIPS > ../tips.cpp )
fi

# Call xgettext on all source files.
$XGETTEXT `find src -name \*.cpp -o -name \*.h -name \*.qml` -o $podir/foobar.pot
