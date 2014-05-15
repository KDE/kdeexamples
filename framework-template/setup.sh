#!/bin/sh
set -e

CMAKELISTS_FILES="CMakeLists.txt src/CMakeLists.txt"

die() {
    echo Error: $* 1>&2
    exit 1
}

usage() {
    cat <<EOF
Usage: setup.sh [OPTIONS] <framework-name> <destination-dir>

Copies template files to destination-dir, using the correct file names. Replaces
all references to the template framework name with framework-name.

framework-name must be in CamelCase.

destination-dir must not exist already.

Options:
  -h, --help        Display this usage message and exit
  --docbook         Add docbook support
  --tr SYSTEM       Select translation system to use
                    SYSTEM must be one of:
                    - ki18n: Use KI18n translation system (default)
                    - qt: Use Qt translation system
                    - none: Do not use any translation system
EOF
    exit 1
}

# When called as "uncomment foo file1", this function turn blocks like this:
#
#   # foo: Uncomment to launch space rocket
#   # /bin/launch
#
#   /bin/land
#
# Into:
#
#   /bin/launch
#
#   /bin/land
uncomment() {
    local marker="$1:"
    local file="$2"
    sed -i "/^ *# *$marker/,+1 {
        # Delete the line which contain the comment with the marker
        /^ *# $marker*/d
        # Uncomment the next line, keeping indentation intact
        s/^\( *\)# */\1/
    }" $file
}

# When called as "rmcomment foo file1", this function turn blocks like this:
#
#   # foo: Uncomment to launch space rocket
#   # /bin/launch
#
#   /bin/land
#
# Into:
#
#   /bin/land
rmcomments() {
    local marker="$1:"
    local file="$2"
    sed -i "/^ *# *$marker/,+1d" $file
}

setup_translation_system() {
    case "$tr" in
    qt)
        echo "Setup Qt translation system"
        rm src/Messages-i18n.sh
        mv src/Messages-qt.sh src/Messages.sh
        for file in $CMAKELISTS_FILES ; do
            uncomment TODO-qt $file
            rmcomments TODO-i18n $file
        done
        ;;
    ki18n)
        echo "Setup KI18n translation system"
        rm src/Messages-qt.sh
        mv src/Messages-i18n.sh src/Messages.sh
        for file in $CMAKELISTS_FILES ; do
            uncomment TODO-i18n $file
            rmcomments TODO-qt $file
        done
        ;;
    none)
        echo "Removing translation system templates"
        rm src/Messages-*.sh
        for file in $CMAKELISTS_FILES ; do
            rmcomments TODO-i18n $file
            rmcomments TODO-qt $file
        done
        ;;
    esac
}

replace_template_names() {
    echo "Replacing template names"
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
}

create_top_level_files() {
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

    echo "Creating metainfo.yaml"
    echo "tier: \"unknown\"" > metainfo.yaml

    echo "Creating .reviewboardrc"
    cat > .reviewboardrc <<EOF
REVIEWBOARD_URL = "https://git.reviewboard.kde.org"
REPOSITORY = 'git://anongit.kde.org/${lowercase_name}'
BRANCH = 'master'
TARGET_GROUPS = 'kdeframeworks'
EOF
}

setup_docbook() {
    for file in $CMAKELISTS_FILES ; do
        if [ "$docbook" = "true" ] ; then
            uncomment TODO-docbook $file
        else
            rmcomments TODO-docbook $file
        fi
        #delete_dual_empty_lines $file
    done
}

# Get template dir
old_pwd=$PWD
cd $(dirname $0)
template_dir=$PWD
cd $old_pwd

# Parse arguments
name=""
dir=""
tr=ki18n
docbook=false

while [ $# -gt 0 ] ; do
    case "$1" in
    -h|--help)
        usage
        ;;
    --docbook)
        docbook=true
        ;;
    --tr)
        shift
        tr="$1"
        case "$tr" in
        qt|ki18n|none)
            ;;
        *)
            die "'$tr' is not a valid value for --tr"
            ;;
        esac
        ;;
    -*)
        die "Unknown option '$1'"
        ;;
    *)
        if [ -z "$name" ] ; then
            name="$1"
        elif [ -z "$dir" ] ; then
            dir="$1"
        else
            die "Too many arguments"
        fi
        ;;
    esac
    shift
done

if [ -z "$dir" ] ; then
    die "Not enough arguments. Try '$(basename $0) --help' for more information."
fi

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
rm $dir/setup.sh $dir/test-setup.sh

cd $dir

replace_template_names
setup_translation_system
setup_docbook
create_top_level_files

cat <<EOF

---------------------------------------------------

All Done. Things to do now:

- Review the generated files

- Edit README.md and metainfo.yaml

- Optionally, add this line to .reviewboardrc:

    TARGET_PEOPLE = 'your_kde_username'

  to be notified when review requests are submitted.
EOF
