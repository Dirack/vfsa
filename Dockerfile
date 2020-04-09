#!/bin/bash
#
# Dockerfile
# 
# Objetivo: Deploy da biblioteca vfsa.
# 
# Site: https://dirack.github.io
# 
# Versão 1.0
# 
# Programador: Rodolfo A C Neves (Dirack) 08/04/2020
# 
# Email: rodolfo_profissional@hotmail.com
# 
# Licença: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

# Pacote Madagascar versão 3.0 com dependências básicas configuradas
FROM dirack/ambientemadagascar:1.0

# Variáveis de ambiente do pacote Madagascar
ENV RSFSRC="/root/madagascar-3.0"
ENV RSFROOT="/root/madagascar"
ENV VFSAROOT="/root/madagascar-3.0/user/vfsa"

# define o mantenedor da imagem
LABEL maintainer="Rodolfo Dirack"
LABEL email="rodolfo_profissional@hotmail.com"
LABEL site="https://dirack.github.io"

# Instalação da vfsa no Madagascar
RUN git clone -b v1.0 --depth 1 https://github.com/Dirack/vfsa.git "$VFSAROOT"
RUN cd "$VFSAROOT" && scons && cd "$RSFSRC" && scons install

# Ir para o diretório de exemplos
WORKDIR "$VFSAROOT/usage_examples"
