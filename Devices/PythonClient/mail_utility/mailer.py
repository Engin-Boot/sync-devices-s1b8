import smtplib, ssl

class Mailer:
    def __init__(self, sender_email, passwd):
        self.sender_email = sender_email
        self.passwd = passwd
        

    def send(self, receiver_email, message):
        port = 465
        context = ssl.create_default_context()
        with smtplib.SMTP_SSL("smtp.gmail.com", port, context=context) as server:
            server.login("syncdevices.s1b12@gmail.com", self.passwd)
            server.sendmail(self.sender_email, receiver_email, message)
   