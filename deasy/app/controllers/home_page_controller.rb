class HomePageController < ApplicationController
  def home
  end
  def search
    @client = GooglePlaces::Client.new("KEY")
    if params[:search] 
      if params[:sortCat] == "Rating"
      @places = @client.spots_by_query( params[:search] +" near "+ params[:city]).sort_by {|m| -m.rating}
      end
      if params[:sortCat] == "Name"
        @places = @client.spots_by_query( params[:search] +" near "+ params[:city]).sort_by {|m| -m.name}
      end
      if params[:sortCat] == "Distance"
        cityCoordinates = Geocoder.search("172.56.21.89")
        @places = @client.spots_by_query( params[:search] +" near "+ params[:city]).sort_by {|m| 
        -Geocoder::Calculations.distance_between(cityCoordinates.first.coordinates, [m.lng,m.lat])
      }
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
