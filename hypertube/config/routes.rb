Rails.application.routes.draw do
  resources :user_friends do
    post :accept, on: :member
  end

  resources :movie_views
  resources :movie_downloads
  devise_for :users, only: :omniauth_callbacks, controllers: {omniauth_callbacks: 'users/omniauth_callbacks'}

  scope "(:locale)", locale: /en|fr/ do
    devise_for :users, skip: :omniauth_callbacks, :controllers => { :omniauth_callbacks => "users/omniauth_callbacks", :registrations => "users/registrations"}
    devise_scope :user do
      get '/users/:username', to: 'users/sessions#show', as: :user
      delete 'sign_out', to: 'devise/sessions#destroy', as: :destroy_user_session_path
    end

    root to: 'home#index'

    resources :movies do
      resources :comments
      get :unavailable, on: :collection
      get :my_list, on: :collection
    end

    resources :user_downloads
    resources :user_movies
  end

  namespace :api, constraints: { format: 'json' } do
    namespace :v1 do
      resources :movies do
        resources :comments
      end
      resources :comments
      resources :users
    end
  end

    require 'sidekiq/web'
    require 'sidekiq/cron/web'
    mount Sidekiq::Web => '/sidekiq'
end
