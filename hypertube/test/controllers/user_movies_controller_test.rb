require 'test_helper'

class UserMoviesControllerTest < ActionDispatch::IntegrationTest
  setup do
    @user_movie = user_movies(:one)
  end

  test "should get index" do
    get user_movies_url
    assert_response :success
  end

  test "should get new" do
    get new_user_movie_url
    assert_response :success
  end

  test "should create user_movie" do
    assert_difference('UserMovie.count') do
      post user_movies_url, params: { user_movie: { movie_id: @user_movie.movie_id, user_id: @user_movie.user_id } }
    end

    assert_redirected_to user_movie_url(UserMovie.last)
  end

  test "should show user_movie" do
    get user_movie_url(@user_movie)
    assert_response :success
  end

  test "should get edit" do
    get edit_user_movie_url(@user_movie)
    assert_response :success
  end

  test "should update user_movie" do
    patch user_movie_url(@user_movie), params: { user_movie: { movie_id: @user_movie.movie_id, user_id: @user_movie.user_id } }
    assert_redirected_to user_movie_url(@user_movie)
  end

  test "should destroy user_movie" do
    assert_difference('UserMovie.count', -1) do
      delete user_movie_url(@user_movie)
    end

    assert_redirected_to user_movies_url
  end
end
