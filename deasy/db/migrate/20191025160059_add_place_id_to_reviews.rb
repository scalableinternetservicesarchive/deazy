class AddPlaceIdToReviews < ActiveRecord::Migration[6.0]
  def change
    add_column :reviews, :place_id, :integer
  end
end
