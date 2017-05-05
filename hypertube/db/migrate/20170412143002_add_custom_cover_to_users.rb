class AddCustomCoverToUsers < ActiveRecord::Migration[5.0]
  def change
    add_column :users, :custom_cover, :string
  end
end
