import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import apology, login_required
from gtts import gTTS
import random, string, datetime, secrets
from random import randint, uniform

# Configure application
app = Flask(__name__)

# Generate a random 24-byte secret key
secret_key = secrets.token_hex(24)
app.secret_key = secret_key

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finalproject.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/", methods=["GET"])
@login_required
def index():
    return render_template("index.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        namelist = []
        for user in db.execute("SELECT username FROM users"):
            namelist.append(user["username"])

        if not username:
            return apology("must provide username", 400)

        elif not password:
            return apology("must provide password", 400)

        elif not confirmation:
            return apology("must confirm password", 400)

        elif password != confirmation:
            return apology("passwords don't match", 400)

        elif username in namelist:
            return apology("username taken", 400)

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)",
                   username, generate_password_hash(password))

        return redirect("/login")

    else:
        return render_template("register.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        flash('Welcome back, ' + request.form.get("username") + ' !')
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/guest", methods=["GET", "POST"])
def guest():
    if request.method == "POST":
        random_id = ''.join([random.choice(string.ascii_letters + string.digits) for _ in range(10)])
        session["user_id"] = random_id
        db.execute("INSERT INTO guests (guestid) VALUES (?)", random_id)
        flash('Welcome!')
        return redirect("/")

    else:
        return render_template("login.html")

@app.route("/reset-password", methods=["GET", "POST"])
def reset():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("must provide username", 400)

        elif not password:
            return apology("must provide password", 400)

        elif not confirmation:
            return apology("must confirm password", 400)

        elif password != confirmation:
            return apology("passwords don't match", 400)

        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                       username, generate_password_hash(password))
            db.execute("DELETE FROM users WHERE username = ?", username)
            return apology("username not found. please register first", 400)
        except:
            db.execute("UPDATE users SET hash = ? WHERE username = ?",
                       generate_password_hash(password), username)
            flash("Password has been reset. Please login again.")
            return redirect("/login")
    else:
        return render_template("reset.html")

@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")



MATH = ["Addition", "Subtraction", "Multiplication", "Division"]
SYMBOLS = ["+", "-", "×", "÷"]

@app.route("/math", methods=["GET", "POST"])
@login_required
def math():
    if request.method == "POST":
        category = request.form.get("category")
        level = request.form.get("level_chosen")
        level_chosen = level[6]

        print(category, level)
        if category == "Addition":
            if level == "Level 1":
                list = []
                ans = []
                for i in range(10):
                    num1 = randint(5, 20)
                    num2 = randint(15, 50 - num1)
                    list.append((num1, num2))
                    ans.append(num1 + num2)

            elif level == "Level 2":
                list = []
                ans = []
                for i in range(10):
                    while True:
                        try:
                            num1 = randint(50, 200)
                            num2 = randint(65, 200 - num1)
                            break
                        except:
                            pass

                    list.append((num1, num2))
                    ans.append(num1 + num2)

            elif level == "Level 3":
                list = []
                ans = []
                for i in range(10):
                    type = randint(1, 2)
                    if type == 1:
                        num1 = randint(100, 1000)
                        num2 = randint(100, 5000 - num1)
                    else:
                        num1 = round(random.uniform(0,100), 3)
                        num2 = round(random.uniform(0,100), 3)
                    list.append((num1, num2))
                    ans.append(num1 + num2)

            return render_template("math_qns.html", list=list, ans=ans, symbol = SYMBOLS[0], category=category, level=level_chosen)

        elif category == "Subtraction":
            if level == "Level 1":
                list = []
                ans = []
                for i in range(10):
                    num1 = randint(15, 50)
                    num2 = randint(7, 45)
                    if num2 > num1:
                        _ = num1
                        num1 = num2
                        num2 = _

                    list.append((num1, num2))
                    ans.append(num1 - num2)

            elif level == "Level 2":
                list = []
                ans = []
                for i in range(10):
                    while True:
                        try:
                            num1 = randint(50, 200)
                            num2 = randint(50, 200 - num1)
                            break
                        except:
                            pass
                    list.append((num1, num2))
                    ans.append(num1 - num2)

            elif level == "Level 3":
                list = []
                ans = []
                for i in range(10):
                    type = randint(1, 3)
                    if type == 2:
                        num1 = randint(105, 500)
                        num2 = randint(50, 100)
                        num3 = randint(70, 300)
                        list.append((num1, num2, num3))
                        ans.append(num1 - num2 + num3)
                    else:
                        if type == 1:
                            num1 = randint(100, 5000)
                            num2 = randint(100, 4000)
                            while num2 >= num1:
                                num2 = randint(100, 4000)
                            list.append((num1, num2))
                            ans.append(num1 - num2)

                        else:
                            num1 = round(random.uniform(0,100), 3)
                            num2 = round(random.uniform(0,100), 3)
                            list.append((num1, num2))
                            ans.append(round(num1 - num2, 3))

            return render_template("math_qns.html", list=list, ans=ans, symbol=SYMBOLS[1], category=category, level=level_chosen)

        elif category == "Multiplication":
            if level == "Level 1":
                list = []
                ans = []
                for i in range(10):
                    num1 = randint(3, 10)
                    num2 = randint(3, 20 - num1)
                    list.append((num1, num2))
                    ans.append(num1 * num2)

            elif level == "Level 2":
                list = []
                ans = []
                for i in range(10):
                    while True:
                        try:
                            num1 = randint(30, 100)
                            num2 = randint(30, 155 - num1)
                            break
                        except:
                            num2 = randint(155 - num1 + 50, 120)
                    list.append((num1, num2))
                    ans.append(num1 * num2)

            elif level == "Level 3":
                list = []
                ans = []
                for i in range(10):
                    type = randint(1, 3)
                    if type == 2:
                        num1 = randint(105, 500)
                        num2 = randint(50, 100)
                        num3 = randint(2, 10)
                        list.append((num1, num2, num3))
                        ans.append(num1 * num2 * num3)
                    else:
                        if type == 1:
                            num1 = randint(100, 1000)
                            num2 = randint(100, 5000 - num1)
                        else:
                            num1 = round(random.uniform(0,100), 3)
                            num2 = randint(3, 10)
                        list.append((num1, num2))
                        ans.append(num1 * num2)

            return render_template("math_qns.html", list=list, ans=ans, symbol = SYMBOLS[2], category=category, level=level_chosen)

        elif category == "Division":
            if level == "Level 1":
                list = []
                ans = []
                for i in range(10):
                    d1 = randint(2, 10)
                    d2 = randint(2, 10)
                    num1 = d1 * d2
                    num2 = d2
                    list.append((num1, num2))
                    ans.append(num1/num2)
                return render_template("math_qns.html", list=list, ans=ans, symbol=SYMBOLS[3], category=category, level=level_chosen)

            elif level == "Level 2":
                list = []
                ans = []
                for i in range(10):
                    d1 = randint(50, 150)
                    d2 = randint(5, 15)
                    num1 = d1 * d2
                    num2 = d2
                    list.append((num1, num2))
                    ans.append(num1/num2)
                return render_template("math_qns.html", list=list, ans=ans, symbol=SYMBOLS[3], category=category, level=level_chosen)

            elif level == "Level 3":
                list = []
                ans = []
                typelist = []
                for i in range(10):
                    type = randint(1, 3)
                    if type == 2:
                        d1 = randint(10, 30)
                        d2 = randint(10, 30)
                        d3 = randint(5, 50)
                        num1 = d1 * d2 * d3
                        num2 = d2
                        num3 = d3
                        list.append((num1, num2, num3))
                        ans.append(d1)
                        typelist.append(type)

                    elif type == 1:
                        d1 = randint(30, 50)
                        d2 = randint(5, 50)
                        d3 = randint(10, 35)
                        num1 = d1 * d2 * d3
                        num2 = d2
                        num3 = d1
                        list.append((num1, num2, num3))
                        ans.append(d3)
                        typelist.append(type)

                    else:
                        num1 = round(random.uniform(0,100), 3)
                        num2 = randint(2, 9)
                        list.append((num1, num2))
                        ans.append(round((num1 / num2), 3))
                        typelist.append(type)
                print('hello', list)
                return render_template("math_qns.html", list=list, ans=ans, symbol=SYMBOLS[3], type=typelist, category=category, level=level_chosen)
    else:
        return render_template("math.html", category=MATH)


# @app.route("/addition", methods=["GET", "POST"])
# @login_required




@app.route("/english", methods=["GET", "POST"])
@login_required
def spelling():
    with open("large", "r") as words:
        words = words.read().splitlines()
    list = []
    n = 0
    while n < 10:
        word = random.choice(words)
        if word not in list:
            list.append(str(word))
            n+=1
    return render_template("english.html", list=list)


@app.route("/mygrades", methods=["GET", "POST"])
@login_required
def mygrades():
    user_id = session["user_id"]

    if request.method == "POST":
        data = request.get_json()
        try:
            level = data['level']
        except:
            level = '-'
        score = data['score']
        quiz = data['category']

        date = datetime.datetime.now()

        db.execute("INSERT INTO pastgrades (user_id, quiz, level, score, date) VALUES (?, ?, ?, ?, ?)",
                   user_id, quiz, level, score, date)

        return ("Success", 200)
    else:
        history = db.execute("SELECT quiz, level, score, date FROM pastgrades WHERE user_id = ? ORDER BY date DESC  LIMIT 10", user_id)
        return render_template("grades.html", history=history)

