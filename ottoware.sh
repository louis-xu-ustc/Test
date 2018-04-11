# File Name: ottoware.sh
# Author: Yunpeng Xu
# Mail: yunpeng.xu@aptiv.com
# Created Time: 03/27/2018
#!/bin/bash

CMD=$0
ACTION=$1
ARGUMENT=$2

# the path of ottoware.sh
CURR_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DEFAULT_PLATFORM=QNX

# check ottoware path
check_path() 
{
    cd $CURR_DIR
    if [ ! -d "$CURR_DIR/build" ]
    then
        mkdir $CURR_DIR/build
    fi
}

# compile ottoware
ottoware_make() 
{
    check_path;
    if [ -z "${ARGUMENT}" ];
        then 
            ARGUMENT=$DEFAULT_PLATFORM
    fi
    echo "Platform is set to be '$ARGUMENT'"
    
    cd $CURR_DIR/build
    cmake ../ -DCMAKE_BUILD_PLATFORM=$ARGUMENT
    make
    echo "ottoware make is done!"
}

# clean the repo
ottoware_clean() 
{
    check_path;
    cd $CURR_DIR/build
    make clean
    echo "ottoware cleaned!"
}

# ottoware cscope
ottoware_cscope ()
{
    OTTO=$CURR_DIR
    find $OTTO                                                                \
        -path "$OTTO/src" -prune -o                                          \
        -name "*.[chxsS]" -print > $OTTO/cscope.files
    cscope -bcqR -I $OTTO/cscope.files
    if [ $? -ne 0 ]
    then              
        echo "failed to create cscope.files"   
    fi
}

#ottoware.sh usage introduction
usage() 
{
    echo "ottoware command   -- ottoware.sh command"
    echo "ottoware help      -- ./ottoware.sh help"
    echo "ottoware make      -- ./ottoware.sh make [QNX (default) or UBUNTU]"
    echo "ottoware clean     -- ./ottoware.sh clean"
    echo "ottoware cscope    -- ./ottoware.sh cscope"
}

#main function
main () 
{
    case $ACTION in
        "make")
            ottoware_make;;
        "clean")
            ottoware_clean;;
        "cscope")
            ottoware_cscope;;
        "help")
            usage;;
        *)
            usage;
            exit;
    esac
}

main
