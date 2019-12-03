# This file should contain all the record creation needed to seed the database with its default values.
# The data can then be loaded with the rails db:seed command (or created alongside the database with db:setup).
#
# Examples:
#
#   movies = Movie.create([{ name: 'Star Wars' }, { name: 'Lord of the Rings' }])
#   Character.create(name: 'Luke', movie: movies.first)

2000.times do
  Review.create(rating: 5, comment: "wow", place_id: "21617bb2f9914c04e45b3efccf9b179875a89f8b")
end

