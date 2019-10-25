class HomePageController < ApplicationController
  def home
  end
  def search
    @client = GooglePlaces::Client.new()
    @places = @client.spots_by_query(params[:places_option])
  end
end
