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
    sudo echo "We need your permission to install the tools."
    inst

    mkdir_project
    git clone $GIT_REPO_URL $GIT_REPO_NAME
}

inst(){
    echo "installing...."
    # Play animation in background
    animation &
    
    # Function is run under `sudo` so
    # password is not asked again.
    # Also stdout is redirected to null.
    sudo apt-get install build-essential git libsdl1.2-dev -y > /dev/null
    
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

# count lines of first ascii picture in array
LINES_PER_IMG=$(( $(echo $IMGS[0] | sed 's/\\n/\n/g' | wc -l) + 1 ))

# tput $1 LINES_PER_IMG times, used for cuu1(cursor up) cud1(cursor down)
tput_loop() { for((x=0; x < $LINES_PER_IMG; x++)); do tput $1; done; }

sigtrap(){
    # make cursor visible again
    tput cvvis

    # reset cursor
    tput_loop "cud1"

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
        clear
        echo -ne $x
        tput_loop "cuu1"
        sleep $REFRESH
    done; done
}

#
#
#
###################################
main

