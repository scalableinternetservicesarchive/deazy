class SavedPlacesController < ApplicationController
  def home
    if !current_user.saved_places.empty?
      @places_id = YAML.load(current_user.saved_places)
    else 
      @places = nil
    end
    
  end
end
