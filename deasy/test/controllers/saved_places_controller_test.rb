require 'test_helper'

class SavedPlacesControllerTest < ActionDispatch::IntegrationTest
  test "should get home" do
    get saved_places_home_url
    assert_response :success
  end

end
