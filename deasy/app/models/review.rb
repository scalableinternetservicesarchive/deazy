class Review < ApplicationRecord
    # belongs_to :book
    # belongs_to :usr 
    # ratyrate_rateable "rating"
    validates_numericality_of :rating, greater_than_or_equal_to: 0, less_than_or_equal_to: 5, message: 'must be between 0 & 5'
end
