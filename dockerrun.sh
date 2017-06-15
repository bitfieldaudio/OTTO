#!/bin/bash
# Change the path on the second -v to wherever you have the TOP-1 git project at
# AKA update /opt/TOP-1 to your actual location, this was just so I could be lazy
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

xhost +local:root
docker run -it --rm --privileged=true\
    --env="DISPLAY" \
    --env="QT_X11_NO_MITSHM=1" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    --device=/dev/snd:/dev/snd\
    --volume $DIR:/top-1 top-1/topisani\

xhost -local:root
