#!/bin/bash
#
# Dockerfile
# 
# Purpose: Deploy of vfsa package.
# 
# Site: https://dirack.github.io
# 
# Version 1.1.0
# 
# Programer: Rodolfo A C Neves (Dirack) 08/04/2020
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

# Docker image with Madagascar package version 3.0
FROM dirack/ambientemadagascar:1.0

# Madagascar environment variables
ENV RSFSRC="/root/madagascar-3.0"
ENV RSFROOT="/root/madagascar"
ENV VFSAROOT="/root/madagascar-3.0/user/vfsa"

# Maintainer information
LABEL maintainer="Rodolfo Dirack"
LABEL email="rodolfo_profissional@hotmail.com"
LABEL site="https://dirack.github.io"

# Install vfsa package in Madagascar
RUN git clone -b v1.1.1 --depth 1 https://github.com/Dirack/vfsa.git "$VFSAROOT"
RUN cd "$VFSAROOT" && scons && cd "$RSFSRC" && scons install

# Go to usage examples directory
WORKDIR "$VFSAROOT/usage_examples"
