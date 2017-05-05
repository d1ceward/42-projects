class CreateSubtilte < ActiveRecord::Migration[5.0]
  def change
    create_table :subtiltes do |t|
      t.string :path
      t.string :label
      t.references :movie, foreign_key: true
    end
  end
end
