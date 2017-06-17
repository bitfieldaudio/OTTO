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
    libglfw3-dev\
    libedit-dev\
    libjack-dev\
    jack-keyboard\
    patchage\
    libgles2-mesa-dev -y

# Install faust
RUN git clone https://github.com/grame-cncm/faust.git /tmp/faust
WORKDIR /tmp/faust
RUN git checkout 24db8d98e63aa8a119ffc601bf6aeec3e33e7a86 #Important, has to be this version
RUN make && make install

# Jack settings
RUN echo '/usr/bin/jackd -r -dalsa -r44100 -p128 -n4' >> /root/.jackdrc

# Run the TOP-1!
WORKDIR /top-1
CMD sh install.sh
