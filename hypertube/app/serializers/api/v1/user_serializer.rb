class Api::V1::UserSerializer < ActiveModel::Serializer
  attributes(:id, :username, :first_name, :last_name, :full_name, :language, :cover, :friends_ids)

  def cover
    if object.custom_cover.url.present?
      object.custom_cover.url
    else
      object.cover
    end
  end

  def friends_ids
    object.friends.pluck(:friend_user_id)
  end
end
