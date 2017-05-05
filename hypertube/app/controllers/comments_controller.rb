class CommentsController < ApplicationController
    inherit_resources
    load_and_authorize_resource
    before_action :get_movie

    def index
      index! do
        return if @movie.nil?
        @comments = @movie.comments
      end
    end

    def create
      resource = Comment.create(comment_params.merge(movie: @movie, user: current_user))
      return redirect_to movie_path(@movie), notice: t('online.modal.success')
    end

    def update
        update! { return redirect_to @movie, notice: t('online.modal.edit') }
    end

    def destroy
        destroy! { return redirect_to @movie, notice: t('online.modal.remove') }
    end

    private def get_movie
        @movie = Movie.find(params[:movie_id])
    end

    private def comment_params
        params.require(:comment).permit(:content)
    end
end
