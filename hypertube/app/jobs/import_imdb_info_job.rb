class ImportImdbInfoJob < ApplicationJob
  queue_as :importer

  def perform uid
    return true if Movie.exists?(uid_imdb: uid)
    imdb_movie = Imdb::Movie.new(uid)

    Movie.create Movie.generate_imdb_infos(imdb_movie)
  end
end
