class Users::SessionsController < Devise::SessionsController
# before_action :configure_sign_in_params, only: [:create]
  before_filter :authenticate_user!

  def show
    @user = User.find_by_username params[:username]
    redirect_to(root_url) unless @user
    # raise ActionController::RoutingError.new('Not Found') unless @user
  end
  # GET /resource/sign_in
  # def new
  #   super
  # end

  # POST /resource/sign_in
  # def create
  #   super
  # end

  # DELETE /resource/sign_out
  # def destroy
  #   super
  # end

  # protected

  # If you have extra params to permit, append them to the sanitizer.
  # def configure_sign_in_params
  #   devise_parameter_sanitizer.permit(:sign_in, keys: [:attribute])
  # end
end
