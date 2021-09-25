from flask import Flask, render_template, Response, redirect, url_for
import cv2
from flask import jsonify
import mysql.connector
from flask import request
import random
import base64
import threading

app = Flask(__name__)

camera = cv2.VideoCapture(2)  # use 0 for web camera
#  for cctv camera use rtsp://username:password@ip_address:554/user=username_password='password'_channel=channel_number_stream=0.sdp' instead of camera
# for local webcam use cv2.VideoCapture(0)

def thread_save_picture(img_base64):
    cnx = None
    result = []
    try:
        cnx = mysql.connector.connect(**config)
        cur = cnx.cursor()

        query_insert = ("INSERT INTO data_photo (photo) VALUES (%s)")
        item_data = (img_base64,)
        cur.execute(query_insert, item_data)

        cnx.commit()
        cur.close()
    except Exception as e:
        print(e)
    finally:
        if cnx != None:
            cnx.close()

def gen_frames():  # generate frame by frame from camera
    while True:
        # Capture frame-by-frame
        success, frame = camera.read()  # read the camera frame
        if not success:
            break
        else:
            ret, buffer = cv2.imencode('.jpg', frame)
            jpg_as_text = base64.b64encode(buffer)
            x = threading.Thread(target=thread_save_picture, args=(jpg_as_text,))
            x.start()
            frame = buffer.tobytes()
            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')  # concat frame one by one and show result

# @app.after_request
# def add_header(r):
#     """
#     Add headers to both force latest IE rendering engine or Chrome Frame,
#     and also to cache the rendered page for 10 minutes.
#     """
#     r.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
#     r.headers["Pragma"] = "no-cache"
#     r.headers["Expires"] = "0"
#     r.headers['Cache-Control'] = 'public, max-age=0'
#     return r

@app.route('/video_feed')
def video_feed():
    #Video streaming route. Put this in the src attribute of an img tag
    return Response(gen_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/data/last_one', methods = ['GET'])
def get_last_one():
    cnx = None
    result = []
    try :
        cnx = mysql.connector.connect(**config)
        cur = cnx.cursor()

        query = "(SELECT id FROM data_profile WHERE is_active = '1' and is_delete = '0')"
        cur.execute(query)
        result = cur.fetchone()
        if result != None :
            query = "(SELECT * FROM data_logger WHERE profile_id = %s ORDER BY ctime DESC limit 1)"
            cur.execute(query, (result[0],))
            result = cur.fetchone()
        else :
            result = []
        cur.close()
    except Exception as e :
        print(e)
    finally :
        if cnx != None :
            cnx.close()

    return jsonify({ "status" : "ok", "data" : result })

@app.route('/data/get_current_data', methods = ['GET'])
def get_current_data():
    limit = int(request.args.get('limit',0))
    print(limit)
    cnx = None
    result = []
    description = ""
    try :
        cnx = mysql.connector.connect(**config)
        cur = cnx.cursor()
        
        query = "(SELECT id FROM data_profile WHERE is_active = '1' and is_delete = '0')"
        cur.execute(query)
        result = cur.fetchone()
        if result != None :
            if limit == 0 :
                query = "(SELECT * FROM data_logger WHERE profile_id = %s ORDER BY ctime DESC )"
                cur.execute(query, (result[0],))
            else :
                query = "(SELECT * FROM data_logger WHERE profile_id = %s ORDER BY ctime DESC LIMIT %s )"
                cur.execute(query, (result[0],limit,))
            result = cur.fetchall()
            description = "Show current data"
        else :
            result = []
            description = "No data or data has been deleted"

        cur.close()
    except Exception as e :
        print(e)
    finally :
        if cnx != None :
            cnx.close()

    return jsonify({ "status" : "ok", "data" : result, "description" : description })

@app.route('/data/get_active_profile', methods = ['GET'])
def get_active_profile():
    cnx = None
    result = []
    try :
        cnx = mysql.connector.connect(**config)
        cur = cnx.cursor()
        query = "(SELECT * FROM data_profile WHERE is_active = '1')"
        cur.execute(query)
        result = cur.fetchone()
        cur.close()
    except Exception as e :
        print(e)
    finally :
        if cnx != None :
            cnx.close()

    return jsonify({ "status" : "ok", "data" : result })

@app.context_processor
def var_profile_list():
    cnx = None
    result = []
    try :
        cnx = mysql.connector.connect(**config)
        cur = cnx.cursor()
        query = "(SELECT * FROM data_profile WHERE is_delete = '0')"
        cur.execute(query)
        result = cur.fetchall()
        cur.close()
    except Exception as e :
        print(e)
    finally :
        if cnx != None :
            cnx.close()
    return dict(profile_list=list(result))

@app.context_processor
def var_last_data():
    cnx = None
    result = []
    try :
        cnx = mysql.connector.connect(**config)
        cur = cnx.cursor()

        query = "(SELECT id FROM data_profile WHERE is_active = '1' and is_delete = '0')"
        cur.execute(query)
        result = cur.fetchone()
        if result != None :
            query = "(SELECT * FROM data_logger WHERE profile_id = %s ORDER BY ctime DESC limit 1)"
            cur.execute(query, (result[0],))
            result = cur.fetchone()
        else :
            result = []
        cur.close()
    except Exception as e :
        print(e)
    finally :
        if cnx != None :
            cnx.close()
    return dict(last_data=list(result))

@app.route('/data/get_all_profile', methods = ['GET'])
def get_all_profile():
    cnx = None
    result = []
    try :
        cnx = mysql.connector.connect(**config)
        cur = cnx.cursor()
        query = "(SELECT * FROM data_profile WHERE is_delete = '0')"
        cur.execute(query)
        result = cur.fetchall()
        cur.close()
    except Exception as e :
        print(e)
    finally :
        if cnx != None :
            cnx.close()

    return jsonify({ "status" : "ok", "data" : result })

@app.route('/data/add_profile', methods = ['POST'])
def add_profile():
    cnx = None
    result = []
    try :
        cnx = mysql.connector.connect(**config)
        cur = cnx.cursor()
        
        query_update = ("UPDATE data_profile SET is_active = '0'")
        cur.execute(query_update)

        query_insert = ("INSERT INTO data_profile (profile_name, is_active) VALUES (%s, '1')")
        item_data = (request.form["profile"],)
        cur.execute(query_insert, item_data)

        cnx.commit()
        cur.close()
    except Exception as e :
        print(e)
    finally :
        if cnx != None :
            cnx.close()

    #return jsonify({ "status" : "ok", "description" : "Data has been saved successfully" })
    return redirect("/", code=303)

@app.route('/data/set_profile/<id>', methods = ['GET', 'POST'])
def set_profile(id):
    cnx = None
    result = []
    try :
        cnx = mysql.connector.connect(**config)
        cur = cnx.cursor()
        
        query_update = ("UPDATE data_profile SET is_active = '0'")
        cur.execute(query_update)

        query_update = ("UPDATE data_profile SET is_active = '1' WHERE id = %s")
        cur.execute(query_update,(id,))

        cnx.commit()
        cur.close()
    except Exception as e :
        print(e)
    finally :
        if cnx != None :
            cnx.close()

    # return jsonify({ "status" : "ok", "description" : "Profile has been successfully activated" })
    #return redirect(url_for('/'))
    return redirect("/", code=303)

@app.route('/data/delete_profile/<id>', methods = ['DELETE'])
def delete_profile(id):
    cnx = None
    result = []
    description = ""
    try :
        cnx = mysql.connector.connect(**config)
        cur = cnx.cursor()

        query = "(SELECT id FROM data_profile WHERE is_active = '1')"
        cur.execute(query)
        result = cur.fetchone()
        id = int(id)
        if id == int(result[0]) :
            description = "This profile is active"
        else :
            query_delete = ("UPDATE data_profile SET is_delete = '1' WHERE id = %s")
            cur.execute(query_delete, (id,))
            cnx.commit()
            description = "Data has been delete successfully"
        
        cur.close()
    except Exception as e :
        print(e)
    finally :
        if cnx != None :
            cnx.close()

    return jsonify({ "status" : "ok", "description" : description })

@app.route('/', methods = ['GET'])
def index():
    """Video streaming home page."""
    return render_template('index.html', rand=random.randrange(100, 1000))


if __name__ == '__main__':
    config = {
        'user': 'root',
        'password': '123456789',
        #'password':'',
        'host': '127.0.0.1',
        'database': 'rocket_lapan',
        'raise_on_warnings': True
    }
    cnx = mysql.connector.connect(**config)
    app.run(debug=True)