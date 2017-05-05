class MovieView < ApplicationRecord
  belongs_to :movie
  belongs_to :user

  validates_presence_of :movie
  validates_presence_of :user

  def viewed_at
    self.created_at
  end
end
