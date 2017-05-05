class ChangeMovieTable < ActiveRecord::Migration[5.0]
  def change
      drop_table :movies

      create_table :movies do |t|
          t.integer       :uid_imdb
          t.text          :title
          t.text          :also_known_as
          t.text          :url
          t.text          :cast_characters
          t.text          :cast_member_ids
          t.text          :cast_members
          t.text          :cast_members_characters
          t.text          :company
          t.text          :countries
          t.text          :director
          t.text          :filming_locations
          t.text          :genres
          t.text          :languages
          t.integer       :length
          t.integer       :mpaa_rating
          t.text          :plot
          t.text          :plot_summary
          t.text          :plot_synopsis
          t.text          :poster
          t.float         :rating
          t.text          :release_date
          t.text          :tagline
          t.text          :trailer_url
          t.integer       :votes
          t.text          :writers
          t.text          :year
          t.timestamps
      end
  end
end
