class Api::V1::MovieViewSerializer < ActiveModel::Serializer
  attributes :id, :user_id, :viewed_at

  def viewed_at
    object.created_at
  end
end
