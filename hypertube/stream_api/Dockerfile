FROM debian:jessie

LABEL maintener "atom <atom@42.fr>"

RUN apt-get update -qq && apt-get install -y build-essential libpq-dev nodejs imagemagick libmagickwand-dev pkg-config
RUN apt-get -qqy install --no-install-recommends autoconf automake ca-certificates git mercurial cmake libass-dev libgpac-dev libtheora-dev libtool libvdpau-dev libvorbis-dev pkg-config texi2html zlib1g-dev libmp3lame-dev wget yasm && apt-get -qqy clean && rm -rf /var/lib/apt/lists/*

ADD setup.sh /setup.sh
RUN ["/bin/bash", "/setup.sh"]

# Create app directory
RUN mkdir -p /app
WORKDIR /app

# Install app dependencies
RUN apt-get update && apt-get install -y build-essential curl
RUN curl -sL https://deb.nodesource.com/setup_7.x | bash -
RUN apt-get install -y nodejs
COPY package.json /app/

RUN bash -c 'npm install'

# Bundle app source
COPY . /app
RUN mkdir /app/stream_api/
RUN mkdir /app/stream_api/public/

EXPOSE 3001

CMD ["/usr/bin/nodejs", "/app/bin/www"]
