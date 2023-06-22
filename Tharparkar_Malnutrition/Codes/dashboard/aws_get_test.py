
import boto3
import plotly.express as px
from boto3.dynamodb.conditions import Key, Attr
import json

# from dashboard.dashboard_v1 import DATA_URL
temperature = []
pressure = []
humidity = []
ph = []
turbidity = []
dates = []

# do this every time it is run on a new PC
aws_access_key = "AKIAZZZNWBLN3O3MH24V"
aws_secret_key = "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"

region = "us-east-1"

dynamo_db = boto3.resource('dynamodb', region_name = region,
                            aws_access_key_id = aws_access_key,
                            aws_secret_access_key = aws_secret_key)

# dynamodb = boto3.client('dynamodb',
#                         region_name = region,
#                         aws_access_key_id = aws_access_key,
#                         aws_secret_access_key = aws_secret_key)

table = dynamo_db.Table('NodeData')

# Fetch the service account key JSON file contents
# We use the following resource
# https://boto3.amazonaws.com/v1/documentation/api/latest/guide/dynamodb.html#querying-and-scanning
# get all the data of Node 1
response = table.query(
    KeyConditionExpression=Key('id').eq('1')
)

print(response)

print(response['Items'][2])
print(str(response['Items'][2]["Pressure"]))

# for i in range(len(response['Items'])):
    # do something

# data_json = json.dumps(response['Items'][1])

# print(data_json)