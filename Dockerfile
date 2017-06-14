FROM debian:9

ENV DISPLAY :0

RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
RUN apt update &&\
    apt install jackd\
    cmake\
    gcc\
    g++\
    git\
    pkg-config\
    libglfw3-dev\
    libedit-dev\
    libjack-jackd2-dev\
    libgles2-mesa-dev -y

RUN git clone https://github.com/grame-cncm/faust.git /tmp/faust
WORKDIR /tmp/faust
RUN make && make install

ADD install.sh /root/install.sh
CMD sh /root/install.sh
ENTRYPOINT /top-1/bin/tapedeck
