from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def index():
    """Main landing page for Germina-co agricultural monitoring system"""
    return render_template('index.html')

@app.route('/game')
def game():
    """Map game page (legacy)"""
    return render_template('Game.html')

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)