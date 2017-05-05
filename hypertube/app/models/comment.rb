class Comment < ApplicationRecord
    belongs_to :user
    belongs_to :movie

    validates_presence_of :content
    validates_presence_of :user
    validates_presence_of :movie

end
