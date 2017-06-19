# set ":ssl_verify_mode" to "OpenSSL::SSL::VERIFY_NONE" if ssl fail

module OneThreeThreeSevenx
  BASE_URL = 'http://1337x.to'

  class Top
    attr_accessor :results, :limit, :uids_imdb

    def initialize limit, uids_imdb
      @results = []
      @limit = limit
      @uids_imdb = uids_imdb
    end

    def execute
      doc = Nokogiri::HTML(open("#{OneThreeThreeSevenx::BASE_URL}/top-100-eng-movies").read)
      doc.css('.table tr').each_with_index do |row, index|
        next if index == 0
        next if row.css('td').size <= 1
        tr_doc = Nokogiri::HTML(open("#{OneThreeThreeSevenx::BASE_URL}/#{row.inner_html.match(/torrent\/[\d]+\/[a-zA-Z0-9\-]*\//)}").read)
        imdb_url = tr_doc.inner_html.match(/http:\/\/www\.imdb\.com\/title\/tt([0-9]{1,7})\//)
        next if imdb_url == nil
        next if @uids_imdb.include? imdb_url[1]
        @uids_imdb << imdb_url[1]
        magnet_a = tr_doc.css('.btn-magnet')
        @results << OneThreeThreeSevenx::Result.new(row, imdb_url[1], magnet_a)
        if @results.size >= @limit
          break
        end
      end
      @results
    end
  end

  class Search
    attr_accessor :results, :limit, :search_string, :uids_imdb

    def initialize limit, search_string, uids_imdb
      @results = []
      @limit = limit
      @search_string = URI.encode(search_string)
      @uids_imdb = uids_imdb
    end

    def execute
      doc = Nokogiri::HTML(open("#{OneThreeThreeSevenx::BASE_URL}/sort-category-search/#{search_string}/Movies/seeders/desc/0/").read)
      doc.css('.table tr').each_with_index do |row, index|
        next if (index == 0)
        next if (row.css('td').size <= 1)
        tr_doc = Nokogiri::HTML(open("#{OneThreeThreeSevenx::BASE_URL}/#{row.inner_html.match(/torrent\/[\d]+\/[a-zA-Z0-9\-]*\//)}").read)
        imdb_url = tr_doc.inner_html.match(/http:\/\/www\.imdb\.com\/title\/tt([0-9]{1,7})\//)
        next if imdb_url == nil
        next if @uids_imdb.include? imdb_url[1]
        @uids_imdb << imdb_url[1]
        next if !tr_doc.inner_html.match(/<span>English/)
        magnet_a = tr_doc.css('.btn-magnet')
        @results << OneThreeThreeSevenx::Result.new(row, imdb_url[1], magnet_a)
        if @results.size >= @limit
          break
        end
      end
      @results
    end
  end

  class Result
    attr_accessor :id, :uid_imdb, :name, :magnet_link

    def initialize row, uid_imdb, magnet_a
      self.id = row.inner_html.match(/torrent\/([\d]+)\/[a-zA-Z0-9\-]*\//)[1]
      self.uid_imdb = uid_imdb
      self.name = row.css('.name').first.content.strip
      if magnet_a.size > 0
        magnet_link = magnet_a.first[:href]
      else
        magnet_link = nil
      end
      self.magnet_link = magnet_link
    end
  end
end
