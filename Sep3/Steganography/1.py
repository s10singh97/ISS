from stegano import lsb

secret = lsb.hide("img.jpg", "Hello World")
secret.save("img-secret.png")

clear_message = lsb.reveal("img-secret.png")
print(clear_message)