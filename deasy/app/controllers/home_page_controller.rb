class HomePageController < ApplicationController
  def home
  end
  def search
    @client = GooglePlaces::Client.new("AIzaSyDyvkPM-LAuAZ94T_hqcaWbof2bGNJyVQE")
    @places = @client.spots_by_query(params[:places_option])
  end
end
