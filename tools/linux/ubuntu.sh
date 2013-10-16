#!/usr/bin/env bash
###############################
# Bash Script to set up linux #
# development environment.    #
###############################

# Stop on error
set -e

# Location to store projects
PROJECTS_DIR="~/Projects"

# Repo vars
GIT_REPO_URL="https://github.com/Exeter-College-Game-Development/ECGame.git"
GIT_REPO_NAME="ECGame"

main(){
    echo "We need your permission to install the tools?"
    sudo install
    mkdir_project
    git clone $GIT_REPO_URL $GIT_REPO_NAME
}

install(){
    echo "installing...."
    # Play animation in background
    animation &
    
    # Function is run under `sudo` so
    # password is not asked again.
    # Also stdout is redirected to null.
    sudo apt-get install build-essential git libsdl1.2-dev > /dev/null
    
    # stop animation
    animation_running=0
}

# Moves and cd's to $PROJECTS_DIR
mkdir_project(){
    mkdir $PROJECTS_DIR
    cd $PROJECTS_DIR
}




## Just animation code below here
#
#
#
#
#
# Waiting animation
IMGS=(
"
 +      o     +              o    \n\
     +             o     +       +\n\
 o          +                     \n\
     o  +           +        +    \n\
 +        o     o       +        o\n\
 -_-_-_-_-_-_-_,------,      o    \n\
 _-_-_-_-_-_-_-|   /\_/\          \n\
 -_-_-_-_-_-_-~|__( ^ .^)  +     +\n\
 _-_-_-_-_-_-_-\"\"  \"\"         \n\
 +      o         o   +       o   \n\
     +         +                  \n\
 o        o         o      o     +\n\
     o           +                \n\
 +      +     o        o      +   \n
" "
     o  +           +        +    \n\
 o          +                    o\n\
     o                 +          \n\
 +      o     +              o    \n\
  o     +        o               +\n\
 _-_-_-_-_-_-_-,------,  o      + \n\
 -_-_-_-_-_-_-_|   /\_/\    +     \n\
 _-_-_-_-_-_-_~|__( ^ .^)     o   \n\
 -_-_-_-_-_-_-_  \"\"  \"\"       \n\
 +      +     o        o      +   \n\
 o        +                o     +\n\
 +      o         +     +       o \n\
     +         +                  \n\
        +           o        +    \n
" )
REFRESH="0.5"

sigtrap(){
    # make cursor visible again
    tput cvvis

    # reset cursor
    tput_loop "cud1"

    # stop audio
    #kill `pgrep vlc`
    #kill `pgrep mplayer` 2&> /dev/null

    echo "caught signal SIGINT(CTRL+C), quitting ..."
    exit 1
}

animation_running=1
animation(){
    # ^C abort, script cleanup
    trap sigtrap INT
    # hide the cursor
    tput civis
    # main loop, pretty self explanatory
    while [ $animation_running ]; do for x in "${IMGS[@]}"; do
        echo -ne $x
        tput_loop "cuu1"
        sleep $REFRESH
    done; done
}

#
#
#
###################################
main()

