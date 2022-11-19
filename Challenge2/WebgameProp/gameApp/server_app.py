from flask import Flask, redirect, render_template



app = Flask(__name__)



@app.route('/')
def login():
    return render_template('login/index.html')


@app.route('/game')
def game():
    return render_template('game/index.html')


@app.route('/won')
def won():
    return render_template('endscreen/index.html')

    
    
    
if __name__ == "__main__":
    app.run()