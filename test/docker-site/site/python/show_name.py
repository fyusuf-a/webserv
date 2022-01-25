#!/usr/bin/python3

import cgi, cgitb

form = cgi.FieldStorage()

first_name = form.getvalue('fname')
last_name = form.getvalue('lname')

print("Content-type:text/html\r\n\r\n")
print('<html>')
print("<head><title>Webserv</title><link rel=\"stylesheet\" href=\"https://cdn.simplecss.org/simple.min.css\"></head>");
print('<body>')
print('<header> <nav> <a href="/">Home</a> <a href="/php/php-ini.php" >PHP cgi</a> <a href="/php/cookie.php" >Cookie page</a> <a href="https://www.youtube.com/watch?v=YxjY_YTksKM" >Medieval exclusive song</a> </nav> <h1>Webserv</h1> <p>A simple Nginx clone</p> </header>')
print('<h2>Hello ', first_name, last_name, ', nice to meet you!</h2>')
print('<a href="/">Go back home</a>')
print('</body>')
print('</html>')
