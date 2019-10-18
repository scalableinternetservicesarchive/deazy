class HomePageController < ApplicationController
    def home
    end
    def search
      @event = params[:places_option]
    end
  end