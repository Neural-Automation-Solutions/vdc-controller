#!/bin/bash

# Name of the executable
executable="vdc-main"

# Check if the program is running
if pgrep "$executable" >/dev/null; then
    echo "Program 'vdc-main' already running at `pidof vdc-main`."
else
    sudo ~/vdc-controller/dist/vdc-main
fi

