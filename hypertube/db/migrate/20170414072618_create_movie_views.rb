class CreateMovieViews < ActiveRecord::Migration[5.0]
  def change
    create_table :movie_views do |t|
      t.references :movie
      t.references :user

      t.timestamps
    end
  end
end
