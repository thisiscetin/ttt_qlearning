#/bin/bash

docker build -t tests . && docker run -it tests
