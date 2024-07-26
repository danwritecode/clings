#!/bin/bash


# Install and upgrade
echo "Installing build-essential..."
apt-get update
apt-get install -y build-essential

if ! command_exists tmux; then
    echo "tmux is not installed. Installing tmux..."
    apt-get install -y tmux
fi

#check if we need to clone
if [ ! -d "clings" ]; then
    echo "clings directory not found. Cloning the repository..."
    git clone https://github.com/danwritecode/clings.git
    cd clings
    make
    cd ..
fi

#tmux work
tmux new-session -d -s clings
tmux split-window -h
tmux send-keys -t 0 "cd clings/exercises/01_welcome && vim hello_world.c" C-m

tmux send-keys -t 1 "cd clings && echo 'Ready to run clings. Type ./clings to start.'" C-m

tmux attach-session -d -t clings


