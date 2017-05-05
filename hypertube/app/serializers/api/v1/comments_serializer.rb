class Api::V1::CommentsSerializer < ActiveModel::Serializer
  attributes(:id, :user_id, :content)
end
