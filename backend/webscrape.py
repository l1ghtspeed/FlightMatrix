from requests import get
from requests.exceptions import RequestException
from contextlib import closing
from bs4 import BeautifulSoup
import SimpleHTTPServer
import SocketServer
from opensky_api import OpenSkyApi

api = OpenSkyApi()
s = 

PORT_NUMBER = 8080

def get_html(url):

    try:
        with closing(get(url, stream=True)) as resp:
            if is_good_response(resp):
                return resp.content
            else:
                return None

    except RequestException as e:
        print(e)


def is_good_response(resp):
    content_type = resp.headers['Content-Type'].lower()
    return (resp.status_code == 200 
            and content_type is not None
            and content_type.find('html') > -1)


def parse_html(url):
    raw_data = get_html(url)
    parsed_data = BeautifulSoup(raw_data, 'html.parser')
    for a in parsed_data.select('a'):
        if(identifyICAO24(a.text)):
            print(a.text)



def identifyICAO24(ident):
    if (len(ident) > 3):
        if (ident[0].isalpha() and ident[1].isalpha() and ident[2].isalpha()):
            if (ident[3:].isnumeric() and len(ident[3:]) < 5):
                return True
        
    return False
    

parse_html('https://flightaware.com/live/aircrafttype/787')
