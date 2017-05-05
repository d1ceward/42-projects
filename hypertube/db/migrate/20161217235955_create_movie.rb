class CreateMovie < ActiveRecord::Migration[5.0]
  def change
    create_table :movies do |t|
        t.text          :name
        t.text          :description
        t.integer       :duration
        t.integer       :note
        t.text          :cover
        t.text          :producer
        t.text          :director
        t.datetime      :produced_at
        t.text          :primary_actors
        t.timestamps
    end
  end
end
