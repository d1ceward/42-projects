class HomeController < ApplicationController
  before_action :collection_user

  def index
    begin
      s_by = ['year', 'length', 'id', 'votes']
      s_type = ['ASC', 'DESC']
      order_by = 'id'
      order_type = 'DESC'
      if s_by.include?(params[:sort_by])
        order_by = params[:sort_by]
      end
      if s_type.include?(params[:sort_type])
        order_type = params[:sort_type]
      end
      @movies = Movie.all.order(order_by + ' ' + order_type).page params[:page]
      if request.xhr?
        respond_to do |format|
          format.js { return render('movies/index.js') }
        end
      else
        @tredings = Rails.cache.fetch("top12", :expires_in => 1.days) do
          Movie.top(12)
        end
      end
    rescue
     render 'movies/unavailable'
    end
  end

  def unavailable
  end
end
