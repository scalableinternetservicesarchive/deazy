class PlacesController < ApplicationController
  def index
    if params[:search]
        @client = GooglePlaces::Client.new(AIzaSyDheNaQURdWzU1BSC7nVnKnKr9VO2AH5T0)
        @places = @client.spots_by_query(params[:search])
    end
  end
end

placesController = PlacesController.new
puts placesController.index