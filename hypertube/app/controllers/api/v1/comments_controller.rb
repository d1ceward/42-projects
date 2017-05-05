class Api::V1::CommentsController < Api::ApiController

  private def comments_params
    params.require(:comments).permit(:content, :movie_id, :user_id)
  end
end
