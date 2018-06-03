import mechanicalsoup
import random

browser = mechanicalsoup.StatefulBrowser()

def getName():
  firstname = ""
  lastname = ""
  return firstname,lastname
def getUserName(first,last):
  username = first + last
  number_cnt = random.randint(0, 30 - len(username))
  for i in range(number_cnt):
    username += str(random.randint(0,9))
username = firstname + lastname



browser.open("https://flightaware.com/commercial/flightxml/signup.rvt?product_type=1")
browser.follow_link("/account/join/")

browser.select_form('form[method="post"]')
browser["name_first"] = "Michael Oxlong"
#browser["custtel"] = "00 00 0001"
#browser["custemail"] = "nobody@example.com"
#browser["size"] = "medium"
#browser["topping"] = "onion"
#browser["topping"] = ("bacon", "cheese")
#browser["comments"] = "This pizza looks really good :-)"
print(browser.get_current_page())
# Uncomment to launch a real web browser on the current page.
browser.launch_browser()

# Uncomment to display a summary of the filled-in form
# browser.get_current_form().print_summary()

#response = browser.submit_selected()
#print(response.text)