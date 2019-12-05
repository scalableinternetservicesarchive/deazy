class ReviewsController < ApplicationController

    #default args passed are controller and action
    #based off the action it looks for a matching method in the controller

    before_action :find_review, only: [:show, :edit, :update, :destroy]
    #Params are {"place_id"=>"9c5196802e47e15dba578913d834e212d2af0269", 
    #"controller"=>"reviews", "action"=>"new"}
    #Called when we click on new review
    def new 
        puts "Inside new reviews controller"
        puts "Params are #{params}"
        # puts "Params[:place_id] #{params[:place_id]}"
        # puts "Params[:user_id] #{current_user.id}"
        @review = Review.new
        @review.place_id = params[:place_id]
        @cached_reviews = Review.cached_by_place_id(params,params[:place_id])
        puts "start"
        puts @cached_reviews
        puts "end"
        #place id is 9c5196802e47e15dba578913d834e212d2af0269
        #Says place id is 9
        puts "Place id is #{@review.place_id}"
    end

    #Called when the submit button is pressed and current input 
    # would result in a new review
    #Params are {"authenticity_token"=>"hV+atXzkZ1AB6BCifW/UuZMLKl2+q82mj1Ka6f+2zLIgirci01Nd8GVx+L279LtntrwN64/JkdbQjK6QL7WBmg==", 
    #"review"=><ActionController::Parameters {"rating"=>"2", "comment"=>"this is new"} permitted: false>, 
    #"commit"=>"Create Review", "controller"=>"reviews", "action"=>"create"}

    def create
        puts "I'm in reviews create"
        @review = Review.new(review_params)
        @review.user_id = current_user.id
        puts "#{review_params}"
        ############################
        #WHY DID THIS MESS THINGS UP?
        #@review.place_id = params[:place_id]        
        puts "Params are #{params}"
       
        puts "#{@review.place_id}"
        #.save tries to save review to DB and returns true if success
        if @review.save
            puts "Saved review #{@review}"
            url = 'http://localhost:3000/reviews/new?place_id='
            redirect_to new_review_path(place_id: @review.place_id)

        end    
    end


    #Called when the submit button is pressed and current input 
    # matches old output
    #Params : {"controller"=>"reviews", "action"=>"edit", "id"=>"1"}
    def edit
        #needs to find model based off id
        puts "inside update reviews controller"
        puts "Params are #{params}"
    end

    def update
        puts "id is #{@review.user_id}"
        puts "current user id is #{current_user.id}"
        if @review.user_id == current_user.id
            puts "same user trying to edit"
            @review.update(review_params)
            redirect_to new_review_path(place_id: @review.place_id)
        end
    end



    private
        def review_params
            params.require(:review).permit(:rating,:comment,:place_id, :user_id,:id)
        end

        def find_place
            @place = Place.find(params[:place_id])
        end

        def find_review 
            @review = Review.find(params[:id])
        end

end
