json.extract! movie_download, :id, :movie_id, :downloaded_at, :downloading, :created_at, :updated_at
json.url movie_download_url(movie_download, format: :json)
