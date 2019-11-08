class AddSavedPacesToUsers < ActiveRecord::Migration[6.0]
  def change
    add_column :users, :saved_places, :text, default: []
    
  end
end
