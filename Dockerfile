# Dockerfile test-suite + install - build file

FROM ubuntu
MAINTAINER Juma Ian <wjuma@students.usiu.ac.ke>
CMD echo "Simple test + build file"

RUN apt-get update
RUN apt-get install build-essential make gcc g++ automake

# install deps + project from github
RUN make
