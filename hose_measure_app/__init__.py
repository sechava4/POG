#Santiago Echavarría Correa
#201220005014

import os
import sqlite3
from flask import Flask, request, session, g, redirect, url_for, abort, \
     render_template, flash
import time  # This is required to include time module.
import json

app = Flask(__name__) # create the application instance :  (__name__) se usa para que busque templates y static en el nombre del root path
app.config.from_object(__name__) # load config from this file , __init__.py

# Load default config and override config from an environment variable
app.config.update(dict(
    DATABASE=os.path.join(app.root_path, 'hose_measure_app.db'),
    SECRET_KEY='development key',
    USERNAME='raceline',
    PASSWORD='admin'
    ))
app.config.from_envvar('FLASKR_SETTINGS', silent=True)


def connect_db():
    """Connects to the specific database."""
    rv = sqlite3.connect(app.config['DATABASE'])
    rv.row_factory = sqlite3.Row # para tratar cada entrie de db como un diccionario
    return rv

def get_db():
    """Opens a new database connection if there is none yet for the
    current application context.
    """
    if not hasattr(g, 'sqlite_db'):
        g.sqlite_db = connect_db()
    return g.sqlite_db

@app.teardown_appcontext
def close_db(error):
    """Closes the database again at the end of the request."""
    if hasattr(g, 'sqlite_db'):
        g.sqlite_db.close()

@app.route('/')
def show_entries():
    db = get_db()
    cur = db.execute('select medida, color from listas order by id desc limit 10')
    cur2 = db.execute('select medida, color from entries order by id desc limit 3')
    entries = cur.fetchall()
    list = cur2.fetchall()
    return render_template('show_entries.html', list=list, entries=entries)



@app.route('/addesp', methods=['POST'])
def add_entry():

    db = get_db()
    content = request.get_json()  #Guarde el json que recibe de esp8266
    id = content["id"]
    medida = content["medida"]       #Lea los JSON
    color = content["color"]
    print(content)
    db.execute('insert into listas (id , medida , color) values (?, ? ,?)',[id, medida, color,])
    db.commit()
    flash('New entry was successfully posted')
    return redirect(url_for('show_entries'))


@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        if request.form['username'] != app.config['USERNAME']:
            error = 'Invalid username'
        elif request.form['password'] != app.config['PASSWORD']:
            error = 'Invalid password'
        else:
            session['logged_in'] = True
            flash('You were logged in')
            return redirect(url_for('show_entries'))
    return render_template('login.html', error=error)


@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    flash('You were logged out')
    return redirect(url_for('show_entries'))

@app.route('/helloesp')
def helloHandler():
    db = get_db()
    # Se selecciona el pedido mas antiguo
    ext = db.execute('select id, medida, color from entries order by id asc limit 1')
    tarea = ext.fetchone()
    id = (tarea['id'])
    medida = (tarea['medida'])
    color = tarea['color']
    if ((color=="red")or(color=="rojo")):
        color = "r"
    data = {"id":id, "medida" : medida,"color":color}
    json_data = json.dumps(data)
    return  json_data
# Run a test server.


app.run(host = '0.0.0.0',debug = True, port = 8080)
#from extern devices use computer ip adress http://192.168.1.53:8080/
#para que sea visible tiene que estar todos los dispositivos conectados a la misma red