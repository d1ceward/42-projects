class RemoveUselessColumnOfMovie < ActiveRecord::Migration[5.0]
  def change
    remove_column :movies, :also_known_as
    remove_column :movies, :cast_characters
    remove_column :movies, :cast_member_ids
    remove_column :movies, :cast_members
    remove_column :movies, :cast_members_characters
    remove_column :movies, :company
    remove_column :movies, :countries
    remove_column :movies, :director
    remove_column :movies, :filming_locations
    remove_column :movies, :genres
    remove_column :movies, :languages
    remove_column :movies, :mpaa_rating
    remove_column :movies, :plot
    remove_column :movies, :plot_summary
    remove_column :movies, :plot_synopsis
    remove_column :movies, :poster
    remove_column :movies, :rating
    remove_column :movies, :release_date
    remove_column :movies, :tagline
    remove_column :movies, :writers
  end
end
