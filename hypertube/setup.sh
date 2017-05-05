export DISABLE_DATABASE_ENVIRONMENT_CHECK=1
export RAILS_ENV=production
export SECRET_KEY_BASE=6f02cb3ecaa1e44d54c573708caf6c30b42536c96bdd62a930fcfdf000f5230335670c352900db9984335c7f6216ec554eef0c3ecb4f93f1fd9400160f412bc4

# CLEAN OLD CACHE
redis-cli flushall
rm -rf ./tmp/cache

# CREATE NEW ENV
mkdir /tmp/graissehubaul
ln -s /tmp/graissehubaul stream_api/public
bash -c "cd ./stream_api/ && npm install && cd -"
bundle install
bundle update
psql -c "CREATE USER gaflix WITH SUPERUSER CREATEROLE CREATEDB REPLICATION BYPASSRLS;"
rails db:drop
rails db:setup
rails assets:precompile

# Lancer redis-server et postgres (side service)
