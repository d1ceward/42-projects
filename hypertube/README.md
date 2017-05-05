# README

Mise en prod sans docker:

`sh setup.sh && foreman start`

Mise en prod via docker:

```
docker-compose build
docker-compose up db
docker-compose exec db psql -U postgres -c "CREATE USER gaflix WITH SUPERUSER;"
docker-compose exec db psql -U postgres -c "CREATE DATABASE gaflix;"
docker-compose up
docker-compose exec app rails db:setup
docker-compose exec app rails assets:precompile
docker-compose up

sudo echo '192.168.99.100 docker.local' >> /etc/hosts
```

Pour créer le user gaflix: `psql -c "CREATE USER gaflix WITH SUPERUSER CREATEROLE CREATEDB REPLICATION BYPASSRLS;"`
