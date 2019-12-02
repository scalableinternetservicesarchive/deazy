class Review < ApplicationRecord
    # belongs_to :book
    # belongs_to :usr 
    # ratyrate_rateable "rating"
    validates_numericality_of :rating, greater_than_or_equal_to: 0, less_than_or_equal_to: 5, message: 'must be between 0 & 5'

    def self.cached_by_place_id(params,placeId)
        Rails.cache.fetch(params.to_enum.to_h) do
            puts "Cached"
            where(place_id: placeId) 
        end
    end
end
