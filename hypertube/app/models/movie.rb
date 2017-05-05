class Movie < ApplicationRecord
  has_many        :comments, :dependent => :destroy
  has_many        :subtiltes, :dependent => :destroy
  has_many        :movie_views, :dependent => :destroy
  has_one         :movie_download, dependent: :destroy
  has_one         :torrent, foreign_key: :uid_imdb, primary_key: :uid_imdb

  validates_presence_of :title
  validates_presence_of :uid_imdb
  validates_uniqueness_of :uid_imdb

  paginates_per 8

  def viewed? user
    self.movie_views.where(user: user).present?
  end

  def downloaded?
    self.movie_download.present? and !self.movie_download.downloading?
  end

  def self.top count = 50
    torrents = HyperTorrent.new(nil, count).results
    uids_imdb = Array.new
    torrents.each do |t|
      ImportImdbInfoJob.perform_later t.uid_imdb
      uids_imdb.push t.uid_imdb
      next if Torrent.exists?(uid_imdb: t.uid_imdb)
      Torrent.create Torrent.generate_torrent_infos(t)
    end
    return Movie.where(uid_imdb: uids_imdb)
  end

  def self.torrent_search term
    torrents = HyperTorrent.new(term).results
    uids_imdb = Array.new
    torrents.each do |t|
      ImportImdbInfoJob.perform_now t.uid_imdb
      uids_imdb.push t.uid_imdb
      next if Torrent.exists?(uid_imdb: t.uid_imdb)
      Torrent.create Torrent.generate_torrent_infos(t)
    end
    return Movie.where(uid_imdb: uids_imdb)
  end

  def self.generate_imdb_infos imdb
      {uid_imdb: imdb.id.to_i, title: imdb.title, url: imdb.url, length: imdb.length,
          trailer_url: imdb.trailer_url, votes: imdb.rating, year: imdb.year, poster: imdb.poster}
  end
end
