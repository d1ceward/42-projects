json.extract! user_friend, :id, :user_id, :friend_user_id, :request_send_at, :request_accepted_at, :created_at, :updated_at
json.url user_friend_url(user_friend, format: :json)
