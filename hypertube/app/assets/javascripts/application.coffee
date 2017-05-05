# This is a manifest file that'll be compiled into application.js, which will include all the files
# listed below.
#
# Any JavaScript/Coffee file within this directory, lib/assets/javascripts, vendor/assets/javascripts,
# or any plugin's vendor/assets/javascripts directory can be referenced here using a relative path.
#
# It's not advisable to add code directly here, but if you do, it'll appear at the bottom of the
# compiled file. JavaScript code in this file should be added after the last require_* statement.
#
# Read Sprockets README (https://github.com/rails/sprockets#sprockets-directives) for details
# about supported directives.
#
#= require jquery
#= require jquery_ujs
#= require jquery-ui
#= require sidekiq
#= require bootstrap
#= require turbolinks
#= require_tree .

customFileButton = (id) ->
  input = document.getElementById(id)
  input.addEventListener 'change', (e) ->
    name = e.target.value.split('\\').pop()
    if name
      document.getElementById('text-content').innerText = name
    else
      document.getElementById('text-content').innerText = document.getElementById('text-content').getAttribute('text')
      input.value = ''

$(document).on 'turbolinks:load', ->
  $('input.datepicker').each (input) ->
    $(this).datepicker
      dateFormat: 'yy-mm-dd'
      altField: $(this).next()
    # If you use i18n-js you can set the locale like that
    $(this).datepicker 'option', $.datepicker.regional[I18n.currentLocale()]
    return
  return

$(document).on 'click', '.border', ->
  $('.user_links').toggleClass('hidden')

$(document).on 'click', '.languages', ->
  $('.languages').toggleClass('open')

$(document).on 'click', 'input[type=file] + label', ->
  customFileButton($(this).attr('for'))

notification = (type, message, duration, position) ->
    id = new Date().getTime()
    $('body').append("<div class=\"notification #{type}\" id=\"#{id}\"></div>")
    $("##{id}").html message

    if position? && position == 'top'
        $("##{id}").animate {opacity: 1, top: 0}, 200, ->
            setTimeout ->
                $("##{id}").animate {opacity: 0, top: -50}, 200
            , duration || 4000
    else
        $("##{id}").animate {opacity: 1, bottom: +50}, 200, ->
            setTimeout ->
                $("##{id}").animate {opacity: 0, bottom: 0}, 200
            , duration || 4000

window.notification = notification;
