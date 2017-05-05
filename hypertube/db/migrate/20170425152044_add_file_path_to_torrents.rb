class AddFilePathToTorrents < ActiveRecord::Migration[5.0]
  def change
    add_column :torrents, :file_path, :string
  end
end