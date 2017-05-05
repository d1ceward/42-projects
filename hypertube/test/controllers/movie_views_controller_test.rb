require 'test_helper'

class MovieViewsControllerTest < ActionDispatch::IntegrationTest
  setup do
    @movie_view = movie_views(:one)
  end

  test "should get index" do
    get movie_views_url
    assert_response :success
  end

  test "should get new" do
    get new_movie_view_url
    assert_response :success
  end

  test "should create movie_view" do
    assert_difference('MovieView.count') do
      post movie_views_url, params: { movie_view: { movie: @movie_view.movie, user: @movie_view.user } }
    end

    assert_redirected_to movie_view_url(MovieView.last)
  end

  test "should show movie_view" do
    get movie_view_url(@movie_view)
    assert_response :success
  end

  test "should get edit" do
    get edit_movie_view_url(@movie_view)
    assert_response :success
  end

  test "should update movie_view" do
    patch movie_view_url(@movie_view), params: { movie_view: { movie: @movie_view.movie, user: @movie_view.user } }
    assert_redirected_to movie_view_url(@movie_view)
  end

  test "should destroy movie_view" do
    assert_difference('MovieView.count', -1) do
      delete movie_view_url(@movie_view)
    end

    assert_redirected_to movie_views_url
  end
end
