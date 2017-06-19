require 'uri'
require 'nokogiri'
require 'open-uri'
require 'openssl'
require 'json'

require_relative 'providers/the_pirate_bay'
require_relative 'providers/1337x'
require_relative 'providers/ytsag'

class HyperTorrent
  attr_accessor :results

  def initialize(search_term = nil, limit = 5)
    results = []
    uids_imdb = []
    if search_term
      results << YtsAg::Search.new(search_term).execute
    else
      results << ThePirateBay::Top.new(limit / 2, uids_imdb).execute
      results << OneThreeThreeSevenx::Top.new(limit / 2, uids_imdb).execute
    end
    @results = results.flatten
  end
end
