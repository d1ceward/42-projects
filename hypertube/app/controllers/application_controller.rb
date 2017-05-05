class ApplicationController < ActionController::Base
    protect_from_forgery with: :exception
    before_action :set_current_user, :set_locale

    def set_current_user
        User.current_user = current_user
    end

    def set_locale
      I18n.locale = params[:locale].try(:to_sym) || I18n.default_locale
    end

    def default_url_options opts={}
      { locale: I18n.locale }.merge(opts)
    end

    def collection_user
      @user = User.params[:user_id] rescue current_user
    end

    def after_sign_in_path_for user
      root_path(locale: user.language.to_sym)
    end

    protected

    def authenticate_user! (options={})
      if user_signed_in?
        super(options)
      else
        redirect_to new_user_session_path
      end
    end

end
