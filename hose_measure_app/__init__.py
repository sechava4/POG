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
    cur = db.execute('select id, medida, color from entries order by id asc limit 10')
    cur2 = db.execute('select id, medida, color from listas order by id desc limit 10')
    entries = cur.fetchall()
    listas = cur2.fetchall()
    print(entries.__len__())            #Se pregunta por el numero de entradas de la tabla
    return render_template('show_entries.html', listas=listas, entries=entries)

@app.route('/add', methods=['POST'])
def add_line():
    if not session.get('logged_in'):
        abort(401)
    db = get_db()
    db.execute('insert into entries (medida, color) values (?, ?)',
                 [request.form['medida'], request.form['color']])
    db.commit()
    flash('Nuevo pedido ha sido montado')
    return redirect(url_for('show_entries'))


@app.route('/addesp', methods=['POST'])
def add_entry():

    db = get_db()
    content = request.get_json()  #Guarde el json que recibe de esp8266
    id = content["id"]
    medida = content["medida"]       #Lea los JSON
    color = content["color"]
    print(content)
    db.execute('insert into listas (id , medida , color) values (?, ? ,?)',[id, medida, color,])
    db.execute('delete from entries where id = (?)',[id])
    db.execute('delete from color_filter where id = (?)', [id])
    db.commit()
    flash('Nueva linea cortada')
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

#Get request desde el esp
@app.route('/helloesp')
def helloHandler():
    db = get_db()
    # Abre la tabla color_filter
    ini = db.execute('select id, medida, color from color_filter order by id asc')
    color_table = ini.fetchall()
    if(color_table.__len__() == False):   #Si no tiene nada

        # Se selecciona el pedido mas antiguo para ver que color tiene
        cur = db.execute('select id, medida, color from entries order by id asc limit 1')
        tarea = cur.fetchone()
        color = tarea['color']
        color=(color,)
        #Se seleccionan todos los pedidos de ese color

        cur2 = db.execute('select id, medida, color from entries where color = ?',color)
        lineas_color = cur2.fetchall()
        print(lineas_color.__len__())
        #print(lineas_color.index("id",1,3))

        ext2 = db.executemany('insert into color_filter (id , medida , color) values (?, ? ,?)',(lineas_color))
        db.commit()



    else:
        #Seleccione el pedido mas antiguo de la tabla color_filter
        ext = db.execute('select id, medida, color from color_filter order by id asc limit 1')
        tarea = ext.fetchone()

    id = (tarea['id'])
    medida = (tarea['medida'])
    color = tarea['color']
    data = {"id":id, "medida" : medida,"color":color}
    json_data = json.dumps(data)
    return  json_data
# Run a test server.


app.run(host = '0.0.0.0',debug = True, port = 8080)
#from extern devices use computer ip adress http://192.168.1.53:8080/
#para que sea visible tiene que estar todos los dispositivos conectados a la misma red