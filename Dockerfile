# Dockerfile test-suite + install - build file

FROM ubuntu
MAINTAINER Juma Ian <wjuma@students.usiu.ac.ke>
CMD echo "Simple test + build file"


RUN apt-get update
RUN apt-get -y install build-essential make gcc g++ automake


# add src files
ADD Makefile /home
ADD src /home
ADD bin /home
# -ADD bin CMD `pwd`
# -ADD Makefile CMD `pwd`


# install deps + project from github
RUN make


# -CMD echo "Done"
