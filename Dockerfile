FROM ubuntu:latest
RUN apt-get update
RUN apt-get -y install cmake build-essential
COPY . /usr/src
WORKDIR /usr/src
RUN cmake .
RUN make

ENTRYPOINT bin/tests
