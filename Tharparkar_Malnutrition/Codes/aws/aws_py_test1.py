# https://www.google.com/search?q=aws+sdk+for+esp32+not+connecting+to+dynamodb&oq=aws+sdk+for+esp32+not+connecting+to+dy&aqs=chrome.1.69i57j33i10i160l2j33i21.15799j0j7&sourceid=chrome&ie=UTF-8
# https://boto3.amazonaws.com/v1/documentation/api/latest/guide/dynamodb.html
import boto3

# arn:aws:iot:us-east-1:673868810971:thing/TestNode1

aws_access_key = "AKIAZZZNWBLN3O3MH24V"
aws_secret_key = "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"

region = "us-east-1"



dynamo_db = boto3.resource('dynamodb', region_name=region,
                            aws_access_key_id = aws_access_key,
                            aws_secret_access_key = aws_secret_key)

client = boto3.client('dynamodb',
                        region_name = region,
                        aws_access_key_id = aws_access_key,
                        aws_secret_access_key = aws_secret_key)


table = dynamo_db.Table('NodeData')



print(table.creation_date_time)

table.put_item(
    Item={
        'Node': '7',
        'TakenAt': '2022-02-21 15:09:07',
        'Humidity': '50',
        'id': '7',
        'PH': '7',
        'Pressure': '1010.9',
        'Temperature': '26',
        'Turbidity': '100'
    }
)

