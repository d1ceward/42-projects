json.extract! movie_view, :id, :movie, :user, :created_at, :updated_at
json.url movie_view_url(movie_view, format: :json)
