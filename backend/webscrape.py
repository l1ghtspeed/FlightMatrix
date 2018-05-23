from requests import get
from requests.exceptions import RequestException
from contextlib import closing
from bs4 import BeautifulSoup



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
    f = open("ids.txt","w+")
    for a in parsed_data.select('a'):
        if(verify(a['href'])):
            if ('%' in a['href']):
                print(a['href'][16:len(a['href'])-4])
                f.write(a['href'][16:len(a['href'])-4]+'\n')
            else:
                print(a['href'][16:len(a['href'])])
                f.write(a['href'][16:len(a['href'])]+'\n')



def verify(ident):
    if ('/live/flight/id' in ident and 'airline' in ident):
        return True
        
    return False




parse_html('https://flightaware.com/live/aircrafttype/787')
