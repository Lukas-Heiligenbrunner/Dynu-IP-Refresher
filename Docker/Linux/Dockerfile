FROM gcc:latest
MAINTAINER luki42

RUN \
    \
    # Install texlive
    echo "instaling cmake" && \
    apt-get update && \
    apt-get install -y --no-install-recommends cmake libgtest-dev && \
    echo "installing build dependencies" && \
    apt-get install -y --no-install-recommends libcurl4-openssl-dev libconfig++-dev && \
    echo "installing packaging tools" && \
    apt-get install -y --no-install-recommends dpkg rpm && \
    # clean up
    apt-get clean

# Expose /home as workin dir
WORKDIR /home
VOLUME ["/home"]