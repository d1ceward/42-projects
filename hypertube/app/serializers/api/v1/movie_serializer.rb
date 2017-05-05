class Api::V1::MovieSerializer < ActiveModel::Serializer
  attributes(*Movie.attribute_names.map(&:to_sym), :downloaded?, :downloaded_at, :views_count)
  has_many :comments
  has_many :movie_views

  def downloaded?
    object.downloaded?
  end

  def downloaded_at
    object.movie_download.try(:downloaded_at)
  end

  def views_count
    object.movie_views.count
  end
end
