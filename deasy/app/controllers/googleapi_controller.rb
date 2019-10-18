class GoogleapiController < ApplicationController
  def index
    if params[:search]
        @client = GooglePlaces::Client.new(my_api_key)
        @places = @client.spots_by_query(params[:search])
    end
  end
end