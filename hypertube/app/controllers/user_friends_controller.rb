class UserFriendsController < InheritedResources::Base

  def accept
    resource = UserFriend.find(params[:id])
    resource.accept_request
    respond_to do |format|
      format.json {return render json: resource}
      format.html {return redirect_back(fallback_location: root_path)}
    end
  end

  def create
    create! { return redirect_back(fallback_location: root_path) }
  end

  def destroy
    destroy! { return redirect_back(fallback_location: root_path) }
  end

  private

  def user_friend_params
    params.require(:user_friend).permit(:user_id, :friend_user_id, :request_send_at, :request_accepted_at)
  end

end
