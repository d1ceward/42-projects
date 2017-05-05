class Api::ApiController < ApplicationController
  include Api::V1

  skip_before_filter :verify_authenticity_token
  before_action :check_params, only: [:create, :update]

  rescue_from ActionController::RoutingError, with: -> { render_404 }
  rescue_from ActiveRecord::RecordNotFound,   with: -> { render_404 }


  def index
    begin
      serializer = self.class.const_get("#{self.controller_name}_serializer".classify.to_sym)
    rescue
      serializer = self.class.const_get("#{self.controller_name.singularize}_serializer".classify.to_sym)
    end
    render json: collection, each_serializer: serializer
  end

  def show
    render json: resource, serializer: self.class.const_get("#{self.controller_name.singularize}_serializer".classify.to_sym)
  end

  def create
    if resource = object.create(resource_params)
      return render json: resource
    else
      render(json: resource.errors, status: :unprocessable_entity)
      return
    end
  end

  def update
    if resource.update(resource_params)
      return render json: resource
    else
      render(json: resource.errors, status: :unprocessable_entity)
      return
    end
  end

  def destroy
    if resource.destroy
      head :no_content, status: :ok
    else
      render json: resource.errors, status: :unprocessable_entity
    end
  end

  def resource
    @resource ||= object.find params[:id]
  end

  def collection
    object.all
  end

  def resource_params
    send("#{self.controller_name}_params") #rescue nil
  end

  def check_params
    begin
      resource_params
    rescue
      return render json: {error: 'Bad request'}, status: :bad_request
    end
  end

  def render_404
    render json: {error: "Not found"}, status: 404
  end

  def object
    self.controller_name.classify.constantize
  end
end
