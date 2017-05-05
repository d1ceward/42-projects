class DownloadMovieJob < ApplicationJob
  queue_as :importer

  def perform uid_imdb
    movie = Movie.find_by_uid_imdb(uid_imdb)
    torrent = movie.torrent
    result = JSON.parse(open("http://localhost:3001/download?magnet=#{torrent.magnet_link}&uid_imdb=#{uid_imdb}").read)
    torrent.file_path = result['path']
    torrent.save
    movie.movie_download.update_attribute(:downloading, false)
  end
end
