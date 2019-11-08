class ChangePlaceIdToBeStringInReviews < ActiveRecord::Migration[6.0]
  def change
    change_column :reviews, :place_id, :string
  end
end
