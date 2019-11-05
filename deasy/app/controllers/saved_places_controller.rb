class SavedPlacesController < ApplicationController
  def home
    @client = GooglePlaces::Client.new(ENV["PLACES_API_KEY"])
    @places_id = []
    if !current_user.saved_places.empty?
      @places_id = YAML.load(current_user.saved_places)
    end

    @places = []
    @places_id.each { |id| 
      spot = @client.spot(id)
      @places.push(spot)
    }

  end
end
