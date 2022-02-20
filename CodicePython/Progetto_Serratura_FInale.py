import psycopg2
import time
import serial
from datetime import datetime

def caricaDati():
    ts = time.time()
    timestamp = datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S')
    conn = psycopg2.connect(
        database="progettoiot", user='federicopierobon', password='', host='localhost', port= '8080'
    )
    x = conn.cursor()
    try:
        x.execute("""insert into accesso(timestamp, casa, porta, mac_address) values(%s,%s,%s,%s);""",(timestamp,'CasaTest1','PortaTest1','0035FFE4E97C'))
        conn.commit()
    except:
        conn.rollback()
    conn.close()

def start():
    ser = serial.Serial('/dev/cu.usbmodem145401', 9600, timeout=0.5)
    time.sleep(2)
    while True:
        data = ser.readline().decode('utf-8').rstrip()
        if data:
            print(data)
            if (data == 'connesso' or data == 'OK+CONN'):
                caricaDati()

start()

