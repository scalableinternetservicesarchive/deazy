class HomePageController < ApplicationController
  def home
  end
  def search
    @client = GooglePlaces::Client.new()
    @places = @client.spots_by_query(params[:places_option])
  end
  def save
    @place = params[:place_id]
    @saved_places = YAML.load(current_user.saved_places)
    @saved_places.push(@place)
    current_user.saved_places = @saved_places.to_yaml
    current_user.save
  end
end
