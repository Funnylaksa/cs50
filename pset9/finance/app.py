import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.context_processor
def inject_menu():
    if not session:
        return {}
    else:
        user_id = session["user_id"]
        users_rows = db.execute("SELECT * FROM users WHERE id = ?", user_id)
        cash = usd(users_rows[0]["cash"])
        username = users_rows[0]["username"]
        return dict(cash=cash, username=username)


@app.context_processor
def utility_processor():
    return dict(usd=usd)


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    portfolio_rows = db.execute(
        "SELECT * FROM portfolio WHERE user_id = ?", user_id)

    users_rows = db.execute("SELECT username FROM users WHERE id = ?", user_id)
    username = users_rows[0]["username"]
    
    for row in portfolio_rows:
        quote = lookup(row["symbol"])
        row["name"] = quote["name"]
        row["price"] = usd(quote["price"])
        row["total"] = usd(row["quantity"] * quote["price"])
    return render_template("portfolio.html", portfolio_rows=portfolio_rows, username=username)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        # Query database for username
        user_id = session["user_id"]
        users_rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cash = users_rows[0]["cash"]

        symbol = request.form.get("symbol").strip().upper()
        quantity = request.form.get("shares")
        quote = lookup(symbol)

        portfolio_rows = db.execute(
            "SELECT * FROM portfolio WHERE user_id = ? and symbol = ?", user_id, symbol)

        if not quote:
            return apology("invalid stock stymbol", 400)

        if not quantity or not quantity.isnumeric() or int(quantity) < 0:
            return apology("quantity must be a positive integer", 400)

        price = int(quote["price"])
        quantity = int(quantity)
        cost = price * quantity
        if cash < cost:
            return apology("you do not have enough cash to buy", 400)

        if len(portfolio_rows) != 1:
            db.execute("INSERT into portfolio (user_id, symbol, quantity) VALUES (?, ?, ?)",
                       user_id, symbol, quantity)
        else:
            new_quantity = portfolio_rows[0]["quantity"] + quantity
            db.execute("UPDATE portfolio SET quantity = ? WHERE user_id = ? and symbol = ?",
                       new_quantity, user_id, symbol)
        db.execute("INSERT into transactions (user_id, symbol, quantity, price, type, time) VALUES (?,?,?,?,?,datetime('now', 'localtime'))",
                   user_id, symbol, quantity, price, "BUY")
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   cash-cost, user_id)
        return redirect(url_for("index"))


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions_rows = db.execute(
        "SELECT * FROM transactions WHERE user_id = ?", user_id)

    users_rows = db.execute("SELECT username FROM users WHERE id = ?", user_id)
    username = users_rows[0]["username"].upper()
    return render_template("history.html", transactions_rows=transactions_rows, username=username)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol").strip()
        quote = lookup(symbol)
        if not quote:
            # error_msg = "Invalid stock symbol"
            # return render_template("quote.html", quote=quote, error_msg=error_msg)
            return apology("invalid stock stymbol", 400)
        return render_template("quote.html", quote=quote)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("/register.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        users_rows = db.execute("SELECT username FROM users")

        usernames = [user["username"] for user in users_rows]

        if not username or not password or not confirmation:
            return apology("all fields required", 400)
        if username in usernames:
            return apology("username already taken", 400)
        if password != confirmation:
            return apology("passwords do not match", 400)

        db.execute("INSERT into users (username, hash) VALUES (?,?)",
                   username, generate_password_hash(password))
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    portfolio_rows = db.execute(
            "SELECT symbol FROM portfolio WHERE user_id = ?", user_id)
    symbols = [row["symbol"] for row in portfolio_rows]
    if request.method == "GET":
        return render_template("sell.html", symbols=symbols)
    else:
        # Query database for username
        user_id = session["user_id"]
        users_rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cash = users_rows[0]["cash"]

        symbol = request.form.get("symbol").strip().upper()
        quantity = request.form.get("shares")
        quote = lookup(symbol)
        
        portfolio_rows = db.execute(
            "SELECT * FROM portfolio WHERE user_id = ? and symbol = ?", user_id, symbol)

        if not quote:
            return apology("invalid stock stymbol", 400)
        if not quantity or not quantity.isnumeric() or int(quantity) < 0:
            return apology("quantity must be a positive integer", 400)
        if len(portfolio_rows) != 1:
            return apology(f"you do own any {symbol} stock", 400)

        available_stock = portfolio_rows[0]["quantity"]
        price = int(quote["price"])
        quantity = int(quantity)
        cost = price * quantity
        if available_stock < quantity:
            return apology(f"you are unable to sell {quantity} stock. you only have {available_stock} {symbol} stock", 400)

        new_quantity = available_stock - quantity
        db.execute("UPDATE portfolio SET quantity = ? WHERE user_id = ? and symbol = ?",
                   new_quantity, user_id, symbol)
        db.execute("INSERT into transactions (user_id, symbol, quantity, price, type, time) VALUES (?,?,?,?,?,datetime('now', 'localtime'))",
                   user_id, symbol, quantity, price, "SELL")
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   cash+cost, user_id)
        return redirect(url_for("index"))
