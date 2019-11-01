class HomePageController < ApplicationController
  def home
  end
  def search
    @client = GooglePlaces::Client.new(my_api_key)
    if params[:search]
      @places = @client.spots_by_query(params[:search])
    end
  end
  def save
    @place = params[:place_id]
    @saved_places = YAML.load(current_user.saved_places)
    @saved_places.push(@place)
    current_user.saved_places = @saved_places.to_yaml
    current_user.save
  end
end
