class AddUidImdbToMovie < ActiveRecord::Migration[5.0]
  def change
    add_column :movies, :uid_imdb, :integer
  end
  # add_index :movies, :uid_imdb, unique: true
end
