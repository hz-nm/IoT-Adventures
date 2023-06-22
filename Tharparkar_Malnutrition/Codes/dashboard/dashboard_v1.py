from encodings import normalize_encoding
import streamlit as st
import numpy as np
import pandas as pd

# Credentials for FIREBASE
#define FIREBASE_HOST "https://esp32-test-project-a01-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "mgqNwC71uXQ9xizdRhveS78tFxizsZXcnIfWT31a"

DATA_URL = ''
DATE_COLUMN = 'date/time'



st.header('Hello 🌎!')
if st.button('Balloons?'):
    st.balloons()

chart_data = pd.DataFrame(
    np.random.randn(20, 3),
    columns=['a', 'b', 'c']
)
st.header('Random Line Chart')
st.line_chart(chart_data)

st.header('Plotting a MAP')
map_data = pd.DataFrame(
    [[24.93418524900444, 67.11216645686935]],
    columns=['lat', 'lon']
)

st.map(map_data)


@st.cache
def load_data(nrows):
    # load the data over here and convert to pd Dataframe that can then be displayed on the page
    data = pd.read_csv(DATA_URL, nrows=nrows)
    lowercase = lambda x: str(x).lower()

    data.rename('lowercase', axis='columns', inplace=True)

    data[DATE_COLUMN] = pd.to_datetime(data[DATE_COLUMN])
    
