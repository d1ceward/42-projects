require 'test_helper'

class MovieDownloadsControllerTest < ActionDispatch::IntegrationTest
  setup do
    @movie_download = movie_downloads(:one)
  end

  test "should get index" do
    get movie_downloads_url
    assert_response :success
  end

  test "should get new" do
    get new_movie_download_url
    assert_response :success
  end

  test "should create movie_download" do
    assert_difference('MovieDownload.count') do
      post movie_downloads_url, params: { movie_download: { downloaded_at: @movie_download.downloaded_at, downloading: @movie_download.downloading, movie_id: @movie_download.movie_id } }
    end

    assert_redirected_to movie_download_url(MovieDownload.last)
  end

  test "should show movie_download" do
    get movie_download_url(@movie_download)
    assert_response :success
  end

  test "should get edit" do
    get edit_movie_download_url(@movie_download)
    assert_response :success
  end

  test "should update movie_download" do
    patch movie_download_url(@movie_download), params: { movie_download: { downloaded_at: @movie_download.downloaded_at, downloading: @movie_download.downloading, movie_id: @movie_download.movie_id } }
    assert_redirected_to movie_download_url(@movie_download)
  end

  test "should destroy movie_download" do
    assert_difference('MovieDownload.count', -1) do
      delete movie_download_url(@movie_download)
    end

    assert_redirected_to movie_downloads_url
  end
end
