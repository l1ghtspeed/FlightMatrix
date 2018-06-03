from urllib.request import Request, urlopen
from bs4 import BeautifulSoup
import random
import requests

s = requests.Session()

def fetch(url, data=None):
    if data is None:
        return s.get(url).content
    else:
        return s.post(url, data=data).content


def getName():
  flist = open("firstnames.txt",'r')
  llsit = open("lastnames.txt",'r')
  firstname = flist.readline(random.randint(0,6296))
  lastname = llist.readline(random.randint(0,4945))
  return firstname,lastname

def getUserName(first,last):
  username = first + last
  number_cnt = random.randint(0, 30 - len(username))
  for i in range(number_cnt):
    username += str(random.randint(0,9))

def getEmail():
  req = Request('https://maildrop.cc/', headers={'User-Agent': 'Chrome'})
  page = urlopen(req)
  soup = BeautifulSoup(page, 'html.parser')
  email_box = soup.find('div', attrs={'id': 'suggestion'})
  return email_box.text.strip()

def verifyEmail(email):
  req = Request('https://maildrop.cc/'+'/inbox'+email[:12], headers={'User-Agent': 'Chrome'})
  page = urlopen(req)
  soup = BeautifulSoup(page, 'html.parser')
  #form = soup.find('form')
  #fields = form.findAll('input')
  #formdata = dict( (field.get('name'), field.get('value')) for field in fields)
  #formdata['mailbox'] = email
  print ("s")



print(getEmail())
verifyEmail(getEmail())
#page = urllib2.urlopen("https://flightaware.com/commercial/flightxml/signup.rvt?product_type=1")
