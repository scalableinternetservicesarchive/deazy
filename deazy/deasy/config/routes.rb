Rails.application.routes.draw do
  devise_for :users
  root 'home_page#home'
  get 'home_page/home'
  get 'home_page/search', to: "home_page#search"
  # For details on the DSL available within this file, see https://guides.rubyonrails.org/routing.html
end
