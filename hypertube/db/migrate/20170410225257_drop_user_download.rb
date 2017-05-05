class DropUserDownload < ActiveRecord::Migration[5.0]
  def change
    drop_table :user_downloads
  end
end
