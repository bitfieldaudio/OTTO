#!/bin/bash
# Change the path on the second -v to wherever you have the TOP-1 git project at
# AKA update /opt/TOP-1 to your actual location, this was just so I could be lazy
docker run -it --rm --privileged=true\
	--device=/dev/snd:/dev/snd\
	--volume /tmp/.X11-unix:/tmp.X11-unix\
	--volume /opt/TOP-1:/top-1 tdball/top-1\
	bash
