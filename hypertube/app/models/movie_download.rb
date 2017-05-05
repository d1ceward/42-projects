class MovieDownload < ApplicationRecord
  belongs_to :movie

  validates_presence_of :movie, on: :create
  validates_presence_of :downloaded_at, on: :create
  validates_presence_of :downloading
  validates_uniqueness_of :movie_id

  before_validation :set_download, if: -> { self.downloaded_at.nil? && self.downloading.nil? }
  before_destroy :delete_file

  def set_download
    self.downloaded_at = Time.now.utc
    self.downloading = true
  end

  def delete_file
    FileUtils.rm_rf Rails.root.join('public', 'uploads', self.movie.uid_imdb.to_s)
  end
end
