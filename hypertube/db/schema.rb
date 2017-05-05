# This file is auto-generated from the current state of the database. Instead
# of editing this file, please use the migrations feature of Active Record to
# incrementally modify your database, and then regenerate this schema definition.
#
# Note that this schema.rb definition is the authoritative source for your
# database schema. If you need to create the application database on another
# system, you should be using db:schema:load, not running all the migrations
# from scratch. The latter is a flawed and unsustainable approach (the more migrations
# you'll amass, the slower it'll run and the greater likelihood for issues).
#
# It's strongly recommended that you check this file into your version control system.

ActiveRecord::Schema.define(version: 20170425152044) do

  # These are extensions that must be enabled in order to support this database
  enable_extension "plpgsql"

  create_table "comments", force: :cascade do |t|
    t.integer  "user_id"
    t.integer  "movie_id"
    t.text     "content"
    t.datetime "created_at", null: false
    t.datetime "updated_at", null: false
    t.index ["movie_id"], name: "index_comments_on_movie_id", using: :btree
    t.index ["user_id"], name: "index_comments_on_user_id", using: :btree
  end

  create_table "movie_downloads", force: :cascade do |t|
    t.integer  "movie_id"
    t.datetime "downloaded_at"
    t.boolean  "downloading"
    t.datetime "created_at",    null: false
    t.datetime "updated_at",    null: false
    t.index ["movie_id"], name: "index_movie_downloads_on_movie_id", using: :btree
  end

  create_table "movie_views", force: :cascade do |t|
    t.integer  "movie_id"
    t.integer  "user_id"
    t.datetime "created_at", null: false
    t.datetime "updated_at", null: false
    t.index ["movie_id"], name: "index_movie_views_on_movie_id", using: :btree
    t.index ["user_id"], name: "index_movie_views_on_user_id", using: :btree
  end

  create_table "movies", force: :cascade do |t|
    t.integer  "uid_imdb"
    t.text     "title"
    t.text     "url"
    t.integer  "length"
    t.text     "trailer_url"
    t.integer  "votes"
    t.text     "year"
    t.datetime "created_at",  null: false
    t.datetime "updated_at",  null: false
    t.string   "poster"
    t.index ["uid_imdb"], name: "index_movies_on_uid_imdb", unique: true, using: :btree
  end

  create_table "subtiltes", force: :cascade do |t|
    t.string  "path"
    t.string  "label"
    t.integer "movie_id"
    t.index ["movie_id"], name: "index_subtiltes_on_movie_id", using: :btree
  end

  create_table "torrents", force: :cascade do |t|
    t.integer  "uid_imdb"
    t.text     "name"
    t.text     "magnet_link"
    t.datetime "created_at",  null: false
    t.datetime "updated_at",  null: false
    t.string   "file_path"
  end

  create_table "user_friends", force: :cascade do |t|
    t.integer  "user_id"
    t.integer  "friend_user_id"
    t.datetime "request_send_at"
    t.datetime "request_accepted_at"
    t.datetime "created_at",          null: false
    t.datetime "updated_at",          null: false
    t.index ["user_id"], name: "index_user_friends_on_user_id", using: :btree
  end

  create_table "user_movies", force: :cascade do |t|
    t.integer  "user_id"
    t.integer  "movie_id"
    t.datetime "created_at", null: false
    t.datetime "updated_at", null: false
    t.index ["movie_id"], name: "index_user_movies_on_movie_id", using: :btree
    t.index ["user_id"], name: "index_user_movies_on_user_id", using: :btree
  end

  create_table "user_providers", force: :cascade do |t|
    t.integer  "user_id"
    t.string   "provider"
    t.string   "uid"
    t.datetime "created_at", null: false
    t.datetime "updated_at", null: false
    t.index ["user_id"], name: "index_user_providers_on_user_id", using: :btree
  end

  create_table "users", force: :cascade do |t|
    t.string   "email",                  default: "", null: false
    t.string   "encrypted_password",     default: "", null: false
    t.string   "reset_password_token"
    t.datetime "reset_password_sent_at"
    t.datetime "remember_created_at"
    t.integer  "sign_in_count",          default: 0,  null: false
    t.datetime "current_sign_in_at"
    t.datetime "last_sign_in_at"
    t.string   "current_sign_in_ip"
    t.string   "last_sign_in_ip"
    t.datetime "created_at",                          null: false
    t.datetime "updated_at",                          null: false
    t.string   "username"
    t.string   "first_name"
    t.string   "last_name"
    t.string   "language"
    t.text     "viewed"
    t.string   "cover"
    t.string   "custom_cover"
    t.index ["email"], name: "index_users_on_email", unique: true, using: :btree
    t.index ["reset_password_token"], name: "index_users_on_reset_password_token", unique: true, using: :btree
    t.index ["username"], name: "index_users_on_username", unique: true, using: :btree
  end

end
