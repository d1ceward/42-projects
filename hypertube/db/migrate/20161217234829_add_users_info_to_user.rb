class AddUsersInfoToUser < ActiveRecord::Migration[5.0]
  def change
      add_column    :users, :username,      :string
      add_column    :users, :first_name,    :string
      add_column    :users, :last_name,     :string
      add_column    :users, :language,      :string
      add_column    :users, :viewed,        :text
  end
end
