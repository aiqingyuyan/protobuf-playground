import json
import data
from flask import Flask
from flask_compress import Compress
from flask import request
from flask import render_template

app = Flask(__name__)
Compress(app)

@app.route("/api/articles", methods = ["GET", "POST"])
def articles():
    json_return = request.headers["Accept"] == "application/json"
    if (request.method == "GET"):
        if json_return:
            return json.dumps(data.articles)
        return data.get_protobuf_data().SerializeToString()

@app.after_request
def after_request(response):
    response.headers.add('Access-Control-Allow-Origin', '*')
    response.headers.add('Access-Control-Allow-Headers', 'Content-Type,Authorization')
    response.headers.add('Access-Control-Allow-Methods', 'GET,POST')
    return response

def main():
    app.run(debug = True)

if __name__ == "__main__":
    main()
