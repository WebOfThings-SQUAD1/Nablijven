from flask import Flask, render_template, Blueprint, abort
from jinja2 import TemplateNotFound


app = Flask(__name__)


main = Blueprint('main', __name__, template_folder="templates")


@main.route("/")
def index():
    return render_template("login/index.html")


# blueprint_game = Blueprint('main', __name__, template_folder='templates')

# app.register_blueprint(blueprint_game)



# @blueprint_game.route('/', defaults={'page': 'login'})
# @blueprint_game.route('/<page>')
# def show(page):
#     try:
#         return render_template(f'{page}.html')
#     except TemplateNotFound:
#         abort(404)





if __name__ == '__main__':
    app.run (host = "127.0.0.1", port = 9919)