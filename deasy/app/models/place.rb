class Place < ApplicationRecord
    paginates_per 6
    def self.searchByRating(client,params)
        Rails.cache.fetch(params.to_enum.to_h,
         expires_in: 12.hours) do
            client.spots_by_query( params[:search] +" near "+ params[:city]).sort_by {|m| -m.rating}
            end
    end
    
    def self.searchByName(client,params)
        Rails.cache.fetch(params.to_enum.to_h,
         expires_in: 12.hours) do
            client.spots_by_query( params[:search] +" near "+ params[:city]).sort_by {|m| -m.name}
            end
    end

    def self.searchByDistance(client,params,cityCoordinates)
        Rails.cache.fetch(params.to_enum.to_h,
         expires_in: 12.hours) do
            client.spots_by_query( params[:search] +" near "+ params[:city])
            .sort_by {|m| -Geocoder::Calculations.distance_between(cityCoordinates.first.coordinates, [m.lng,m.lat])}
            end
    end
end
