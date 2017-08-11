########### Python 3.6 #############
import http.client, urllib.request, urllib.parse, urllib.error, base64, json

subscription_key = '7aa23ea1b1f64e408dac7f3a08e34812'
uri_base = 'westcentralus.api.cognitive.microsoft.com'

headers = {
    'Content-Type': 'application/octet-stream',
    'Ocp-Apim-Subscription-Key': subscription_key,
}

params = urllib.parse.urlencode({
    'returnFaceAttributes': 'emotion',
    'returnFaceId': 'false',
    'returnFaceLandmarks': 'false',
})

imageFile = open("test.jpg", "rb")
data = imageFile.read()
body = bytearray(data)

try:

    conn = http.client.HTTPSConnection('westcentralus.api.cognitive.microsoft.com')
    conn.request("POST", "/face/v1.0/detect?%s" % params, body, headers)
    response = conn.getresponse()
    data = response.read().decode('utf-8')

    parsed = json.loads(data)
    print ("Response:")
    print (json.dumps(parsed, sort_keys=True, indent=2))
    conn.close()

except Exception as e:
    print('Error:')
    print(e)

