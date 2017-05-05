class Api::V1::CommentSerializer < ActiveModel::Serializer
  attributes(:id, :content)
  belongs_to :user
end
