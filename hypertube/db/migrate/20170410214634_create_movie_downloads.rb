class CreateMovieDownloads < ActiveRecord::Migration[5.0]
  def change
    create_table :movie_downloads do |t|
      t.references :movie, foreign_key: true
      t.datetime :downloaded_at
      t.boolean :downloading

      t.timestamps
    end
  end
end
