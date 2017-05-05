FROM ruby:2.3.3
LABEL maintener "atom <atom@42.fr>"

RUN apt-get update -qq && apt-get install -y build-essential libpq-dev nodejs imagemagick libmagickwand-dev pkg-config

RUN mkdir /hypertube
WORKDIR /hypertube
ADD Gemfile /hypertube/Gemfile
ADD Gemfile.lock /hypertube/Gemfile.lock
RUN bundle install
ADD . /hypertube
