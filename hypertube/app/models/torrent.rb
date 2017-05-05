class Torrent < ApplicationRecord
  belongs_to :movie, foreign_key: :uid_imdb, primary_key: :uid_imdb


  def self.generate_torrent_infos torrent
    info = {uid_imdb: torrent.uid_imdb, name: torrent.name, magnet_link: torrent.magnet_link}
  end
end
