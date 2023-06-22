# This is the value that we have to work with
# {'Node1': 
#     {'2022-02-11 15:09:07': 
#         {'Humidity': 45.8457, 'PH': 7.1, 'Pressure': 1010.2417, 'Temperature': 25.31, 'Turbidity': 100},
#     '2022-02-11 15:12:25': 
#         {'Humidity': 45.64648, 'PH': 7.1, 'Pressure': 1010.29962, 'Temperature': 25.31, 'Turbidity': 100}}

from ctypes.wintypes import PCHAR
import json
import firebase_admin
from firebase_admin import db
from firebase_admin import credentials
import time
from encodings import normalize_encoding
import streamlit as st
import numpy as np
import pandas as pd

temperature = []
pressure = []
humidity = []
ph = []
turbidity = []

# do this every time it is run on a new PC
# default_app = firebase_admin.initialize_app()

# Fetch the service account key JSON file contents
cred = credentials.Certificate('secrets.json')

firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://esp32-test-project-a01-default-rtdb.firebaseio.com/'
})

while(True):
    ref = db.reference('/Nodes')

    # read the data at the posts reference
    data = ref.get()


    data_json = json.dumps(data)

    for date in data["Node1"]:
        temperature.append(data["Node1"][str(date)]["Temperature"])
        humidity.append(data["Node1"][str(date)]["Humidity"])
        pressure.append(data["Node1"][str(date)]["Pressure"])
        turbidity.append(data["Node1"][str(date)]["Turbidity"])
        ph.append(data["Node1"][str(date)]["PH"])


    with open("realtime_data.json", "w") as f:
        json.dump(data, f, indent=2)

    time.sleep(5*60)





