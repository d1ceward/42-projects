class AddUniqToUidImdbToMovie < ActiveRecord::Migration[5.0]
  def change
      add_index :movies, :uid_imdb, unique: true
  end
end
