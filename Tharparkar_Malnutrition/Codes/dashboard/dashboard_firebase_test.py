
from firebase import firebase

# FirebaseAuthentication(secret, email, debug=False, admin=False, extra=None)
authentication = firebase.FirebaseAuthentication

fire_app = firebase.FirebaseApplication('https://esp32-test-project-a01-default-rtdb.firebaseio.com/', authentication=authentication)

# fire_app.authentication = authentication
print(authentication.extra)

user = authentication.get_user()
print(user.firebase_auth_token)

result = fire_app.get('/Nodes', None)

print(result)