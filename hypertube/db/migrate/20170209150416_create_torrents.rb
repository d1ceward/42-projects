class CreateTorrents < ActiveRecord::Migration[5.0]
  def change
    create_table :torrents do |t|
      t.integer :uid_imdb
      t.text :name
      t.text :magnet_link

      t.timestamps
    end
  end
end
