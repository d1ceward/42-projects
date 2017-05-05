class AddImdbInfosToMovie < ActiveRecord::Migration[5.0]
  def change
      add_column :movies, :imdb_infos, :text
  end
end
