class MovieViewsController < ApplicationController
  inherit_resources
  load_and_authorize_resource

  def create
    last_view = current_user.movie_views.where(movie_id: params[:movie_view][:movie_id]).last.try(:viewed_at)
    if (last_view.nil? or (last_view.present? and last_view > (Time.now.utc - 5.minutes))) and Movie.where(id: params[:movie_view][:movie_id]).first.try(:downloaded?)
      resource = MovieView.create movie_view_params.merge({ user_id: current_user.id })
    else
      resource = current_user.movie_views.last
    end
    respond_to do |format|
      format.html { return redirect_to movie_view_path(resource) }
      format.json { return render json: resource }
    end
  end

  private
    def movie_view_params
      params.require(:movie_view).permit(:movie_id, :user_id)
    end
end
