# Utilisez une image existante comme base
FROM ubuntu:latest

ENV RTYPE_SERVER_IP=0.0.0.0

# Installez les dépendances nécessaires pour votre projet
RUN apt-get update && \
    apt-get install -y build-essential && \
    apt-get install -y libboost-all-dev && \
    apt-get install -y git && \
    apt-get install -y cmake && \
    apt-get install -y wget && \
    apt-get install -y dos2unix && \
    apt-get install -y libssl-dev

RUN wget -qO /usr/local/bin/ninja.gz https://github.com/ninja-build/ninja/releases/latest/download/ninja-linux.zip
RUN gunzip /usr/local/bin/ninja.gz
RUN chmod a+x /usr/local/bin/ninja

# Installez les dépendances de la lib
RUN apt install -y libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev


# Copiez les fichiers de votre projet dans le conteneur Docker
COPY . /app

# Exécutez le script de compilation dans le conteneur Docker
WORKDIR /app

RUN dos2unix ./build.sh

RUN ./build.sh

# Exposez le port que votre serveur utilise
EXPOSE 4242/udp

# Lancez l'exécutable du serveur dans le conteneur Docker

CMD "/app/build/Server/r-type-server"