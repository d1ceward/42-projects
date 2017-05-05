class Users::RegistrationsController < Devise::RegistrationsController
# before_action :configure_sign_up_params, only: [:create]
# before_action :configure_account_update_params, only: [:update]

  # GET /resource/sign_up
  # def new
  #   super
  # end

  # POST /resource
  # def create
  #   super
  # end

  # GET /resource/edit
  # def edit
  #   super
  # end

  # PUT /resource
  def update
    @user = User.find(current_user.id)
    successfully_updated = if @user.persisted? and @user.provider.nil?
      unless @user.valid_password? params[:user][:current_password]
        @user.errors.add(:current_password, :incorrect)
        false
      else
        @user.update_with_password(account_update_params)
      end
    else
      @user.update_without_password(account_update_params)
    end

    if successfully_updated
      set_flash_message :notice, :updated
      sign_in @user, :bypass => true
      return redirect_to after_update_path_for(@user)
    else
      return render "edit"
    end
  end

  # DELETE /resource
  # def destroy
  #   super
  # end

  # GET /resource/cancel
  # Forces the session data which is usually expired after sign
  # in to be expired now. This is useful if the user wants to
  # cancel oauth signing in/up in the middle of the process,
  # removing all OAuth session data.
  # def cancel
  #   super
  # end

  private
  # If you have extra params to permit, append them to the sanitizer.
    def sign_up_params
      params.require(:user).permit(:email, :password, :password_confirmation, :first_name, :last_name, :custom_cover, :custom_cover_cache)
    end

    def account_update_params
      params.require(:user).permit(:email, :password, :password_confirmation, :current_password, :first_name, :last_name, :custom_cover, :custom_cover_cache, :language)
    end

    def after_update_path_for user
      root_path(locale: user.language.to_sym)
    end

  # If you have extra params to permit, append them to the sanitizer.
  # def configure_account_update_params
  #   devise_parameter_sanitizer.permit(:account_update, keys: [:attribute])
  # end

  # The path used after sign up.
  # def after_sign_up_path_for(resource)
  #   super(resource)
  # end

  # The path used after sign up for inactive accounts.
  # def after_inactive_sign_up_path_for(resource)
  #   super(resource)
  # end
end
