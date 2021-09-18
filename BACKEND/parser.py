import serial
import mysql.connector

def parsing_data(lora_data):
    try :
        if ("<<DATA:" in lora_data) and (">>" in lora_data) :
            lora_data = lora_data.replace("<<DATA:", "")
            lora_data = lora_data.replace(">>", "")
            lora_data = lora_data.split(",")

            # column data
            # compas_x, compas_y, compas_z, azimuth, bearing, temperature, pressure, altitude, aclx, acly, aclz, gps latitude, gps longitude, gps altitude,rssi
            compas_x = int(lora_data[0])
            compas_y = int(lora_data[1])
            compas_z = int(lora_data[2])
            azimuth = int(lora_data[3])
            bearing = int(lora_data[4])
            temperature = float(lora_data[5])
            pressure = float(lora_data[6])
            altitude = float(lora_data[7])
            aclx = float(lora_data[8])
            acly = float(lora_data[9])
            aclz = float(lora_data[10])
            gps_latitude = float(lora_data[11])
            gps_longitude = float(lora_data[12])
            gps_altitude = float(lora_data[13])
            rssi = float(lora_data[14])
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

    parsing_data("<<DATA:396,837,-467,64,2,34.25,100194.52,94.55,0.02,-0.02,0.98,0.00,0.00,0.00,-123>>")
    ser = serial.Serial('COM4')
    while True:
        try:
            ser_bytes = ser.readline()
            lora_data = ser_bytes.decode("utf")
            lora_data = lora_data.strip()
            parsing_data(lora_data)
        except Exception as e :
            print(e)
