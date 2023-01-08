import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session, url_for

# Configure application
app = Flask(__name__)
app.secret_key = b'a secret key'

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

monthDict = {1:'Jan', 2:'Feb', 3:'Mar', 4:'Apr', 5:'May', 6:'Jun', 
            7:'Jul', 8:'Aug', 9:'Sep', 10:'Oct', 11:'Nov', 12:'Dec'}


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name = request.form['name']
        birthday = request.form['birthday']
        year, month, day = birthday.split('-')
        if int(day) not in range(1,32) or int(month) not in range(1,13):
            error_msg = "Invalid inputs"
            birthdays = db.execute("SELECT * FROM birthdays_year")
            return render_template("index.html", birthdays=birthdays, monthDict=monthDict, error_msg=error_msg)
        else:
            db.execute("INSERT into birthdays_year (name, day, month, year) VALUES (?, ?, ?, ?)", name,day,month,year)
        return redirect("/")

    else:
        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays_year")
        return render_template("index.html", birthdays=birthdays, monthDict=monthDict)


