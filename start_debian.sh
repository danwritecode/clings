#!/bin/bash

# Check if packages are installed
is_package_installed() {
    dpkg -s "$1" &> /dev/null
}

# Confirmation logic
confirm_install() {
    read -p "You don't have $1 installed. Do you want to install it now? (y/n) " REPLY
    case $REPLY in
        [Yy]* ) return 0;;
        * ) return 1;;
    esac
}

# build-essential
if ! is_package_installed build-essential; then
    if confirm_install "build-essential"; then
        echo "Installing build-essential..."
        sudo apt-get update
        sudo apt-get install build-essential
    else
        echo "build-essential is required but not installed. Exiting."
        exit 1
    fi
fi

# tmux
if ! which tmux > /dev/null 2>&1; then
    if confirm_install "tmux"; then
        echo "Installing tmux..."
        sudo apt-get install tmux
    else
        echo "tmux is required but not installed. Exiting."
        exit 1
    fi
fi

# git
if ! which git > /dev/null 2>&1; then
    if confirm_install "git"; then
        echo "Installing git..."
        sudo apt-get install git
    else
        echo "git is required but not installed. Exiting."
        exit 1
    fi
fi

# Check if we need to clone
if [ ! -d "clings" ]; then
    echo "clings directory not found. Cloning the repository..."
    git clone https://github.com/danwritecode/clings.git
    cd clings
    make
    cd ..
fi

# tmux work (split into two windows and run clings)
tmux new-session -d -s clings
tmux split-window -h
tmux send-keys -t 0 "cd clings/exercises/01_welcome && vim hello_world.c" C-m
tmux send-keys -t 1 "cd clings && echo 'Ready to run clings. Type ./clings to start.'" C-m
tmux attach-session -d -t clings
