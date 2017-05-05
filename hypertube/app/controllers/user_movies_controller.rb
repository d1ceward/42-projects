class UserMoviesController < ApplicationController
  inherit_resources
  load_and_authorize_resource
  before_action :collection_user

  def create
    create! { return redirect_back(fallback_location: root_path, notice: t('online.user_movie.add')) }
  end

  def destroy
    destroy! { return redirect_back(fallback_location: root_path, notice: t('online.user_movie.remove')) }
  end

  private
    def user_movie_params
      params.require(:user_movie).permit(:user_id, :movie_id)
    end
end
