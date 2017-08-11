import httplib, urllib, base64, json


def get_emotion(url, key, image_path):
    ret = ""
    subscription_key = key
    headers = {
        'Content-Type': 'application/octet-stream',
        'Ocp-Apim-Subscription-Key': subscription_key,
    }
    
    params = urllib.urlencode({
    'returnFaceAttributes': 'emotion',
        'returnFaceId': 'false',
        'returnFaceLandmarks': 'false',
    })
    
    imageFile = open(image_path, "rb")
    data = imageFile.read()
    body = bytearray(data)
    
    try:
        #conn = httplib.HTTPSConnection('westcentralus.api.cognitive.microsoft.com')
        conn = httplib.HTTPSConnection(url)
        conn.request("POST", "/face/v1.0/detect?%s" % params, body, headers)
        response = conn.getresponse()
        data = response.read().decode('utf-8')
    
        # 'data' contains the JSON data. The following formats the JSON data for display.
        parsed = json.loads(data)
        #print ("Response:")
        #print (json.dumps(parsed, sort_keys=True, indent=2))
        ret = json.dumps(parsed, sort_keys=True, indent=2)
        conn.close()
    
    except Exception as e:
        print url, key, image_path
        ret = "Error"
        
    return ret
