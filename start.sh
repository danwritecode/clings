#!/bin/bash


# Install build-essential
echo "Installing build-essential..."
apt-get update
apt-get install -y build-essential

# Check if tmux is installed, if not, install it
if ! command_exists tmux; then
    echo "tmux is not installed. Installing tmux..."
    apt-get install -y tmux
fi

# Check if the clings directory exists
if [ ! -d "clings" ]; then
    echo "clings directory not found. Cloning the repository..."
    git clone https://github.com/danwritecode/clings.git
    cd clings
    make
    cd ..
fi

# Create a new tmux session
tmux new-session -d -s clings

# Split the window vertically
tmux split-window -h

# In the left pane, open hello_world.c in vim
tmux send-keys -t 0 "cd clings/exercises/01_welcome && vim hello_world.c" C-m

# In the right pane, navigate to the clings directory and prepare to run clings
tmux send-keys -t 1 "cd clings && echo 'Ready to run clings. Type ./clings to start.'" C-m

# Attach to the tmux session
tmux attach-session -d -t clings


#!/bin/bash

# Function to check if a command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Check if tmux is installed
if ! command_exists tmux; then
    echo "tmux is not installed. Please install it and try again."
    exit 1
fi

# Check if the clings directory exists
if [ ! -d "clings" ]; then
    echo "clings directory not found. Cloning the repository..."
    git clone https://github.com/danwritecode/clings.git
    cd clings
    make
    cd ..
fi

# Create a new tmux session
tmux new-session -d -s clings

# Split the window vertically
tmux split-window -h

# In the left pane, open hello_world.c in vim
tmux send-keys -t 0 "cd clings/exercises/01_welcome && vim hello_world.c" C-m

# In the right pane, navigate to the clings directory and prepare to run clings
tmux send-keys -t 1 "cd clings && echo 'Ready to run clings. Type ./clings to start.'" C-m

# Attach to the tmux session
tmux attach-session -d -t clings