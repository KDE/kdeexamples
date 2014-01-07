#!/bin/sh
set -e

die() {
    echo ERROR: $* 1>&2
    exit 1
}

usage() {
    cat <<EOF
Usage: setup.sh <framework-name> <destination-dir>

Copies template files to destination-dir, using the correct file names. Replaces
all references to the template framework name with framework-name.

framework-name must be in CamelCase.

destination-dir must not exist already.
EOF
    exit 1
}

# Get template dir
old_pwd=$PWD
cd $(dirname $0)
template_dir=$PWD
cd $old_pwd

# Check command line arguments
if [ $# -ne 2 ] ; then
    usage
fi

name="$1"
dir="$2"

if [ -e "$dir" ] ; then
    die "'$dir' already exists"
fi

case "$name" in
[A-Z]*)
    ;;
*)
    die "Framework name '$name' must start with a capitalized letter"
    ;;
esac

# if we have KFooBar, kill the K for KF5FooBar
kf5name="KF5$(echo $name | sed -e "s/^K//")"

# Copy files
lowercase_name=$(echo $name | tr A-Z a-z)
uppercase_name=$(echo $name | tr a-z A-Z)

echo "Copying files to $dir"
cp -r $template_dir $dir
rm $dir/setup.sh

echo "Replacing template names"
cd $dir
find -type f | while read file ; do
    sed -i \
        -e "s/KF5FooBar/$kf5name/g" \
        -e "s/FooBar/$name/g" \
        -e "s/foobar/$lowercase_name/g" \
        -e "s/FOOBAR/$uppercase_name/g" \
        $file

    # Rename files matching *FooBar*
    case "$file" in
    *FooBar*)
        mv $file $(echo $file | sed -e "s/KF5FooBar/$kf5name/" -e "s/FooBar/$name/")
        ;;
    *)
        ;;
    esac
done
