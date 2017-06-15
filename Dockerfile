FROM debian:9

ENV DISPLAY :0

RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
RUN apt update &&\
    apt install jackd1\
    cmake\
    gcc\
    g++\
    git\
    pkg-config\
    faust\
    libglfw3-dev\
    libedit-dev\
    libjack-dev\
    jack-keyboard\
    patchage\
    libgles2-mesa-dev -y

# RUN git clone https://github.com/grame-cncm/faust.git /tmp/faust
# WORKDIR /tmp/faust
# RUN make && make install

run echo '/usr/bin/jackd -r -dalsa -r44100 -p128 -n4' >> /root/.jackdrc

WORKDIR /top-1
CMD sh install.sh
#ENTRYPOINT ./bin/tapedeck
