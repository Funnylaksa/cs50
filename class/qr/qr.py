import os
import qrcode

img = qrcode.make("https://www.youtube.com/watch?v=xvFZjo5PgG0")
img.save("qrcode.png", "PNG")

os.system("code qrcode.png")