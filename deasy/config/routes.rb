Rails.application.routes.draw do
  get 'home_page/home'
  get 'home_page/search', to: "home_page#search"
  get 'googleapi', to: 'googleapi#index'
  # For details on the DSL available within this file, see https://guides.rubyonrails.org/routing.html
end
