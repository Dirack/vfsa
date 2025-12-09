FROM ghcr.io/dirack/madagascarenvironment-4.2:1.2.0
COPY . /home/madagascar-4.2/user/vfsa
RUN echo "Installing VFSA..." && cd /home/madagascar-4.2/user/vfsa && scons && cd /home/madagascar-4.2 && scons install && echo "...done"
