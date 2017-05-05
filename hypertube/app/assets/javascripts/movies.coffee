# Place all the behaviors and hooks related to the matching controller here.
# All this logic will automatically be available in application.js.
# You can use CoffeeScript in this file: http://coffeescript.org/

$(document).on 'turbolinks:load', ->
  $('[href="#player"][role="tab"]').click () ->
    $.ajax {
      url: "/movie_views/",
      type: 'POST',
      dataType: 'json',
      data: { movie_view: { movie_id: $(this).data('movie') } }
    }

  if $('.pagination').length
    $('.pagination').css({display: 'none'});
    window.reach_end_of_movie = false
    window.pending = false
    $(window).unbind('scroll').scroll ->
      url = $('.pagination a[rel="next"]').attr('href')
      if url && !window.pending && !window.reach_end_of_movie && $(window).scrollTop() > $(document).height() - $(window).height() - 50
        window.movies_count = $('#movies_container figure').length
        window.pending = true
        $.ajaxSetup {async:false}
        $.getScript url, () ->
          window.pending = false
          if (window.movies_count == $('#movies_container figure').length)
            window.reach_end_of_movie = true
          else
            $('.pagination a[rel="next"]').attr('href', url.replace(/page=(\d{1,})/i, (match, p1) -> "page=#{parseInt(p1) + 1}") )

  Turbolinks.clearCache()
  if $('form#sort:not(.fixed)').length
    el = $('form#sort')
    cont = $('form#sort + #wrapper')
    top = $('form#sort').position().top - 70
    if ($(window).scrollTop() > top)
      el.css({'position': 'fixed', 'top': '70px'})
      cont.css({'margin-top': el.height() + 60})
    $(window).scroll ->
      isPositionFixed = (el.css('position') == 'fixed')
      if ($(window).scrollTop() > top && !isPositionFixed)
        el.css({'position': 'fixed', 'top': '70px'})
        cont.css({'margin-top': el.height() + 60})
      if ($(window).scrollTop() < top && isPositionFixed)
        el.css({'position': 'static', 'top': '0px'})
        cont.css({'margin-top': 0})
