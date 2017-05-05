class MoviesController < ApplicationController
    inherit_resources
    load_and_authorize_resource
    before_action :collection_user
    before_filter :authenticate_user!

    def index
      begin
        Movie.torrent_search(params[:search])
      rescue
        render 'movies/unavailable'
      end
      sql = String.new
      params[:search].split(' ').each_with_index do |s, i|
        sql += ' AND ' unless i == 0
        sql += "title ILIKE '%" + s + "%'"
      end
      if sql.present?
        @movies = Movie.where(sql).order('title ASC')
      else
        return redirect_to root_path
      end
    end

    def show
      show! do
        @movie = Movie.find(params[:id])
        @imdbinfo = Rails.cache.fetch("movie_imdb_info_#{@movie.uid_imdb}", :expires_in => 1.days) do
          Imdb::Movie.new(@movie.uid_imdb)
        end
        torrent = @movie.torrent
        if torrent.file_path
          file = Subdb::Video.new("stream_api/public/#{torrent.uid_imdb.to_s}/" + torrent.file_path)
          trans = file.search
          if trans
            trans = trans.split(',')
            trans.each do |language|
              next if Subtilte.exists?(label: language, movie: @movie)
              data = file.download([language])
              File.open(File.join("stream_api/public/#{torrent.uid_imdb.to_s}/" + language + '.srt'), 'w+') do |f|
                f.write(data.force_encoding("UTF-8"))
                Subtilte.create(path: "#{torrent.uid_imdb.to_s}/#{language}.srt", label: language, movie: @movie)
              end
            end
          end
        end
      end
    end

    def my_list
      @movies = @user.movies
    end

    private def movie_params
        params.require(:movie).permit(:name, :description, :duration, :note,
            :cover, :producer, :produced_at, :director, :primary_actors)
    end
end
