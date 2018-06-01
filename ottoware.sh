# File Name: ottoware.sh
# Author: Yunpeng Xu
# Mail: yunpeng.xu@aptiv.com
# Created Time: 03/27/2018
#!/bin/bash

CMD=$0
ACTION=$1
ARGUMENT=$2

# ssh config on your local machine
HOST=QNX
SSH_CONFIG=~/.ssh/config
# read User and HostName from your ssh config file
User=$(awk '/^Host QNX$/{x=1}x&&/User/{print $2;exit}' ${SSH_CONFIG})
HostName=$(awk '/^Host QNX$/{x=1}x&&/HostName/{print $2;exit}' ${SSH_CONFIG})

# setting on remote QNX virtual machine
QNX_OTTO_DIR=/home/qnxuser/ottoware

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

    cd $CURR_DIR/lib
    if [ ! -d "$CURR_DIR/lib/qnx" ]; then
        mkdir $CURR_DIR/lib/qnx
        if [ ! -d "$CURR_DIR/lib/qnx/interfaces" ]; then
            mkdir -p $CURR_DIR/lib/qnx/interfaces 
        fi
    fi

    if [ ! -d "$CURR_DIR/lib/ubuntu" ]; then
        mkdir $CURR_DIR/lib/ubuntu
        if [ ! -d "$CURR_DIR/lib/ubuntu/interfaces" ]; then
            mkdir -p $CURR_DIR/lib/ubuntu/interfaces
        fi
    fi

    cd $CURR_DIR/bin
    if [ ! -d "$CURR_DIR/bin/qnx" ]; then
        mkdir $CURR_DIR/bin/qnx
    fi

    if [ ! -d "$CURR_DIR/bin/ubuntu" ]; then
        mkdir $CURR_DIR/bin/ubuntu
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

# ottoware scp - scp all the files under folder lib/ and bin/ to QNX platoform
ottoware_scp()
{
    check_path;
    fill_argument;

    echo -e "${YELLOW}Make sure you have already created the correct dir in the virtual machine${NC}"
    echo -e "${YELLOW}You shall create ~/ottoware, ~/ottoware/config ~/ottoware/lib/qnx ~/ottoware/bin/qnx in advance${NC}\n"
   
    echo -e "${YELLOW}transfer ottoware/lib folder to QNX${NC}"
    scp -r ${CURR_DIR}/lib/qnx ${User}@${HostName}:${QNX_OTTO_DIR}/lib

    echo -e "${YELLOW}transfer ottoware/bin folder to QNX${NC}"
    scp -r ${CURR_DIR}/bin/qnx ${User}@${HostName}:${QNX_OTTO_DIR}/bin

    echo -e "${GREEN}All the files specified are transfered!${NC}"
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
    echo "ottoware clean     -- ./ottoware.sh clean [ALL (default) or QNX or UBUNTU]"
    echo "ottoware scp       -- ./ottoware.sh scp [LIBBIN (library + binary, default) or ALL (library + binary + config)] only for QNX platform"
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
        "scp")
            ottoware_scp;;
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
