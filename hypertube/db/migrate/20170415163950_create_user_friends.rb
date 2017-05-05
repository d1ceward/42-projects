class CreateUserFriends < ActiveRecord::Migration[5.0]
  def change
    create_table :user_friends do |t|
      t.references :user, foreign_key: true
      t.integer :friend_user_id, foreign_key: true
      t.datetime :request_send_at
      t.datetime :request_accepted_at

      t.timestamps
    end
  end
end
