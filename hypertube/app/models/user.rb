class User < ApplicationRecord
    mount_uploader :custom_cover, AvatarUploader
    devise      :database_authenticatable, :registerable, :omniauthable,
                :recoverable, :rememberable, :trackable, :validatable,
                :omniauth_providers => [:facebook, :marvin]

    has_one     :provider, class_name: UserProvider,  dependent: :destroy
    has_many    :user_movies, dependent: :destroy
    has_many    :movies, :through => :user_movies
    has_many    :comments, dependent: :destroy
    has_many    :movie_views, dependent: :destroy
    has_many    :user_friends
    has_many    :friends, -> { where.not(request_accepted_at: nil) }, class_name: UserFriend, dependent: :destroy
    has_many    :send_requests, -> { where(request_accepted_at: nil) }, class_name: UserFriend
    has_many    :received_requests, -> { where(request_accepted_at: nil) }, class_name: UserFriend, foreign_key: :friend_user_id

    validates_presence_of :first_name, with: /^[a-zA-Z0-9_\.]*$/, :multiline => true, presence: true
    validates_presence_of :last_name, with: /^[a-zA-Z0-9_\.]*$/, :multiline => true, presence: true

    before_validation :set_language, :set_username, on: :create

    def set_language
        self.language = 'en'
    end

    def full_name
      self.first_name + ' ' + self.last_name
    end

    def find_username suffix = ""
        return unless (self.first_name and self.last_name)
        (1..8).map do |i|
            base = "#{I18n.transliterate(self.first_name)[0,i]}#{I18n.transliterate(self.last_name)}"
            base.gsub(' ', '-').gsub(/[^a-z_-]/i, '')[0,(8-suffix.length)].downcase + suffix
        end.uniq.detect {|username| User.where(username: username).count == 0}
    end

    def  set_username
        return unless self.username.blank?
        self.username = (self.find_username || (2..Float::INFINITY).each do |suffix|
            username = self.find_username(suffix.to_s)
            break username if username
        end)
    end

    class << self
        def current_user=(user)
            Thread.current[:current_user] = user
        end

        def current_user
            Thread.current[:current_user]
        end
    end
end
