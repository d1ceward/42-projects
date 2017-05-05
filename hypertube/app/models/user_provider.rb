class UserProvider < ActiveRecord::Base
    belongs_to :user

    def self.find_for_facebook_oauth(auth)

        user = UserProvider.where(:provider => auth.provider, :uid => auth.uid).first
        unless user.nil?
            user.user
        else
            registered_user = User.where(:email => auth.info.email).first
            unless registered_user.nil?
                UserProvider.create!(provider: auth.provider, uid: auth.uid, user_id: registered_user.id)
                registered_user
            else
                user = User.create!(email: auth.info.email, first_name: auth.info.first_name, last_name: auth.info.last_name, username: auth.info.nickname, password: Devise.friendly_token[0,20], cover: auth.info.image)
                user_provider = UserProvider.create!(provider: auth.provider, uid: auth.uid, user_id: user.id)
                user
            end
        end
    end

    def self.find_from_marvin_oauth(auth)
        user = UserProvider.where(:provider => auth.provider, :uid => auth.uid).first
        unless user.nil?
            user.user
        else
            registered_user = User.where(:email => auth.info.email).first
            unless registered_user.nil?
                UserProvider.create!(provider: auth.provider, uid: auth.uid, user_id: registered_user.id)
                registered_user
            else
                user = User.create!(email: auth.info.email, first_name: auth.extra.raw_info.first_name, last_name: auth.extra.raw_info.last_name, username: auth.info.nickname, password: Devise.friendly_token[0,20], cover: auth.info.image)
                user_provider = UserProvider.create!(provider: auth.provider, uid: auth.uid, user_id: user.id)
                user
            end
        end
    end
end
