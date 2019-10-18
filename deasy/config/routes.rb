Rails.application.routes.draw do
  get 'sessions/new'
  get 'sessions/create'
  get 'sessions/destroy'
  # For details on the DSL available within this file, see https://guides.rubyonrails.org/routing.html
  ############### how it works
#   When your Rails application receives an incoming request for:
# GET /patients/17
# it asks the router to match it to a controller action. If the first matching route is:
# get '/patients/:id', to: 'patients#show'

  root 'users#index'
  resources :users
  resources :sessions, only: [:new, :create, :destroy]
  get 'signup', to: 'users#new' 
  get 'login', to: 'sessions#new', as: 'login'
  get 'logout' , to: 'sessions#destroy', as: 'logout'
  get 'home_page/home', to: 'users#show#home'
  get 'home_page/search', to: "home_page#search"
end
