class Api::V1::MoviesSerializer < ActiveModel::Serializer
  attributes(*Movie.attribute_names.map(&:to_sym), :downloaded?, :views_count)

  def downloaded?
    object.downloaded?
  end

  def views_count
    object.movie_views.count
  end
end
