FROM ghcr.io/dirack/madagascarenvironment-3.0:1.0.1
COPY . /home/tryitondocker/madagascar-3.0/user/vfsa
RUN echo "Installing VFSA..." && cd /home/tryitondocker/madagascar-3.0/user/vfsa && scons && cd /home/tryitondocker/madagascar-3.0 && scons install && echo "...done"
