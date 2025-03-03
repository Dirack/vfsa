FROM ghcr.io/dirack/madagascarenvironment-4.0:1.0.1
COPY . /home/madagascar-4.0/user/vfsa
RUN echo "Installing VFSA..." && cd /home/madagascar-4.0/user/vfsa && scons && cd /home/madagascar-4.0 && scons install && echo "...done"
