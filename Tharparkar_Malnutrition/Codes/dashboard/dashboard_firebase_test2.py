# since this app has already been initialized as the main app. All new programming will now be done exclusively on this app.

import firebase_admin
from firebase_admin import db
from firebase_admin import credentials
import time

# do this everytime it is run on a new pc
# default_app = firebase_admin.initialize_app()

# Fetch the service account key JSON file contents
cred = credentials.Certificate('secrets.json')

firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://esp32-test-project-a01-default-rtdb.firebaseio.com/'
})

while(True):
    ref = db.reference('/Nodes')

    # Read the data at the posts reference
    print(ref.get())
    print()
    time.sleep(3600*5)