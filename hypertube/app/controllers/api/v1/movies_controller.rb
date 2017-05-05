class Api::V1::MoviesController < Api::ApiController

  private def movies_params
    params.require(:movies).permit(:uid_imdb, :title, :url, :length, :trailer_url, :votes, :year)
  end
end
