Rails.application.routes.draw do
  get 'saved_places/home'
  devise_for :users
  root 'home_page#home'
  get 'home_page/home'
  get 'home_page/search', to: "home_page#search"
  get 'home_page/search2', to: "home_page#search2"
  post 'home_page/save'
  get 'home_page/details'
  # For details on the DSL available within this file, see https://guides.rubyonrails.org/routing.html
end
