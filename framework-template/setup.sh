#!/bin/sh
set -e

die() {
    echo ERROR: $* 1>&2
    exit 1
}

usage() {
    cat <<EOF
Usage: setup.sh <framework-name> <translation-system> <destination-dir>

Copies template files to destination-dir, using the correct file names. Replaces
all references to the template framework name with framework-name.

framework-name must be in CamelCase.

translation-system must be one of "qt", "i18n", "none".

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
if [ $# -ne 3 ] ; then
    echo "Wrong number of arguments."
    echo
    usage
fi

name="$1"
tr="$2"
dir="$3"

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

case "$tr" in
qt|i18n|none)
    ;;
*)
    die "'$tr' is not a valid translation system"
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

# Handle translations
case "$tr" in
qt)
    sed -i 's/XGETTEXT/XGETTEXT_QT/' Messages.sh
    ;;
none)
    rm Messages.sh
    ;;
i18n)
    ;;
esac

echo "Creating README.md"
cat > README.md <<EOF
# $name

## Introduction

TODO: write an introduction about this framework

## Links

- Mailing list: <https://mail.kde.org/mailman/listinfo/kde-frameworks-devel>
- IRC channel: #kde-devel on Freenode
- Git repository: <https://projects.kde.org/projects/frameworks/$lowercase_name/repository>
EOF

echo "Creating ${lowercase_name}.yaml"
echo "tier: \"unknown\"" > ${lowercase_name}.yaml

echo "Creating .reviewboardrc"
cat > .reviewboardrc <<EOF
REVIEWBOARD_URL = "https://git.reviewboard.kde.org"
REPOSITORY = 'git://anongit.kde.org/${lowercase_name}'
BRANCH = 'master'
TARGET_GROUPS = 'kdeframeworks'
EOF

cat <<EOF

Things to do now:

- Edit README.md and ${lowercase_name}.yaml

- Optionally, add this line to .reviewboardrc:

    TARGET_PEOPLE = 'your_kde_username'

  to be notified when review requests are submitted.
EOF
