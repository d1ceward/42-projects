class UserFriend < ApplicationRecord
  belongs_to :user
  belongs_to :friend_user, class_name: User

  validates_presence_of :user_id
  validates_presence_of :friend_user_id
  validates_presence_of :request_send_at
  validates_uniqueness_of :user_id, scope: [:friend_user_id]

  before_validation :set_send_at
  after_commit :send_request, on: :create, if: -> { request_accepted_at.nil? }
  before_destroy :remove_friendship

  def accept_request
    self.update(request_accepted_at: Time.now.utc)
    UserFriend.create(user_id: self.friend_user_id, friend_user_id: self.user_id, request_send_at: Time.now.utc, request_accepted_at: Time.now.utc)
  end

  def send_request
    FriendRequestMailer.send_mail(self.user, self.friend_user).deliver_later
  end

  def remove_friendship
    UserFriend.delete(UserFriend.where(user_id: self.friend_user_id, friend_user_id: self.user_id).pluck(:id))
  end

  private
  def set_send_at
    self.request_send_at = Time.now.utc
  end
end
