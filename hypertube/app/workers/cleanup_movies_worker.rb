class CleanupMoviesWorker < ApplicationJob
  queue_as :default

  def perform(*args)
    movies = Movie.joins(:movie_views).where('movie_views.created_at > ?', Time.now.utc - 30.days)
    if movies.any?
      movies.destroy_all
    end
  end
end
