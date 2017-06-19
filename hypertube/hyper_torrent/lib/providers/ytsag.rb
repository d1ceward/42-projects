# set ":ssl_verify_mode" to "OpenSSL::SSL::VERIFY_NONE" if ssl fail

module YtsAg
  BASE_URL = 'https://yts.ag'

  class Search
    attr_accessor :results, :search_string, :uids_imdb

    def initialize search_string
      @results = []
      @search_string = URI.encode(search_string)
    end

    def execute
      doc = JSON.parse(open("#{YtsAg::BASE_URL}/api/v2/list_movies.json?query_term=#{search_string}").read)
      if doc['data']['movie_count'] > 0
        doc['data']['movies'].each do |row|
          @results << YtsAg::Result.new(row)
        end
      end
      @results
    end
  end

  class Result
    attr_accessor :id, :uid_imdb, :name, :magnet_link

    def initialize row
      self.id = row['id']
      self.uid_imdb = row['imdb_code'].sub(/^tt/, '')
      self.name = row['title_long']
      row['torrents'].each do |t|
        if t['quality'] == '720p'
          self.magnet_link = "magnet:?xt=urn:btih:#{t['hash']}&dn=#{URI.encode(row['title_long'])}&tr=udp%3A%2F%2Fglotorrents.pw%3A6969%2Fannounce&tr=udp%3A%2F%2Ftracker.openbittorrent.com%3A80&tr=udp%3A%2F%2Ftracker.coppersurfer.tk%3A6969&tr=udp%3A%2F%2Ftracker.leechers-paradise.org%3A6969&tr=udp%3A%2F%2Fp4p.arenabg.ch%3A1337&tr=udp%3A%2F%2Ftracker.internetwarriors.net%3A1337"
          break
        end
      end
    end
  end
end
