require 'sinatra'
require 'sinatra/flash'
require 'sinatra/json'
require 'haml'
require 'json'
require 'mongo'
require 'bcrypt'
require 'password_strength'
require 'geokit'
require 'net/smtp'
require 'faker'
require 'open-uri'
require 'nokogiri'

class M_Fixnum
  N_BYTES = [42].pack('i').size
  N_BITS = N_BYTES * 16
  MAX = 2 ** (N_BITS - 2) - 1
  MIN = -MAX - 1
end

# CONFIGURATION
configure do
  set :environment, :development
  set :bind, '0.0.0.0'
  set :port, 3000
  enable :sessions, :raise_sinatra_param_exceptions
  disable :show_exceptions
  set :session_secret, '2secret4you'
  mongo_db = Mongo::Client.new([ "localhost:27017" ], :database => 'matcha')
  mongo_db[:users].indexes.create_one location: '2dsphere'
  set :db, mongo_db
end

# EXECPTION
before do
  if !@user && session[:user] && session[:user]['username']
    trash = settings.db[:users].find({username: session[:user]['username']})
    @user = trash.first
    if @user
      trash.update_one '$set' => { lastVisit: DateTime.now }
      @unread_count = settings.db[:messages].count({ receiver: @user['username'], has_been_read: false })
      @unread_count2 = settings.db[:notifs].count({ receiver: @user['username'], has_been_read: false })
    end
  end
end

not_found do
  status 404
  haml :'404', locals: { title: 'Error 404' }
end

error do
  redirect back
end

# FUNCTIONS
helpers do
  def h text
    Rack::Utils.escape_html(text)
  end

  def login_user
    users = settings.db[:users].find(username: params['username'])
    return false if users.count == 0
    password = BCrypt::Password.new(users.first['password'])
    return false if password != params['password']
    session[:user] = users.first
    return true
  end

  def send_email to, opts={}
    opts[:from] ||= 'd1ceward.smtp@gmail.com'
    opts[:from_alias] ||= 'matcha'
    opts[:subject] ||= "Notification"
    opts[:body] ||= "Placeholder"
    msg = <<END_OF_MESSAGE
From: #{opts[:from_alias]} <#{opts[:from]}>
To: <#{to}>
Subject: #{opts[:subject]}

#{opts[:body]}
END_OF_MESSAGE
    smtp = Net::SMTP.new('smtp.gmail.com', 587)
    smtp.enable_starttls
    smtp.start('gmail.com', opts[:from], 'Jcz28Ny3', :login) do |smtp|
      smtp.send_message msg, opts[:from], to
    end
  end

  def is_user?
    @user != nil
  end

  def check_conection user1, user2
    settings.db[:likes].count({ '$or' => [
      { liker: user1, liked: user2 },
      { liker: user2, liked: user1 }
    ]}) >= 2
  end

  def get_user_content username
    content = settings.db[:users].find(username: username).first
    return content
  end
end

def auth role
  condition do
    if !send("is_#{role}?")
      flash[:danger] = "Access denied"
      redirect "/users/signin", 303
    end
  end
end

# ROUTES
get '/' do
  haml :index, locals: { title: 'Home' }
end

get '/users/signup' do
  if @user
    redirect :/
  else
    haml :'users/signup', locals: { title: 'Sign Up' }
  end
end

post '/users/signup' do
  special_char = "?<>',?[]}{=)(*&^%$#`~{}"
  special_char_regex = /[#{special_char.gsub(/./){|char| "\\#{char}"}}]/
  raise flash[:danger] = 'Invalid username length' if params['username'].length < 6 || params['username'].length > 26
  raise flash[:danger] = 'Invalid username characters' if params['username'] =~ special_char_regex
  raise flash[:danger] = 'Invalid first name length' if params['first_name'].length < 2 || params['first_name'].length > 26
  raise flash[:danger] = 'Invalid first name characters' if params['first_name'] =~ special_char_regex
  raise flash[:danger] = 'Invalid last name length' if params['last_name'].length < 2 || params['last_name'].length > 26
  raise flash[:danger] = 'Invalid last name characters' if params['last_name'] =~ special_char_regex
  raise flash[:danger] = 'Invalid password length' if params['password'].length < 6 || params['password'].length > 26
  strength = PasswordStrength.test params['username'], params['password']
  raise flash[:danger] = 'Password is not strong enough' if !strength.strong?
  raise flash[:danger] = 'Invalid confirm password' if params['password'] != params['confirm_password']
  raise flash[:danger] = 'Invalid age' if params['age'] !~ /^[0-9]{0,2}$/
  raise flash[:danger] = 'Invalid sex' if params['sex'] != "male" && params['sex'] != "female"
  raise flash[:danger] = 'Invalid email' if params['email'] !~ /\A[\w+\-.]+@[a-z\d\-]+(\.[a-z]+)*\.[a-z]+\z/i
  raise flash[:danger] = 'Username already exist' if settings.db[:users].find(username: params['username']).count != 0
  raise flash[:danger] = 'Email already used' if settings.db[:users].find(email: params['email']).count != 0
  if request.ip.to_s != "127.0.0.1"
   location = Geokit::Geocoders::MultiGeocoder.geocode request.ip.to_s
   raise flash[:danger] = 'Geocoder fail' if !location.lat
  else
   location = Geokit::Geocoders::MultiGeocoder.geocode /(?:[0-9]{1,3}\.){3}[0-9]{1,3}/.match(Nokogiri::HTML(open("http://freegeoip.net/json/")).text).to_s
   raise flash[:danger] = 'Geocoder fail' if !location.lat
  end
  settings.db[:users].insert_one({
    username: params['username'],
    password: BCrypt::Password.create(params['password']),
    first_name: params['first_name'],
    last_name: params['last_name'],
    email: params['email'],
    location: { type: "Point", coordinates: [ location.lng, location.lat ] },
    age: params['age'].to_i,
    orientation: [ 'male', 'female' ],
    sex: params['sex'],
    interests: [ 'Default' ],
    blocked_usernames: ['6309204018941526906623261853960594008381'],
    bio: "No Biography",
    score: 0
  })
  redirect :'/users/signin'
end

get '/users/signin' do
  if @user
    redirect :/
  else
    haml :'users/signin', locals: { title: 'Sign In' }
  end
end

post '/users/signin' do
  raise flash[:danger] = "Authentification fail" if !login_user
  flash[:success] = "Authentification succeded"
  redirect :/
end

get "/users/signout" do
  session.delete(:user)
  redirect :/
end

get "/users/forgot_password" do
  if @user
    redirect :/
  else
    haml :'/users/forgot_password', locals: { title: 'Forgot Password' }
  end
end

post "/users/forgot_password" do
  raise flash[:danger] = 'Invalid email' if !(params['email'] =~ /\A[\w+\-.]+@[a-z\d\-]+(\.[a-z]+)*\.[a-z]+\z/i)
  raise flash[:danger] = 'Email dosen\'t exist' if settings.db[:users].find(email: params['email']).count == 0
  token = SecureRandom.hex
  settings.db[:users].find_one_and_update({ email: params['email'] }, { '$set' => { password_reset_token: token } })
  send_email params['email'], body: "#{request.env['HTTP_HOST']}/users/reset_password?token=#{token}"
  flash[:success] = "An email was send"
  redirect :/
end

get "/users/reset_password" do
  if @user
    redirect :/
  else
    haml :'/users/reset_password', locals: { title: 'Reset Password', token: params['token'] }
  end
end

post "/users/reset_password" do
  raise flash[:danger] = 'Invalid password length' if params['password'].length < 6 || params['password'].length > 26
  strength = PasswordStrength.test params['username'], params['password']
  raise flash[:danger] = 'Password is not strong enough' if !strength.strong?
  raise flash[:danger] = 'Invalid confirm password' if params['password'] != params['confirm_password']
  raise flash[:danger] = 'Invalid token' if settings.db[:users].find(password_reset_token: params['token']).count == 0
  settings.db[:users].find_one_and_update({ password_reset_token: params['token'] }, {
      '$unset' => { 'password_reset_token' => '' },
      '$set' => { password: BCrypt::Password.create(params['password']) }
  })
  flash[:success] = 'Password successfully reset'
  redirect :'users/signin'
end

get '/users/all/:page', auth: :user do
  params['min_age'] = M_Fixnum::MIN if !params['min_age'] || params['min_age'].to_i == 0
  params['max_age'] = M_Fixnum::MAX if !params['max_age'] || params['max_age'].to_i == 0
  params['min_score'] = M_Fixnum::MIN if !params['min_score'] || params['min_score'].to_i == 0
  params['max_score'] = M_Fixnum::MAX if !params['max_score'] || params['max_score'].to_i == 0
  params['max_distance'] = "max" if !params['max_distance'] || params['max_distance'].to_i == 0
  params['order_by'] = 1 if params['order_by'].to_i != 1 && params['order_by'].to_i != -1
  params['sort_by'] = 0 if params['sort_by'].to_i < 0 || params['sort_by'].to_i > 4
  if params['page'].to_i < 0
    flash[:danger] = "Page doesn't exists"
    redirect :'/users/all/1'
  end
  if params['tag'] =~ /,/
    tags = params['tag'].split(',')
    tags = tags.map do |tag|
      raise flash[:danger] = 'Tag must be separated by coma' if tag !~ /\A[\w]{2,42}$/i
      tag.capitalize
    end
    puts tags
  elsif params['tag'] && params['tag'] != ""
    raise flash[:danger] = 'Invalid tag' if params['tag'] !~ /\A[\w]{2,42}$/i
    tags = [ params['tag'].downcase.capitalize ]
  else
    tags = @user['interests']
  end
  if params['sort_by'].to_i == 1
    sort_obj = { :age => params['order_by'].to_i }
  elsif params['sort_by'].to_i == 2
    sort_obj = { :distance => params['order_by'].to_i }
  elsif params['sort_by'].to_i == 3
    sort_obj = { :score => params['order_by'].to_i }
  elsif params['sort_by'].to_i == 4
    sort_obj = { :interests => params['order_by'].to_i }
  else
    sort_obj = { :distance => 1, :score => 1 }
  end
  if params['max_distance'] == "max"
    max_distance = M_Fixnum::MAX
  else
    max_distance = params['max_distance'].to_i * 1000
  end
  users = settings.db[:users].aggregate([
    { '$geoNear' => { near: @user['location'], spherical: true, maxDistance: max_distance, distanceField: 'distance', num: 420000, query: {
      username: { '$ne' => @user['username'] },
      sex: { '$in' => @user['orientation'] },
      interests: { tags == @user['interests'] ? '$in' : '$all' => tags },
      orientation: @user['sex'],
      :age => { '$gte' => params['min_age'].to_i, '$lte' => params['max_age'].to_i },
      :score => { '$gte' => params['min_score'].to_i, '$lte' => params['max_score'].to_i }
    } } },
    { '$match' => { username: { '$nin' => @user['blocked_usernames'] } } },
    { '$sort' => sort_obj },
    { '$skip' => 15 * (params['page'].to_i - 1) },
    { '$limit' => 15 }
  ])
  puts users.first
  if users.count < 1 && params['page'].to_i > 1
    flash[:danger] = "Page doesn't exists"
    redirect :'/users/all/1'
  end
  haml :'users/all', locals: { title: 'Browse', users: users, page: params[:page].to_i }
end

get '/users/show/:username', auth: :user do
  if user = settings.db[:users].find({ username: params['username'] }).first
    likes = settings.db[:likes].find liker: @user['username'], liked: params['username']
    report_nb = settings.db[:reports].find(reported: params['username']).count
    if params['username'] != @user['username']
      if settings.db[:visits].find({ visiter: @user['username'], visited: params['username'] }).count < 1
        if !(user['blocked_usernames'] && user['blocked_usernames'].include?(@user['username']))
          settings.db[:notifs].insert_one receiver: params['username'], message: "#{@user['username']} visited your profile", has_been_notice: false, has_been_read: false, date: DateTime.now
        end
        settings.db[:visits].insert_one visiter: @user['username'], visited: params['username']
      end
    end
    haml :'users/show', locals: { title: "Show #{params['username']}", user: user, i_like: (likes.count > 0), report_nb: report_nb }
  else
    redirect not_found
  end
end

get '/users/edit/:username', auth: :user do
  if params[:username] == @user['username']
    haml :'users/edit', locals: { title: "Show #{params[:username]}", user: @user }
  else
    redirect not_found
  end
end

post '/users/edit/:username', auth: :user do
  if params[:username] == @user['username']
    users = settings.db[:users].find username: @user['username']
    if params[:file]
      raise flash[:danger] = 'Invalid file type' if params[:file][:type] != "image/jpeg" && params[:file][:type] != "image/png"
      raise flash[:danger] = 'Too many photos' if users.first['pictures'] && users.first['pictures'].count == 5
      FileUtils.cp params[:file][:tempfile].path, 'public/uploads/' + File.basename(params[:file][:tempfile].path)
      users.update_one '$push' => { pictures: '/uploads/' + File.basename(params[:file][:tempfile].path) }
      users.update_one '$set' => { profilePicture: '/uploads/' + File.basename(params[:file][:tempfile].path) }
    end
    raise flash[:danger] = 'Invalid age' if params[:age].to_i < 18 || params[:age].to_i > 120
    raise flash[:danger] = 'Invalid email' if !(params['email'] =~ /\A[\w+\-.]+@[a-z\d\-]+(\.[a-z]+)*\.[a-z]+\z/i)
    raise flash[:danger] = 'Invalid first name' if params['first_name'] !~ /^[a-z ,.'-]+$/i
    raise flash[:danger] = 'Invalid last name' if params['last_name'] !~ /^[a-z ,.'-]+$/i
    raise flash[:danger] = 'Invalid bio' if params['bio'].length < 1 || params['bio'].length > 1000
    raise flash[:danger] = 'Email already used' if params['email'] != users.first['email'] && settings.db[:users].find(email: params['email']).count != 0
    users.update_one '$set' => {
      age: params[:age].to_i,
      email: params['email'],
      location: { type: "Point", coordinates: [ params['location-lng'].to_f, params['location-lat'].to_f ] },
      sex: params['sex'],
      orientation: params['orientation'],
      first_name: params['first_name'],
      last_name: params['last_name'],
      bio: h(params['bio'])
    }
    flash[:success] = 'Info updated'
    redirect "/users/edit/#{users.first['username']}"
  else
    redirect not_found
  end
end

post '/users/edit_photo/?', auth: :user do
  content_type :json
  if @user['pictures'].include?(params['picture'])
    users = settings.db[:users].find username: @user['username']
    if params['action'].to_i == 0
      users.update_one '$set' => { profilePicture: params['picture'] }
      { :state => 1 }.to_json
    else
      users.update_one '$pull' => { pictures: params['picture'] }
      FileUtils.rm 'public' + params['picture']
      { :state => 1 }.to_json
    end
  else
    { :state => 0, :message => "Invalid picture" }.to_json
  end
end

post "/users/add_tag/?", auth: :user do
  content_type :json
  if @user['interests'].count <= 11
    if params['tag'] =~ /\A[\w]{2,42}$/i && params['tag'] != "Default"
      if @user['interests'].include?(params['tag'])
        { :state => 0, :message => "Tag already exists" }.to_json
      else
        settings.db[:users].find_one_and_update({ username: @user['username'] }, { '$push' => { interests: params['tag'].downcase.capitalize } })
        { :state => 1 }.to_json
      end
    else
      { :state => 0, :message => "Invalid tag" }.to_json
    end
  else
    { :state => 0, :message => "Maximum tag reached" }.to_json
  end
end

post "/users/delete_tag/?", auth: :user do
  content_type :json
  if params['tag'] =~ /\A[\w]{2,42}$/i && params['tag'] != "Default"
    settings.db[:users].find_one_and_update({ username: @user['username'] },
      { '$pull' => { interests: params['tag'] }
    })
    { :state => 1 }.to_json
  else
    { :state => 0, :message => "Invalid tag" }.to_json
  end
end

get "/report/:username", auth: :user do
  raise flash[:danger] = 'Invalid user' if settings.db[:users].find(username: params['username']).count == 0 || @user['username'] == params['username']
  raise flash[:danger] = 'Already reported this user' if settings.db[:reports].find(reporter: @user['username'], reported: params['username']).count != 0
  settings.db[:reports].insert_one({
    reporter: @user['username'],
    reported: params['username']
  })
  flash[:success] = 'Reported'
  redirect back
end

get "/block/:username", auth: :user do
  raise flash[:danger] = 'Invalid user' if settings.db[:users].find(username: params['username']).count == 0 || @user['username'] == params['username']
  settings.db[:users].find_one_and_update({ username: @user['username'] }, { '$push' => { 'blocked_usernames' => params['username'] } })
  flash[:success] = 'Blocked'
  redirect back
end

get "/unblock/:username", auth: :user do
  raise flash[:danger] = 'Invalid user' if settings.db[:users].find(username: params['username']).count == 0 || @user['username'] == params['username']
  settings.db[:users].find_one_and_update({username: @user['username']}, {
    '$pull' => {'blocked_usernames' => params['username']}
  })
  flash[:success] = 'Unblocked'
  redirect back
end

get "/like/:username", auth: :user do
  user = settings.db[:users].find(username: params['username'])
  raise flash[:danger] = 'Invalid user' if user.count == 0 || @user['username'] == params['username']
  raise flash[:danger] = 'You must have a photo to like someone' if !@user['profilePicture']
  settings.db[:likes].insert_one liker: @user['username'], liked: params['username']
  if check_conection(params['username'], @user['username'])
    settings.db[:users].find({
      username: { '$in' => [ @user['username'], params['username'] ] }
    }).update_many({
      '$inc' => { score: 100 }
    })
  end
  settings.db[:users].find_one_and_update({ username: params['username'] },
    { '$inc' => { score: 20 }
  })
  if !(user.first['blocked_usernames'] && user.first['blocked_usernames'].include?(@user['username']))
    settings.db[:notifs].insert_one receiver: params['username'], message: "#{@user['username']} liked your profile", has_been_notice: false, has_been_read: false, date: DateTime.now
  end
  redirect back
end

get "/unlike/:username", auth: :user do
  user = settings.db[:users].find(username: params['username'])
  raise flash[:danger] = 'Invalid user' if user.count == 0 || @user['username'] == params['username']
  settings.db[:likes].delete_many liker: @user['username'], liked: params['username']
  settings.db[:users].find_one_and_update({ username: params['username'] },
    { '$inc' => { score: -10 }
  })
  if !(user.first['blocked_usernames'] && user.first['blocked_usernames'].include?(@user['username']))
    settings.db[:notifs].insert_one receiver: params['username'], message: "#{@user['username']} unliked your profile", has_been_notice: false, has_been_read: false, date: DateTime.now
  end
  redirect back
end

get "/users/likes/?", auth: :user do
  likes = settings.db[:likes].find liked: @user['username']
  haml :'users/likes', locals: { title: "Likes", likes: likes }
end

get "/users/visits/?", auth: :user do
  visits = settings.db[:visits].find visited: @user['username']
  haml :'users/visits', locals: { title: "Visits", visits: visits }
end

get '/messages/all', auth: :user do
  convs = settings.db[:convs].find({
    '$or' => [ { username1: @user['username'] }, { username2: @user['username'] } ]
  })
  haml :'messages/all', locals: { title: "Conversation list", convs: convs }
end

get '/messages/show/:username', auth: :user do
  raise flash[:danger] = 'Invalid user' if settings.db[:users].find({username: params['username']}).count < 1
  receiver = settings.db[:users].find({username: params['username']}).first
  raise flash[:danger] = 'This user blocked you' if receiver['blocked_usernames'] && receiver['blocked_usernames'].include?(@user['username'])
  raise flash[:danger] = 'You must be mutually liked to chat' if !check_conection(params['username'], @user['username'])
  conv = settings.db[:convs].find({
    '$or' => [ { username1: params['username'], username2: @user['username'] }, { username1: @user['username'], username2: params['username'] } ]
  }).first
  if conv
     messages = settings.db[:messages].find({ conv: conv['_id'] })
     settings.db[:messages].find({ conv: conv['_id'], emitter: params['username'] }).update_many({ '$set' => { has_been_read: true } })
  end
  haml :'messages/show', locals: { title: "Messages from #{params[:username]}", receiver: receiver, messages: messages }
end

post '/messages/send/:username', auth: :user do
  raise flash[:danger] = 'Invalid user' if settings.db[:users].find({username: params['username']}).count < 1
  receiver = settings.db[:users].find({username: params['username']}).first
  raise flash[:danger] = 'This user blocked you' if receiver['blocked_usernames'] && receiver['blocked_usernames'].include?(@user['username'])
  raise flash[:danger] = 'You must be mutually liked to chat' if !check_conection(params['username'], @user['username'])
  raise flash[:danger] = 'Invalid message' if params['message'].length < 1 || params['message'].length > 1000
  conv = settings.db[:convs].find({
    '$or' => [ { username1: params['username'], username2: @user['username'] }, { username1: @user['username'], username2: params['username'] } ]
  }).first
  if !conv
    settings.db[:convs].insert_one({ username1: @user['username'], username2: params['username'] })
    conv = settings.db[:convs].find({ username1: @user['username'], username2: params['username'] }).first
  end
  settings.db[:messages].insert_one({
    conv: conv['_id'],
    emitter: @user['username'],
    receiver: params['username'],
    content: h(params['message']),
    has_been_read: false,
    date: DateTime.now
  })
  settings.db[:notifs].insert_one receiver: params['username'], message: "#{@user['username']} send you a message", has_been_notice: false, has_been_read: false, date: DateTime.now
  redirect back
end

get '/users/search/:page', auth: :user do
  params['min_age'] = M_Fixnum::MIN if !params['min_age'] || params['min_age'].to_i == 0
  params['max_age'] = M_Fixnum::MAX if !params['max_age'] || params['max_age'].to_i == 0
  params['min_score'] = M_Fixnum::MIN if !params['min_score'] || params['min_score'].to_i == 0
  params['max_score'] = M_Fixnum::MAX if !params['max_score'] || params['max_score'].to_i == 0
  params['max_distance'] = "max" if !params['max_distance'] || params['max_distance'].to_i == 0
  params['order_by'] = 1 if params['order_by'].to_i != 1 && params['order_by'].to_i != -1
  params['sort_by'] = 0 if params['sort_by'].to_i < 0 || params['sort_by'].to_i > 4
  if params['page'].to_i < 0
    flash[:danger] = "Page doesn't exists"
    redirect :'/users/search/1'
  end
  if params['tag'] =~ /,/
    tags = params['tag'].split(',')
    tags = tags.map do |tag|
      raise flash[:danger] = 'Tag must be separated by coma' if tag !~ /\A[\w]{2,42}$/i
      tag.capitalize
    end
    puts tags
  elsif params['tag'] && params['tag'] != ""
    raise flash[:danger] = 'Invalid tag' if params['tag'] !~ /\A[\w]{2,42}$/i
    tags = [ params['tag'].downcase.capitalize ]
  else
    tags = [ "Default" ]
  end
  if params['sort_by'].to_i == 1
    sort_obj = { :age => params['order_by'].to_i }
  elsif params['sort_by'].to_i == 2
    sort_obj = { :distance => params['order_by'].to_i }
  elsif params['sort_by'].to_i == 3
    sort_obj = { :score => params['order_by'].to_i }
  elsif params['sort_by'].to_i == 4
    sort_obj = { :interests => params['order_by'].to_i }
  else
    sort_obj = { :_id => 1 }
  end
  if params['max_distance'] == "max"
    max_distance = M_Fixnum::MAX
  else
    max_distance = params['max_distance'].to_i * 1000
  end
  users = settings.db[:users].aggregate([
    { '$geoNear' => { near: @user['location'], spherical: true, maxDistance: max_distance, distanceField: 'distance', num: 420000, query: {
      username: { '$ne' => @user['username'] },
      sex: { '$in' => @user['orientation'] },
      interests: { '$all' => tags },
      orientation: @user['sex'],
      :age => { '$gte' => params['min_age'].to_i, '$lte' => params['max_age'].to_i },
      :score => { '$gte' => params['min_score'].to_i, '$lte' => params['max_score'].to_i }
    } } },
    { '$match' => { username: { '$nin' => @user['blocked_usernames'] } } },
    { '$sort' => sort_obj },
    { '$skip' => 15 * (params['page'].to_i - 1) },
    { '$limit' => 15 }
  ])
  if users.count < 1 && params['page'].to_i > 1
    flash[:danger] = "Page doesn't exists"
    redirect :'/users/search/1'
  end
  haml :'users/search', locals: { title: "Search", users: users, page: params[:page].to_i }
end

get "/users/notifs/?", auth: :user do
  notifs = settings.db[:notifs].find(receiver: @user['username']).sort(date: -1)
  notifs.update_many({ '$set' => { has_been_notice: true, has_been_read: true } })
  haml :'users/notifs', locals: { title: "Notifications", notifs: notifs }
end

post '/notifs/?' do
  json = {}
  if @user
    notifs = settings.db[:notifs].find receiver: @user['username'], has_been_notice: false, has_been_read: false
    if notifs.count > 0
      out = notifs.to_a
      notifs.update_many({ '$set' => { has_been_notice: true } })
    end
  end
  json out
end

get '/grp/:count' do
  params[:count].to_i.times do
    first_name = Faker::Name.first_name
    last_name = Faker::Name.last_name
    slug = Faker::Internet.slug(first_name + last_name)
    user_name = Faker::Internet.user_name(first_name + last_name)
    pictures = []
    5.times do |i|
      pictures << Faker::Avatar.image("#{slug}-#{i}", "500x500", "jpg")
    end
    orientation = [
      ['male','female'],
      ['male'],
      ['female']
    ]
    settings.db[:users].insert_one({
      username: user_name,
      password: BCrypt::Password.create('1234'),
      first_name: first_name,
      last_name: last_name,
      bio: Faker::Hipster.paragraph(2, false, 4),
      email: Faker::Internet.safe_email(first_name + last_name),
      location: { type: "Point", coordinates: [ Faker::Address.longitude.to_i, Faker::Address.latitude.to_i ] },
      age: 18.upto(50).to_a.shuffle.first,
      orientation: orientation.shuffle.first,
      sex: ['female','male'].shuffle.first,
      lastVisit: Faker::Date.backward(0.upto(14).to_a.shuffle.first),
      interests: ['Party', 'Sausages', 'Beer', 'Music', 'Travel', 'People', 'Me'].shuffle[0..2],
      pictures: pictures[1..4],
      blocked_usernames: ['6309204018941526906623261853960594008381'],
      profilePicture: pictures[0],
      score: 0,
    })
    settings.db[:users].find_one_and_update({ username: user_name }, { '$push' => { interests: "Default" } })
  end
  redirect :'/'
end
