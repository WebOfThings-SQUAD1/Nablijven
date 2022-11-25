from flask import Flask, redirect, render_template

try:
    [host, port] = open("../exe/addrs.conf", "r").read().split(':')
except Exception as e:
    print(e)
    port='127.0.0.1'
    port=9919
    
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
    app.run(host=host, port=port)
