class Api::V1::UsersController < Api::ApiController
  def update
    render json: {error: "Forbidden"}, status: :forbidden
  end

  def destroy
    render json: {error: "Forbidden"}, status: :forbidden
  end
end
