class FriendRequestMailer < ApplicationMailer
  default from: "no-reply@gaflix.com"

  def send_mail sender, receiver
    @sender = sender
    @receiver = receiver

    mail(to: receiver.email, subject: "GaFlix - Friend request received")
  end
end
