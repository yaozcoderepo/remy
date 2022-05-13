FROM salttest/ubuntu-13.04

WORKDIR /app

COPY remy-reproduce-1.0 ./remy-reproduce-1.0

RUN apt-get update && \
    apt-get install -y git && \
    apt-get install -y wget && \
    apt-get install -y build-essential && \
    apt-get install -y libprotobuf-dev && \
    apt-get install -y libx11-dev && \
    apt-get install -y xorg-dev && \
    apt-get install -y protobuf-compiler && \
    apt-get install -y python-matplotlib && \
    apt-get install -y gnuplot && \
    apt-get install -y inkscape

CMD bash
