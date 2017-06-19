# set ":ssl_verify_mode" to "OpenSSL::SSL::VERIFY_NONE" if ssl fail

module ThePirateBay
  BASE_URL = 'https://thepiratebay.org'

  class Top
    attr_accessor :results, :limit, :uids_imdb

    def initialize limit, uids_imdb
      @results = []
      @limit = limit
      @uids_imdb = uids_imdb
    end

    def execute
      doc = Nokogiri::HTML(open("#{ThePirateBay::BASE_URL}/top/200").read)
      doc.css('#searchResult tr').each_with_index do |row, index|
        next if index == 0
        next if row.css('td').size <= 1
        tr_doc = Nokogiri::HTML(open("#{ThePirateBay::BASE_URL}/torrent/#{row.inner_html.match(/torrent\/([\d]+)\//)[1]}").read)
        imdb_url = tr_doc.inner_html.match(/http:\/\/www\.imdb\.com\/title\/tt([0-9]{1,7})\//)
        next if imdb_url == nil
        next if @uids_imdb.include? imdb_url[1]
        @uids_imdb << imdb_url[1]
        next if !tr_doc.inner_html.match(/<dd>English/)
        @results << ThePirateBay::Result.new(row, imdb_url[1])
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
      doc = Nokogiri::HTML(open("#{ThePirateBay::BASE_URL}/search/#{search_string}/0/99/200").read)
      doc.css('#searchResult tr').each_with_index do |row, index|
        next if (index == 0)
        next if (row.css('td').size <= 1)
        tr_doc = Nokogiri::HTML(open("#{ThePirateBay::BASE_URL}/torrent/#{row.inner_html.match(/torrent\/([\d]+)\//)[1]}").read)
        imdb_url = tr_doc.inner_html.match(/http:\/\/www\.imdb\.com\/title\/tt([0-9]{1,7})\//)
        next if imdb_url == nil
        next if @uids_imdb.include? imdb_url[1]
        @uids_imdb << imdb_url[1]
        next if !tr_doc.inner_html.match(/<dd>English/)
        @results << ThePirateBay::Result.new(row, imdb_url[1])
        if @results.size >= @limit
          break
        end
      end
      @results
    end
  end

  class Result
    attr_accessor :id, :uid_imdb, :name, :magnet_link

    def initialize row, uid_imdb
      self.id = row.inner_html.match(/torrent\/([\d]+)\//)[1]
      self.uid_imdb = uid_imdb
      self.name = row.css('.detName').first.content.strip
      magnet_links = row.css('td')[1].css("a[title='Download this torrent using magnet']")
      if magnet_links.size > 0
        magnet_link = magnet_links.first[:href]
      else
        magnet_link = nil
      end
      self.magnet_link = magnet_link
    end
  end
end
