import serial
import mysql.connector

def insert_data(dict_data):
    global cnx
    print(dict_data)
    cursor = cnx.cursor()
    add_employee = ("INSERT INTO data_logger "
                    "(compas_x, compas_y, compas_z, azimuth, bearing, directional, temperature, pressure, altitude, gps_latitude, gps_longitude, gps_age, gps_altitude, gps_sat_value, gps_course, gps_speed, rssi) "
                    "VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)")
    cursor.execute(add_employee, dict_data)
    cnx.commit()
    cursor.close()

def parsing_data(lora_data):
    try :
        if ("<<DATA:" in lora_data) and (">>" in lora_data) :
            lora_data = lora_data.replace("<<DATA:", "")
            lora_data = lora_data.replace(">>", "")
            lora_data = lora_data.split(",")

            # column data
            # // x,y,z,azimuth,bearing,temperature,pressure,altitude,gps latitude,gps longitude,gps age, gps altitude, gps sat value, gps course, gps speed, rssi
            compas_x = int(lora_data[0])
            compas_y = int(lora_data[1])
            compas_z = int(lora_data[2])
            azimuth = int(lora_data[3])
            bearing = int(lora_data[4])
            directional = str(lora_data[5])
            temperature = float(lora_data[6])
            pressure = float(lora_data[7])
            altitude = float(lora_data[8])
            gps_latitude = float(lora_data[9])
            gps_longitude = float(lora_data[10])
            gps_age = int(lora_data[11])
            gps_altitude = float(lora_data[12])
            gps_sat_value = int(lora_data[13])
            gps_course = float(lora_data[14])
            gps_speed = float(lora_data[15])
            rssi = float(lora_data[16])
            insert_data((compas_x, compas_y, compas_z, azimuth, bearing, directional, temperature, pressure, altitude, gps_latitude, gps_longitude, gps_age, gps_altitude, gps_sat_value, gps_course, gps_speed, rssi))

        else :
            print("No data found!")
    except Exception as e :
        print(e)

if __name__ == "__main__":
    config = {
        'user': 'root',
        'password': '123456789',
        'host': '127.0.0.1',
        'database': 'rocket_lapan',
        'raise_on_warnings': True
    }
    cnx = mysql.connector.connect(**config)

    ser = serial.Serial('COM10')
    ser.baudrate = 115200
    while True:
        try:
            ser_bytes = ser.readline()
            lora_data = ser_bytes.decode("utf")
            lora_data = lora_data.strip()
            parsing_data(lora_data)
            #print(lora_data)
        except Exception as e :
            print(e)
