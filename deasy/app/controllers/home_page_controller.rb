class HomePageController < ApplicationController
  def home
  end
  def search
    @client = GooglePlaces::Client.new(ENV["PLACES_API_KEY"])
    if params[:search] 
      if params[:sortCat] == "Rating"
      @places = Place.searchByRating(@client,params).page params[:page]
      end
      if params[:sortCat] == "Name"
        @places = Place.searchByName(@client,params)
      end
      if params[:sortCat] == "Distance"
        cityCoordinates = Geocoder.search("172.56.21.89")
        @places = Place.searchByDistance(@client,params,cityCoordinates)
      end
    end
  end
  def save
    @place = params[:place_id]
    if !current_user.saved_places.empty?
      @saved_places = YAML.load(current_user.saved_places)
      @saved_places.push(@place)
    else 
      @saved_places = [@place]
    end
    current_user.saved_places = @saved_places.to_yaml
    current_user.save
  end
  def details
    @place = params
  end
end
