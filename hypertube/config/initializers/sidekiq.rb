Sidekiq.default_worker_options = { 'backtrace' => true }

url = Rails.env.production? ? 'redis://localhost:6379/12' : 'redis://localhost:6379/12'

Sidekiq.configure_server do |config|
  config.redis = { url: url }
end

Sidekiq.configure_client do |config|
  config.redis = { url: url }
end


schedule_file = Rails.root.join("config", "schedule.yml")

if File.exists?(schedule_file)
  Sidekiq::Cron::Job.load_from_hash YAML.load_file(schedule_file)
end
