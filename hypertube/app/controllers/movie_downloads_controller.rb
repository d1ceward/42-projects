class MovieDownloadsController < ApplicationController
  inherit_resources
  load_and_authorize_resource

  def create
    create! do
      if request.xhr?
        begin
          movie = Movie.where(id: params[:movie_download][:movie_id]).first
          DownloadMovieJob.perform_now movie.uid_imdb
          respond_to do |format|
            format.js { return render('movie_downloads/create.js') }
          end
        rescue ActiveRecord::RecordNotFound
          redirect_to root_path
        end
      end
    end
  end

  private
    def movie_download_params
      params.require(:movie_download).permit(:movie_id, :downloaded_at, :downloading)
    end
end
